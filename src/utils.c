#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/utils.h"

#define BUFFER_SIZE 4096

void err_n_die(const char *fmt, ...)
{
    int errno_save;
    va_list ap;

    errno_save = errno;

    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, "\n");
    fflush(stdout);

    if (errno_save != 0)
    {
        fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    va_end(ap);

    exit(1);
}

char *read_file(int fd)
{
    char read_buffer[BUFFER_SIZE];
    memset(read_buffer, 0, BUFFER_SIZE);

    char *file_text = malloc(sizeof(char));

    int bytes_read = 0;
    int current_size = 0;

    while ((bytes_read = read(fd, read_buffer, BUFFER_SIZE - 1)) > 0)
    {
        // increase the size of file_text by the number of bytes read
        file_text = realloc(file_text, sizeof(char) * (current_size + bytes_read));
        // move the text from the buffer to the newly allocated space in file text
        memmove(file_text + current_size, read_buffer, bytes_read);
        // increase the size of file text by the number of bytes read into the buffer
        current_size = current_size + bytes_read;

        // setting the entries of read_buffer to zero to avoid any errors
        memset(read_buffer, 0, BUFFER_SIZE);
    }

    // adding another character and setting it to the terminating character to indicate the end of the string.
    file_text = realloc(file_text, sizeof(char) * (current_size + 1));
    file_text[current_size] = 0;
    return file_text;
}