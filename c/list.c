#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define list_prev(l)         ( (l) ? (((list*)(l))->prev):NULL)
#define list_next(l)         ( (l) ? (((list*)(l))->next):NULL)

typedef void* ptr;
typedef const void* constptr;


typedef int (*comparefunc)     (constptr a, constptr b);
typedef int (*comparedatafunc) (constptr a, constptr b);

typedef struct _list list;
struct _list
{
  ptr data;
  list *next;
  list *prev;
};

list* list_alloc                  (void);

void list_free                    (list *l);
void list_free_full               (list *l);

list* list_append                 (list *l, ptr *d);
list* list_prepend                (list *l, ptr *d);
list* list_insert                 (list *l, ptr *d, int pos);
list* list_insert_sorted          (list *l, ptr *d, comparefunc func);
list* list_insert_sorted_with_data(list *l, ptr *d, comparefunc func, ptr ud);
list* list_insert_before          (list *l, list *f, ptr d);

list* list_remove                 (list *l, constptr d);
list* list_remove_all             (list *l, constptr d);
list* list_remove_link            (list *l, list *ln);
list* list_delete_link            (list *l, list *ln);

list* list_reverse                (list *l);

list* list_nth                    (list *l, int n);
list* list_nth_prev               (list *l, int n);
list* list_find                   (list *l, constptr d);

list* list_position               (list *l, list *ln);
list* list_index                  (list *l, constptr d);

list* list_first                  (list *l);
list* list_last                   (list *l);
list* list_length                 (list *l);

list* list_sort                   (list *l, comparefunc func);
list* list_sort_with_data         (list *l, comparefunc func, ptr ud);


list* list_alloc(void) {
  list *l = malloc(sizeof *l);
  return l;
}
