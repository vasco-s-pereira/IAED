#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/*Tamanho da tabela. Numero primo para evitar colisoes*/
#define HASH_SIZE 1117


int hash_function(char *s) /*Funcao hash*/
{

    int h = 0, a = 127;
    for (; *s != '\0'; s++)
    {
        h = (a * h + *s) % HASH_SIZE;
    }
    return h;
}

node_p **init_hash_p() /*Inicializa a tabela hash de paragens*/
{
    int i;

    node_p **hashtable = (node_p **)malloc(HASH_SIZE * sizeof(node_p *));

    for (i = 0; i < HASH_SIZE; i++)
    {
        hashtable[i] = NULL;
    }

    return hashtable;
}

node_c **init_hash_c() /*Inicializa a tabela hash de carreiras*/
{
    int i;

    node_c **hashtable = (node_c **)malloc(HASH_SIZE * sizeof(node_c *)); /*O calloc e usado de forma a todos valores serem inicializados a NULL*/

    for (i = 0; i < HASH_SIZE; i++)
    {
        hashtable[i] = NULL;
    }

    if (hashtable == NULL)
    {
        printf("No memory.\n");
        exit(0);
    }
    return hashtable;
}

/*Insere uma nova paragem na lista*/
node_p *insert_new_p_value(node_p *head, paragem *x)
{
    node_p *y = (node_p *)malloc(sizeof(node_p));
    node_p *current;
    y->paragem = x;
    y->next = NULL;

    if (head == NULL)
    {
        head = y;
    }
    else
    {
        current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = y;
    }

    return head;
}

/*Insere uma nova carreira na lista*/
node_c *insert_new_c_value(node_c *head, carreira *x)
{
    node_c *y = (node_c *)malloc(sizeof(node_c));
    node_c *current;
    y->carreira = x;
    y->next = NULL;

    if (head == NULL)
    {
        head = y;
    }
    else
    {
        current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = y;
    }

    return head;
}

/*Da free a tabela de paragens*/
void free_list_p(node_p **hash_paragem)
{
    int i;
    node_p *current, *aux;

    for (i = 0; i < HASH_SIZE; i++)
    {
        current = hash_paragem[i];

        while (current != NULL)
        {

            aux = current;
            free(current->paragem->nome);
            free_lista(current->paragem->carreira_index);
            free(current->paragem);
            current = current->next;
            free(aux);
        }
    }

    free(hash_paragem);
}

/*Da free a tabela de carreiras*/
void free_list_c(node_c **hash_carreira)
{
    int i;
    node_c *current, *aux;

    for (i = 0; i < HASH_SIZE; i++)
    {
        current = hash_carreira[i];

        while (current != NULL)
        {

            aux = current;
            free(current->carreira->nome);
            free_lista(current->carreira->paragem_index);
            free_lista_f(current->carreira->tempo);
            free_lista_f(current->carreira->preco);
            free(current->carreira);
            current = current->next;
            free(aux);
        }
    }

    free(hash_carreira);
}

/*Aloca espaco para uma nova carreira na tabela de listas*/
node_c **insert_into_table_c(int index, carreira *x, node_c **hash_carreira)
{
    node_c *y;
    if (hash_carreira[index] == NULL)
    {
        hash_carreira[index] = malloc(sizeof(node_c *));
        y = NULL;
    }
    else
    {
        y = hash_carreira[index];
    }

    hash_carreira[index] = insert_new_c_value(y, x);

    return hash_carreira;
}

/*Aloca espaco para uma nova paragem na tabela de listas*/
node_p **insert_into_table_p(int index, paragem *x, node_p **hash_paragem)
{
    node_p *y;
    if (hash_paragem[index] == NULL)
    {
        hash_paragem[index] = malloc(sizeof(node_p *));
        y = NULL;
    }
    else
    {
        y = hash_paragem[index];
    }

    hash_paragem[index] = insert_new_p_value(y, x);

    return hash_paragem;
}

/*Remove uma carreira da tabela de listas*/
node_c *remove_from_table_c(int index, node_c *hash_carreira)
{
    node_c *y, *aux;

    for (y = hash_carreira, aux = NULL; y != NULL;
         aux = y, y = y->next)
    {
        if (index == y->carreira->id)
        {
            if (y == hash_carreira)
            {
                hash_carreira = y->next;
            }
            else
            {
                aux->next = y->next;
            }
            break;
        }
    }

    y->next = NULL;
    free(y->carreira->nome);
    free_lista(y->carreira->paragem_index);
    free_lista_f(y->carreira->preco);
    free_lista_f(y->carreira->tempo);
    free(y->carreira);
    free(y);
    

    return hash_carreira;
}

/*Remove uma paragem da tabela de listas*/
node_p *remove_from_table_p(int index, node_p *hash_paragem)
{
    node_p *y, *aux;

    for (y = hash_paragem, aux = NULL; y != NULL;
         aux = y, y = y->next)
    {
        if (index == y->paragem->id)
        {
            if (y == hash_paragem)
            {
                hash_paragem = y->next;
            }
            else
            {
                aux->next = y->next;
            }
            break;
        }
    }

    y->next = NULL;
    free(y->paragem->nome);
    free_lista(y->paragem->carreira_index);
    free(y->paragem);
    free(y);
    

    return hash_paragem;
}