#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_SIZE 1024

/* Reads a '\n'-terminated line from fd, returning the length of the line and
   pointing *line to the beginning of the line. The pointer is valid until the
   next call to buffer_readline() with the same fd.

   If the underlying call to read() returns -1 or 0, returns the same value,
   with the value of errno intact.

   If fd contains a line longer than BUFFER_SIZE, it will be returned over
   multiple calls to buffer_readline(), with only the last piece terminated
   by '\n'. */
ssize_t buffer_readline(int fd, char **line);

/* As buffer_readline() but with two additional arguments.
   - rsize, if non-NULL, receives the actual amount of data read; and
   - rdata, if non-NULL, receives a pointer to the rsize bytes of new data.
   These arguments are used even when the return value is -1.
   As with line, this pointer is only valid until the next call. */
ssize_t buffer_readline_r(int fd, char **line, size_t *rsize, char **rdata);

/* Deletes and frees any buffer allocated for fd. */
void buffer_clear(int fd);

#endif
