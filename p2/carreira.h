#ifndef _CARREIRA_H_
#define _CARREIRA_H_

#include "paragem.h"
#include "linked_int.h"

typedef struct carreira
{
    char *nome; /*Nome*/
    double tempo_total; /*Preco e tempo total*/
    double preco_total;
    linked_double *tempo; /*Linked lists do tempo e da\o preco*/
    linked_double *preco;
    int id; /*Id*/
    int numero_de_paragens; /*Numero de paragens associadas*/
    linked_int *paragem_index; /*Guarda o id das paragens associadas em formato de lista*/

} carreira;

/*Lista usada na tabela hash de forma a evitar colisoes */
typedef struct node_c
{
    carreira *carreira;
    struct node_c *next;

} node_c;

int *add_carreira(int *n_carreiras, node_c **hash_carreira, node_p **hash_paragem, int *locations_c, int *locations_p);
int check_carreira_exist(char *s, node_c *hash_carreira);
void print_paragens_associadas(carreira z, int *locations_p, node_p **hash_paragem);
void print_paragens_associadas_reverse(carreira z, int *locations_p, node_p **hash_paragem);
void print_carreiras(int n_carreiras, node_c **hash_carreira, node_p **hash_paragem, int *locations_c, int *locations_p);
carreira *get_carreira(char *s, node_c *hash_carreira);
carreira *get_carreira_by_index(int index, node_c *hash_carreira);
carreira *remove_all_n(int index, carreira *y);
char *get_carreira_nome(int index, node_c *hash_carreira);
void teste_pratico(int *locations_c, node_c **hash_carreira, node_p **hash_paragem, int n_carreiras);

#endif
