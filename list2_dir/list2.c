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

int is_empty(Node *list)
{
    if (list == NULL)
    {
        puts("nullptr");
        return 1;
    }

    return (list->next == list) && (list->prev == list);
}

void print(Node *list)
{
    if (is_empty(list))
    {
        puts("Empty list");
        return;
    }

    for (Node *p = list->next; p != list; p = p->next)
        printf("%d ", p->data);
    puts("");
}

void print_back(Node *list)
{
    if (is_empty(list))
    {
        puts("Empty list");
        return;
    }

    for (Node *p = list->prev; p != list; p = p->prev)
        printf("%d", p->data);
    puts("");
}

void print_dbg(Node *list)
{
    if (is_empty(list))
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

void insert_after(Node *left, Node *new)
{
    Node *right = left->next;
    new->prev = left;
    new->next = right;
    left->next = new;
    right->prev = new;
}

void insert_before(Node *right, Node *new)
{
    insert_after(right->prev, new);
}

void init(Node *list)
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

void remove_after(Node *left)
{
    list_remove(left->next);
}

void remove_before(Node *right)
{
    list_remove(right->prev);
}

Node *push_front(Node *list, elem_t elem)
{
    Node *new_note = calloc(1, sizeof(Node));

    new_note->data = elem;
    insert_after(list, new_note);

    return new_note;
}

Node *push_back(Node *list, elem_t elem)
{
    return push_front(list->prev, elem);
}

elem_t list_delete(Node *list)
{
    if (list == NULL)
    {
        puts("nullptr");
        return 0;
    }

    elem_t res = list->data;
    free(list);

    return res;
}

elem_t pop_front(Node *list)
{
    return list_delete(list->next);
}

elem_t pop_back(Node *list)
{
    return list_delete(list->prev);
}

void clear(Node *list)
{
    while (!is_empty(list))
        pop_front(list);
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
