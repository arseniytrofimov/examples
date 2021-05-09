#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void make_output(int str, int symbol, char ** argv){
    char s1[15] = " differs from ";
    char s2[8] = ": line ";
    char s3[9] = " symbol ";
    char buf[100];
    int len, i = 0;
    while (argv[1][i] != '\0')
        i++;
    write(1, argv[1], i);
    write(1, s1, 14);
    i = 0;
    while (argv[2][i] != '\0')
        i++;
    write(1, argv[2], i);
    write(1, s2, 7);
    len = sprintf(buf, "%d", str);
    write(1, buf, len);
    write(1, s3, 8);
    len = sprintf(buf, "%d", symbol);
    write(1, buf, len);
    write(1, "\n", 1);
}

int main(int argc, char ** argv){
    int fd1, fd2, n, n1, str_count, symbol_count;
    str_count = 1;
    symbol_count = 1;
    char buf1[4096], buf2[4096];
    if (argc > 3){
        write(2, "Too many arguments\n", 19);
        return 1;
    }
    if (argc < 3){
        write(2, "Too few arguments\n", 18);
        return 1;
    }
    if ((fd1 = open(argv[1], O_RDONLY)) == -1){
        write(2, "Can't open file1\n", 17);
        return 2;
    }
    if ((fd2 = open(argv[2], O_RDONLY)) == -1){
        write(2, "Can't open file2\n", 17);
        return 2;
    }
    int j = 0;
    while (j < 100){
        n = read(fd1, buf1, 4096);
        n1 = read(fd2, buf2, 4096);
        for (int i = 0; i < n; i++){
            if ((i == (n - 1)) || (i == (n1 - 1))){
                if ((buf1[i] == buf2[i]) || (n == n1)){
                    write(1, "There is no difference\n", 23);
                    return 0;
                }else{
                    make_output(str_count, symbol_count, argv);
                    return 3;
                }
            }
            if (buf1[i] == '\n'){
                str_count++;
                symbol_count = 1;
            }else
                symbol_count++;
            if (buf1[i] != buf2[i]){
                make_output(str_count, symbol_count, argv);
                return 3;
            }
        }
        j++;
    }
}