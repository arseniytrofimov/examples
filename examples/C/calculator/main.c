//there are only integer numbers
//there are no numbers < 0 (f.e. -5)
//and there is no "-<variable>" operation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define var_rule(c) (((c >= 'a') && (c <= 'z'))\
|| ((c >= 'A') && (c <= 'Z')) || (c == '_')\
|| ((c >= '0') && (c <= '9')))
#define all_values(c) (((c >= 'a') && (c <= 'z'))\
|| ((c >= 'A') && (c <= 'Z')) || (c == '+')\
|| ((c >= '0') && (c <= '9')) || (c == '-')\
|| (c == '*') || (c == '/') || (c == '_'))
#define isalpha(c) (((c >= 'a') && (c <= 'z'))\
|| ((c >= 'A') && (c <= 'Z')))
#define isnum(c) ((c >= '0') && (c <= '9'))
#define isoper(c) ((c == '-') || (c == '+')\
|| (c == '*') || (c == '/'))

char mult_div_descent(char c);
char symbol_descent(char c);

//-------------------------------------------

struct stack{
    int value;
    struct stack * prev;
};
struct stack * my_stack = NULL;

void push_stack(int val){
    /**
        pushes integer value val to stack
    **/
    if (my_stack == NULL){
        my_stack = malloc(sizeof(struct stack));
        my_stack->prev = NULL;
        my_stack->value = val;
    }else{
        struct stack * p;
        p = malloc(sizeof(struct stack));
        p->prev = my_stack;
        p->value = val;
        my_stack = p;
    }
}

int pop_stack(void){
    /**
        gets integer value from stack
    **/
    if (my_stack == NULL) return -1;
    struct stack * p;
    p = my_stack;
    my_stack = p->prev;
    int val = p->value;
    free(p);
    return val;
}

void free_stack(void){
    struct stack * p;
    while (my_stack != NULL){
        p = my_stack;
        my_stack = p->prev;
        free(p);
    }
}

//-------------------------------------------

struct variable{
    char var[7];
    int value;
};
struct variable *table = NULL;
///size_table holds number of variables in table
int size_table = 0;

void free_table(void){
    if (table == NULL) return;
    table = realloc(table, sizeof(struct variable));
    free(table);
}

//-------------------------------------------

///last_value holds 'o' if last char was operation,
///'v' if last char was number or variable,
///'b' if last char was a bracket
///I need it not to lose exception with missed value
char last_value = ' ';

///balance_brackets is used to look after brackets balance
int balance_brackets = 0;

//-------------------------------------------

void handle_missing_operator_exception(){
    /**
        there is no operation between
        some variables/numbers
    **/
    fprintf(stderr,
            "You forgot to put an operation between some values!\n");
    exit(1);
}

void handle_missing_value_exception(){
    /**
        there are two operations with no
        variable or number between them
    **/
    fprintf(stderr,
            "You forgot to put a value between some operations!\n");
    exit(2);
}

void handle_wrong_variable_exception(){
    /**
        variable was longer 6 chars
        or started with 0..9 or _
    **/
    fprintf(stderr,
            "Variable was longer 6 chars or started with 0..9 or _!\n");
    exit(3);
}

void handle_wrong_balance_of_brackets(int arg){
    /**
        error with brackets balance
        if arg equals -1, then '(' < ')'
        if arg equals 1 then '(' > ')'
        if arg equals 0 then there two brackets
        with nothing between them
    **/
    if (arg == -1)
        fprintf(stderr, "Wrong brackets balance!  '(' < ')'\n");
    if (arg == 1)
        fprintf(stderr, "Wrong brackets balance!  '(' > ')'\n");
    if (arg == 0)
        fprintf(stderr, "Two brackets nearby!\n");
    exit(4);
}

void handle_wrong_operator_exception(){
    /**
        syntax error
        there was an unknown symbol
        (not a..z, A..Z, 0..9, _, +, -, /, *)
    **/
    fprintf(stderr, "There was an unknown symbol!\n");
    exit(5);
}

void handle_wrong_int_number(){
    /**
        number is bigger then MaxInt
    **/
    fprintf(stderr, "Too big int number!\n");
    exit(6);
}

//-------------------------------------------

