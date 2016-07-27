#include <stdlib.h>
#include "list.h"

#define LIST_C_INSTANCE(LIST, VALUE) \
    LIST *LIST##_add(LIST *list, VALUE value) { \
        LIST *item = malloc(sizeof(LIST)); \
        item->head = value; \
        item->tail = list; \
        return item; \
    } \
    \
    LIST *LIST##_pop(LIST *list) { \
        LIST *tail = list->tail; \
        free(list); \
        return tail; \
    } \
    \
    LIST *LIST##_del(LIST *list, VALUE value) { \
        LIST head = { 0, list }; \
        for (LIST *prev = &head; prev->tail != NULL; prev = prev->tail) { \
            if (prev->tail->head == value) { \
                prev->tail = LIST##_pop(prev->tail); \
                break; \
            } \
        } \
        return head.tail; \
    }

LIST_C_INSTANCE(ilist, int)
LIST_C_INSTANCE(plist, void *)
