#ifndef LIST_H
#define LIST_H

#define LIST_H_INSTANCE(LIST, VALUE) \
    typedef struct LIST##_s { \
        VALUE head; \
        struct LIST##_s *tail; \
    } LIST; \
    \
    LIST *LIST##_add(LIST *, VALUE); \
    LIST *LIST##_pop(LIST *); \
    LIST *LIST##_del(LIST *, VALUE);

LIST_H_INSTANCE(ilist, int)
LIST_H_INSTANCE(plist, void *)

#endif
