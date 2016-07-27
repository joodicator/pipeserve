#define _GNU_SOURCE

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include "buffer.h"
#include "list.h"

typedef struct {
    int fd;
    char data[BUFFER_SIZE];
    char *end;
    size_t shift;
} buffer_t;

static plist *buffers = NULL;

ssize_t buffer_readline(int fd, char **line) {
    return buffer_readline_r(fd, line, NULL, NULL);
}

ssize_t buffer_readline_r(int fd, char **line, size_t *rsize, char **rdata ) {
    buffer_t *buffer = NULL;
    for (plist *item = buffers; item != NULL; item = item->tail) {
        buffer_t *itemb = (buffer_t *) item->head;
        if (itemb->fd == fd) {
            buffer = itemb;
            break;
        }
    }
    if (buffer == NULL) {
        buffer = malloc(sizeof(buffer_t));
        buffer->fd = fd;
        buffer->end = &buffer->data[0];
        buffer->shift = 0;
        buffers = plist_add(buffers, buffer);
    }

    char *start = buffer->end;
    ssize_t bytes;

    for (;;) {
        size_t dsize = buffer->end - &buffer->data[buffer->shift];
        char *endl = memchr(&buffer->data[buffer->shift], '\n', dsize);
        if (endl != NULL) {
            // A line has been found within the buffer.
            *line = &buffer->data[buffer->shift];
            buffer->shift += bytes = 1 + endl - &buffer->data[buffer->shift];
            break;
        }

        if (buffer->shift) {
            memmove(&buffer->data[0], &buffer->data[buffer->shift],
                    buffer->end - &buffer->data[buffer->shift]);
            buffer->end -= buffer->shift;
            start -= buffer->shift;
            buffer->shift = 0;
        }

        size_t space = BUFFER_SIZE - (buffer->end - &buffer->data[0]);
        if (space == 0) {
            // The buffer is full and no newline has been found.
            *line = &buffer->data[0];
            buffer->shift = bytes = BUFFER_SIZE;
            break;
        }

        // The buffer is not yet full, and no newline has been found.
        bytes = read(buffer->fd, buffer->end, space);
        if (bytes == -1 || bytes == 0) break;
        buffer->end += bytes;
    }

    if (rdata != NULL) *rdata = start;
    if (rsize != NULL) *rsize = buffer->end - start;
    return bytes;
}

void buffer_clear(int fd) {
    plist head = { NULL, buffers };
    for (plist *prev = &head; prev->tail != NULL; prev = prev->tail) {
        buffer_t *buffer = prev->tail->head;
        if (buffer->fd != fd) continue;
        prev->tail = prev->tail->tail;
        free(buffer);
    }
    buffers = head.tail;
}
