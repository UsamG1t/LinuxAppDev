#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

enum
{
    BUF_SIZE = 8
};

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Error: :There are not enough files to move\n");
        return -1;
    }

    int fd_in, fd_out;

    if ((fd_in = open(argv[1], O_RDONLY)) < 0) {
        perror("Error with 1st file: ");
        return errno;
    }

    if ((fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        perror("Error with 2nd file: ");
        return errno;
    }

    char buf[BUF_SIZE];
    int retval;
    while ((retval = read(fd_in, &buf, BUF_SIZE)) > 0) {
        char* p = buf;
        int count = retval;

        while((retval = write(fd_out, &buf, count)) > 0) {
            p += retval;
            count -= retval;
        }

        if (retval < 0) {
            perror("Error with write-ability of file: ");
            close(fd_out);
            unlink(argv[2]);
            return errno;
        }
    }

    if (retval < 0) {
        perror("Error with read-ability of file: ");
        close(fd_out);
        unlink(argv[2]);
        return errno;
    }

    if (close(fd_out) < 0) {
        perror("Error during close 2nd file: ");
        close(fd_out);
        unlink(argv[2]);
        return errno;
    }

    close(fd_in);
    if (unlink(argv[1]) < 0) {
        perror("Error during delete 1st file: ");
        return errno;
    }

    return 0;
}