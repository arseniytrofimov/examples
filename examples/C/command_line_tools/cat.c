#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char ** argv){
    int fd, l, n, k, tmp;
    int i = 1, flag = 0, flag2;
    char buffer[4096];
    char buf[100];
    if (argc < 2){
        write(2, "Too few arguments\n", 18);
        return 1;
    }
    if (!(strcmp(argv[1], "-n"))){
        flag = 1;
        if (argc == 2){
            write(2, "Too few arguments\n", 18);
            return 1;
        }
    }
    if (!flag){
        for (i = 1; i < argc; i++){
            if ((fd = open(argv[i], O_RDONLY)) == -1){
                write(2, "Can't open file\n", 16);
                return 2;
            }
            while ((n = read(fd, buffer, 4096)) > 0)
                write(1, buffer, n);
        }
    }else{
        for (int j = 2; j < argc; j++){
            if ((fd = open(argv[j], O_RDONLY)) == -1){
                write(2, "Can't open file\n", 16);
                return 2;
            }
            while ((n = read(fd, buffer, 4096)) > 0){
                k = 0;
                flag2 = 0;
                while ((k != (n - 1)) && (k != n)){
                    tmp = k;
                    while ((buffer[k] != '\n') && (buffer[k] != EOF) && (k != (n - 1)))
                        k++;
                    if ((k == (n - 1)) && (buffer[k] != '\n') && (buffer[k] != EOF)){
                        flag2 = 1;
                    }else{
                        if (!flag2){
                            l = sprintf(buf, "%d", i);
                            i++;
                            buf[l] = ':';
                            buf[l + 1] = ' ';
                            write(1, buf, l + 2);
                            flag2 = 0;
                            k++;
                        }
                    }
                    write(1, &buffer[tmp], (k - tmp));
                }
            }
        }
    }
    return 0;
}
