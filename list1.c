// list1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int elem_t;

typedef struct Node
{
    elem_t data;
    struct Node *next;
} Node;

int is_empty(Node *list)
{
    return list == NULL;
}

void print(Node *list)
{
    if (is_empty(list))
    {
        puts("Empty list");
        return;
    }

    for (Node *p = list; p != NULL; p = p->next)
        printf("%d ", p->data);
    puts("");
}

void push(Node **plist, elem_t elem)
{
    Node *new_node = calloc(1, sizeof(Node));
    new_node->next = *plist;
    new_node->data = elem;
    *plist = new_node;
}

elem_t pop(Node **plist)
{
    if (*plist == NULL)
    {
        puts("Empty list");
        return 0;
    }

    Node *p = *plist;
    elem_t res = p->data;
    *plist = p->next;
    free(p);

    return res;
}

elem_t get(Node *list)
{
    return list->data;
}

int size(Node *list)
{
    int size = 0;

    while (list != NULL)
    {
        size++;
        list = list->next;
    }

    return size;
}

void clear(Node **plist)
{
    Node *p = *plist;

    while (*plist != NULL)
    {
        Node *p = *plist;
        *plist = p->next;
        free(p);
    }
}

#ifdef MAIN_LIST1
int main()
{
    Node *list = NULL;
    push(&list, 1);
    push(&list, 12);
    push(&list, 13);
    push(&list, 14);
    push(&list, 15);
    push(&list, 16);
    print(list);
    printf("%d", size(list));
    int x = pop(&list);
    print(list);
    x = pop(&list);
    x = pop(&list);
    x = pop(&list);
    x = pop(&list);
    x = pop(&list);
    print(list);

    x = pop(&list);
    print(list);
    push(&list, 21);
    push(&list, 21);

    print(list);

    clear(&list);

    x = pop(&list);

    push(&list, 31);

    print(list);

    clear(&list);

    return 0;
}
#endif // MAIN_LIST1