void use_operation(char o){
    /**
        uses operation 'o' to last two
        values from stack
    **/
    int value1, value2, res;
    value2 = pop_stack();
    value1 = pop_stack();
    switch (o){
        case '+':
            res = value1 + value2;
            break;
        case '-':
            res = value1 - value2;
            break;
        case '*':
            res = value1 * value2;
            break;
        case '/':
            if (value2 == 0){
                fprintf(stderr, "Trying to divide by 0");
                exit(8);
            }
            res = value1 / value2;
            break;
        default:
            handle_wrong_operator_exception();
            exit(1);
    }
    push_stack(res);
}

//-------------------------------------------

struct queue{
    //0 if number
    //1 if variable
    //2 if operation
    int type;
    int value;
    char c_value;
    struct queue * next;
};
struct queue *list = NULL;

void free_list(void){
    struct queue *p;
    while (list != NULL){
        p = list;
        list = p->next;
        free(p);
    }
}

void add_to_list_variable(void){
    struct queue *p, *p1;
    p = malloc(sizeof(struct queue));
    p->next = NULL;
    p->type = 1;
    p->value = size_table;
    if (list == NULL){
        list = p;
    }else{
        p1 = list;
        while (p1->next != NULL) p1 = p1->next;
        p1->next = p;
    }
}

void add_to_list_number(int number){
    struct queue *p, *p1;
    p = malloc(sizeof(struct queue));
    p->next = NULL;
    p->type = 0;
    p->value = number;
    if (list == NULL){
        list = p;
    }else{
        p1 = list;
        while (p1->next != NULL) p1 = p1->next;
        p1->next = p;
    }
}

void add_to_list_operation(char op){
    struct queue *p, *p1;
    p = malloc(sizeof(struct queue));
    p->next = NULL;
    p->type = 2;
    p->c_value = op;
    if (list == NULL){
        list = p;
    }else{
        p1 = list;
        while (p1->next != NULL) p1 = p1->next;
        p1->next = p;
    }
}

//-------------------------------------------

void add_variable(const char array[7]){
    /**
        adds new variable
        to the table with variables
    **/
    struct variable * p;
    if (size_table == 0)
        p = malloc(sizeof(struct variable));
    else
        p = realloc(table, (1 + size_table) * sizeof(struct variable));
    table = p;
    for (int i = 0; i <= 6; i++) table[size_table].var[i] = array[i];
    table[size_table].value = -1;
    add_to_list_variable();
    size_table++;
}

void check_propriety(char c){
    /**
        catches all situation that cause errors
        f.e. wrong brackets balance of unknown symbol
    **/
    char curr = ' ';
    if (c == '\n' || (int)c == -1) return;
    if (isalpha(c) || isnum(c)) curr = 'v';
    if (isoper(c)) curr = 'o';
    if (c == '(') curr = '(';
    if (c == ')') curr = ')';
    if (curr == ' ') handle_wrong_operator_exception();
    if (curr == last_value && curr == 'v')
        handle_missing_operator_exception();
    if (curr == last_value && curr == 'o')
        handle_missing_value_exception();
    if (curr == last_value && (curr == '(' || last_value == ')'))
        handle_wrong_balance_of_brackets(0);
    if (curr == '(' && last_value == ')')
        handle_wrong_balance_of_brackets(0);
    if (curr == ')' && last_value == '(')
        handle_wrong_balance_of_brackets(0);
    if ((curr == '(' && last_value == 'v') ||
        (curr == 'v' && last_value == ')'))
        handle_missing_value_exception();
    last_value = curr;
}

char get_next_char(void){
    /**
        function gets next char passing spaces
    **/
    char c;
    while ((c = (char)getchar()) == ' ');
    if (c == '\n') return '\n';
    if ((int)c == -1) return '\n';
    check_propriety(c);
    return c;
}

char get_full_number(char c){
    /**
        tries to find full number that
        starts with number in char c
        returns this number
    **/
    int number, i;
    char new_num[11];
    char next_char;
    new_num[0] = c;
    i = 1;
    next_char = (char)getchar();
    while (next_char >= '0' && next_char <= '9' && i <= 10){
        new_num[i] = next_char;
        i++;
        next_char = (char)getchar();
    }
    new_num[i] = '\0';
    if (next_char >= '0' && next_char <= '9')
        handle_wrong_int_number();
    if (var_rule(next_char))
        handle_wrong_variable_exception();
    number = atoi(new_num);
    add_to_list_number(number);
    if (next_char != ' '){
        check_propriety(next_char);
        return next_char;
    }
    next_char = get_next_char();
    return next_char;
}

