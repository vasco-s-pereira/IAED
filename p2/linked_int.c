#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ligacao.h"

#include "linked_int.h"

/*NOTA: as funcoes com um nome igual mas com um _f
fazem as mesma coisa que a sua contra parte mas com uma variavel double e nao int*/

/*Cria um novo elemento na lista*/
linked_int *NEW(int valor)
{

    linked_int *x = (linked_int *)malloc(sizeof(linked_int));
    x->val = valor;
    x->next = NULL;
    return x;
}

linked_double *NEW_f(double valor)
{
    linked_double *x = (linked_double *)malloc(sizeof(linked_double));
    x->val = valor;
    x->next = NULL;
    return x;
}

/*Insere um novo valor no fim da lista*/
linked_int *insert_val_end(int valor, linked_int *head)
{

    linked_int *x;
    if (head == NULL)
        return NEW(valor);
    for (x = head; x->next != NULL; x = x->next)
        ;
    x->next = NEW(valor);
    return head;
}

/*Insere um novo valor no principio da lista*/
linked_int *insert_val_begin(int valor, linked_int *head)
{
    linked_int *x = NEW(valor);
    x->next = head;
    return x;
}

linked_double *insert_val_end_f(double valor, linked_double *head)
{
    linked_double *x;
    if (head == NULL)
        return NEW_f(valor);
    for (x = head; x->next != NULL; x = x->next)
        ;
    x->next = NEW_f(valor);
    return head;
}

linked_double *insert_val_begin_f(double valor, linked_double *head)
{
    linked_double *x = NEW_f(valor);
    x->next = head;
    return x;
}

/*Da print ao conteudo da lista*/
void print_lista(linked_int *lista)
{

    linked_int *aux = lista;

    while (aux != NULL)
    {
        printf("%i\n", aux->val);
        aux = aux->next;
    }
}

/*Da free a lista*/
void free_lista(linked_int *lista)
{
    linked_int *tmp;

    while (lista != NULL)
    {
        tmp = lista;
        lista = lista->next;
        free(tmp);
    }
}

void free_lista_f(linked_double *lista)
{
    linked_double *tmp;

    while (lista != NULL)
    {
        tmp = lista;
        lista = lista->next;
        free(tmp);
    }
}

/*Verifica se um elemento index pertence a lista*/
int lookup(int index, linked_int *lista)
{

    int pos = -1, counter = 0;
    linked_int *y = lista;

    while (y != NULL)
    {
        if (y->val == index)
        {
            pos = counter;
            break;
        }

        counter++;
        y = y->next;
    }

    return pos;
}

/*Remove todos os duplicados de uma lista*/
linked_int *removeDuplicates(linked_int *start)
{
    linked_int *ptr1, *ptr2, *dup;
    ptr1 = start;

    while (ptr1 != NULL && ptr1->next != NULL)
    {
        ptr2 = ptr1;

        while (ptr2->next != NULL)
        {
            if (ptr1->val == ptr2->next->val)
            {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(dup);
            }
            else
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }

    return start;
}

/*Remove o valor de uma lista*/
linked_int *remove_from_linked_int(int valor, linked_int *lista)
{
    linked_int *t, *prev;
    for (t = lista, prev = NULL; t != NULL;
         prev = t, t = t->next)
    {
        if (t->val == valor)
        {
            if (t == lista)
                lista = t->next;
            else
                prev->next = t->next;

            free(t);
            break;
        }
    }

    return lista;
}
