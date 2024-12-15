#ifndef _LINKEDINT_H_
#define _LINKEDINT_H_


typedef struct linked_int
{
    int val;
    struct linked_int *next;
}linked_int;

typedef struct linked_double
{
    double val;
    struct linked_double *next;
}linked_double;

linked_int *insert_val_end(int valor, linked_int *lista);
linked_int *insert_val_begin(int valor, linked_int *lista);
linked_double *insert_val_end_f(double valor, linked_double *head);
linked_double *insert_val_begin_f(double valor, linked_double *head);
linked_int *NEW(int valor);
linked_double *NEW_f(double valor);
void free_lista(linked_int *lista);
void free_lista_f(linked_double *lista);
void print_lista(linked_int *lista);
int lookup(int index, linked_int *lista);
linked_int *removeDuplicates(linked_int* start);
linked_int *remove_from_linked_int(int valor, linked_int *lista);

#endif