char get_full_variable(char c){
    /**
        tries to find full variable that
        starts with char c
        if everything is fine, adds new variable
        to the table with variables
        returns next value after variable
    **/
    char new_var[7];
    char next_char;
    int i;
    new_var[0] = c;
    i = 1;
    next_char = (char)getchar();
    while (var_rule(next_char) && (i < 6)){
        new_var[i] = next_char;
        i++;
        next_char = (char)getchar();
    }
    new_var[i] = '\0';
    add_variable(new_var);
    if (var_rule(next_char))
        handle_wrong_variable_exception();
    if (next_char != ' '){
        check_propriety(next_char);
        return next_char;
    }
    next_char = get_next_char();
    if (var_rule(next_char))
        handle_missing_operator_exception();
    return next_char;
}

//-------------------------------------------
//next three functions create a recursive descent
//and function descent starts it
char begin_descent(char c){
    char curr, tmp;
    curr = c;
    curr = mult_div_descent(curr);
    while (curr == '+' || curr == '-'){
        tmp = curr;
        curr = get_next_char();
        curr = mult_div_descent(curr);
        add_to_list_operation(tmp);
    }
    return curr;
}

char mult_div_descent(char c){
    char curr, tmp;
    curr = c;
    curr = symbol_descent(curr);
    while (curr == '*' || curr == '/'){
        tmp = curr;
        curr = get_next_char();
        curr = symbol_descent(curr);
        add_to_list_operation(tmp);
    }
    return curr;
}

char symbol_descent(char c){
    char curr;
    curr = c;
    if (balance_brackets <= 0 && curr == ')')
        handle_wrong_balance_of_brackets(-1);
    if (curr == '('){
        balance_brackets += 1;
        curr = get_next_char();
        curr = begin_descent(curr);
        if (curr != ')'){
            if (all_values(curr))
                handle_wrong_balance_of_brackets(1);
            else
                handle_wrong_operator_exception();
        }else{
            curr = get_next_char();
            balance_brackets -= 1;
        }
    }else{
        if (isalpha(curr)){
            curr = get_full_variable(curr);
            return curr;
        }
        if (isnum(curr)){
            curr = get_full_number(curr);
            return curr;
        }
        if (curr != '\n')
            handle_wrong_operator_exception();
    }
    return curr;
}

void descent(void){
    char start_char = get_next_char();
    if (start_char == '\n') return;
    char last = begin_descent(start_char);
    if (last != '\n')
        handle_wrong_operator_exception();
}

//-------------------------------------------

void add_values(void){
    /**
        asks user to tell values
        for all variables
    **/
    char str[30];
    char per[7];
    char value[20];
    int val;
    int flag, j, i;
    char finish_str[8] = "Finish\n\0";
    printf("Please enter values in this format:\n");
    printf("<Name of variable> = <value>\\n\n");
    printf("To finish enter such string:\n");
    printf("Finish\\n\n");
    fgets(str, 30, stdin);
    while (strcmp(str, finish_str) != 0){
        i = 0;
        flag = 0;
        while (str[i] != ' '){
            per[i] = str[i];
            i++;
        }
        per[i] = '\0';
        i += 3;
        int o = i;
        while (str[i] != '\n'){
            value[i - o] = str[i];
            i++;
        }
        value[i - o] = '\0';
        if ((val = atoi(value)) == 0){
            printf("Wrong input for values for variables!\n");
            printf("Try again\n");
            fgets(str, 30, stdin);
            continue;
        }
        j = 0;
        while (j < size_table){
            if (strcmp(table[j].var, per) == 0){
                table[j].value = val;
                flag = 1;
                break;
            }
            j++;
        }
        if (!flag){
            printf("There is no such variable!\n");
            printf("Try again\n");
        }
        fgets(str, 30, stdin);
    }
    printf("You have finished values input\n");
    int flag2 = 1;
    j = 0;
    while (j < size_table){
        if (table[j].value == -1) flag2 = 0;
        j++;
    }
    if (flag2 == 0){
        printf("You didn't put values for all variables!\n");
        exit(7);
    }
}

//-------------------------------------------

int result(void){
    ///calculates the result of expression
    struct queue *p;
    p = list;

    while (p != NULL){
        switch (p->type){
            case 0:
                push_stack(p->value);
                break;
            case 1:
                push_stack(table[p->value].value);
                break;
            case 2:
                use_operation(p->c_value);
                break;
        }
        p = p->next;
    }
    return pop_stack();
}

//-------------------------------------------


int main(){
    descent();
    if (size_table != 0) add_values();
    int res = result();
    printf("%d\n", res);
    free_stack();
    free_list();
    free_table();
    return 0;
}
