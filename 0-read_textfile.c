#include "main.h"
#include <stdlib.h>

/**
 * read_textfile - Reads a text file and prints its contents to POSIX stdout.
 * @filename: A pointer to the name of the file.
 * @letters: The number of letters that the function should read and print.
 *
 * Return: If the function fails or filename is NULL - 0.
 *         Otherwise - the actual number of bytes read and printed.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
    ssize_t fd, num_read, num_written;
    char *buffer;

    if (filename == NULL)
        return 0;

    buffer = malloc(sizeof(char) * letters);
    if (buffer == NULL)
        return 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        free(buffer);
        return 0;
    }

    num_read = read(fd, buffer, letters);
    if (num_read == -1)
    {
        free(buffer);
        close(fd);
        return 0;
    }

    num_written = write(STDOUT_FILENO, buffer, num_read);
    if (num_written == -1 || num_written != num_read)
    {
        free(buffer);
        close(fd);
        return 0;
    }

    free(buffer);
    close(fd);

    return num_written;
}
