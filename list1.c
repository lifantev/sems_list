// list1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <stdbool.h>

typedef int elem_t;

typedef struct Node
{
    elem_t data;
    struct Node* next;
} Node;

void print(Node** plist)
{
    for(Node *p = plist; p != NULL; p = p->next)
        printf("%d ", p->data);
    puts("");
}

void push(Node** plist, elem_t elem)
{
    if(is_empty(*plist))
        puts("Empty list");
    
    Node* new_node = calloc(1, sizeof(Node));
    new_node->next = *plist;
    new_node->data = elem;
    *plist = new_node; 
}

elem_t pop(Node** plist)
{
    if(*plist == NULL)
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

int is_empty(Node* list)
{
    return list == NULL;
}

int main() 
{
    Node** list = NULL;
    
    return 0;
}
