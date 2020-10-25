#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <sys/types.h>  /* Type definitions used by many programs */
#include <sys/stat.h>
#include <fcntl.h>

// outline
//      open 2x
//      read
//      write
//      close 2x

#define BUF_SIZE 1024

int
main(int argc, char* argv[]) {

    ssize_t numRead;
    char buf[BUF_SIZE];

    /* Open input and output files */

    int fd_input = open(argv[1], O_RDONLY);
    int fd_output = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);

    /* Transfer data until we encounter end of input or an error */

    while ((numRead = read(fd_input, buf, BUF_SIZE)) > 0)
        write(fd_output, buf, numRead);

    /* Clean up open file descriptors */

    close(fd_input);
    close(fd_output);

    return EXIT_SUCCESS;
}
