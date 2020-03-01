// list2.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int elem_t;

typedef struct Node
{
    elem_t data;
    struct Node *next;
    struct Node *prev;
} Node;

int list_is_empty(Node *list)
{
    if (list == NULL)
    {
        puts("nullptr");
        return 1;
    }

    return (list->next == list) && (list->prev == list);
}

void list_print(Node *list)
{
    if (list_is_empty(list))
    {
        puts("Empty list");
        return;
    }

    for (Node *p = list->next; p != list; p = p->next)
        printf("%d ", p->data);
    puts("");
}

void list_print_back(Node *list)
{
    if (list_is_empty(list))
    {
        puts("Empty list");
        return;
    }

    for (Node *p = list->prev; p != list; p = p->prev)
        printf("%d", p->data);
    puts("");
}

void list_print_dbg(Node *list)
{
    if (list_is_empty(list))
    {
        puts("Empty list");
        return;
    }

    puts("------------------\n");
    printf("list: prev = %p || next = %p", list->prev, list->next);

    for (Node *p = list->next; p != list; p = p->next)
        printf("%d || prev = %p || next = %p\n", p->data, p->prev, p->next);
    puts("");
}

void list_insert(Node *left, Node *new)
{
    Node *right = left->next;
    new->prev = left;
    new->next = right;
    left->next = new;
    right->prev = new;
}

void list_insert_before(Node *right, Node *new)
{
    list_insert(right->prev, new);
}

void list_init(Node *list)
{
    if (list != NULL)
    {
        list->prev = list;
        list->next = list;
    }
}

void list_remove(Node *node)
{
    Node *left = node->prev;
    Node *right = node->next;

    left->next = right;
    right->prev = left;
}

void list_remove_after(Node *left)
{
    list_remove(left->next);
}

void list_remove_before(Node *right)
{
    list_remove(right->prev);
}

Node *list_push_front(Node *list, elem_t elem)
{
    Node *new_note = calloc(1, sizeof(Node));

    new_note->data = elem;
    list_insert(list, new_note);

    return new_note;
}

Node *list_push_back(Node *list, elem_t elem)
{
    return list_push_front(list->prev, elem);
}

elem_t list_delete(Node *list)
{
    if (list == NULL)
    {
        puts("nullptr");
        return 0;
    }

    elem_t res = list->data;
    list->next->prev = list->prev;
    list->prev->next = list->next;

    free(list);

    return res;
}

elem_t list_pop_front(Node *list)
{
    return list_delete(list->next);
}

elem_t list_pop_back(Node *list)
{
    return list_delete(list->prev);
}

void list_clear(Node *list)
{
    while (!list_is_empty(list))
        list_pop_front(list);
}

void print_it(elem_t elem, void *arg)
{
    fprintf((FILE *)arg, "%d", elem);
}

void foreach (Node *list, void (*func)(elem_t, void *), void *arg)
{
    for (Node *p = list->next; p != list; p = p->next)
        func(p->data, arg);
}

void print_to_file(Node *list, FILE *fout)
{
    foreach (list, print_it, fout);
    fputs("\n", fout);
}

void sum_it(elem_t elem, void *arg)
{
    elem_t *res = (elem_t *)arg;
    *res += elem;
}

elem_t list_sum(Node *list)
{
    elem_t res = 0;
    foreach(list, sum_it, &res);

    return res;
}

int main()
{
    struct Node x[10];
	struct Node * a = malloc(sizeof(struct Node));
	struct Node * b = malloc(sizeof(struct Node));

	list_init(a);
	list_init(b);
	// End of test 1
	
	for(int i=0; i<10; i++) {
		x[i].data = i;
		list_insert(a, &x[i]);
	}
	list_print(a);   // 9 8 7 6 5 4 3 2 1 0 
	// End of test 2
	
	list_remove(&x[5]);
	list_print(a);
	list_remove(&x[0]);
	list_print(a);
	list_remove(&x[9]);
	list_print(a);
	// End of test 3
	
	list_insert_before(a, &x[0]);
	list_print(a);
	list_insert(a, &x[9]);
	list_print(a);
	list_insert(&x[6], &x[5]);
	list_print(a);
	// End of test 4
	
	while(!list_is_empty(a))
		list_remove(a->next);
	// End of test 5

	for(int i=0; i<10; i++)
		list_push_back(a, i);
	list_print(a);
	// End of test 6
	
	for(int i=0; i<10; i++)
		list_push_front(b, list_pop_back(a));
	list_print(b);
	// End of test 7
	
	for(int i=0; i<10; i++) {
		list_push_front(a, i);
		list_pop_front(b);
	}
	list_print(a);
	// End of test 8

	for(int i=0; i<10; i++)
		list_push_back(b, list_pop_front(a));
	list_print(b);
	// End of test 9
	
	list_clear(a);
	list_clear(b);
	// End of test 10

    list_delete(a);
    list_delete(b);
    
    return 0;
} 