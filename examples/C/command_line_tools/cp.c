#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv){
    int fd, fd1, n;
    char buffer[4096];
    struct stat s;
    if (argc > 3){
        write(2, "Too many arguments\n", 19);
        return 0;
    }
    if (argc < 3){
        write(2, "Too few arguments\n", 18);
        return 0;
    }
    if ((fd = open(argv[1], O_RDONLY)) == -1){
        write(2, "Can't open file1\n", 17);
        return 1;
    }
    if ((fd1 = open(argv[2], O_RDONLY)) != -1){
        write(2, "Such file already exists\n", 25);
        return 2;
    }
    stat(argv[1], &s);
    if ((fd1 = creat(argv[2], s.st_mode)) == -1){
        write(2, "Can't create file2\n", 19);
        return 3;
    }
    while ((n = read(fd, buffer, 4096)) > 0)
        write(fd1, buffer, n);
    return 0;
}