#ifndef _PARAGEM_H_
#define _PARAGEM_H_


#include "linked_int.h"

typedef struct paragem
{
    char *nome; /*Nome da paragem*/
    double latitude, longitude; /*Longitude e latitude*/
    int id; /*Id*/
    int numero_de_carreiras; /*Numero de carreiras associadas*/
    linked_int *carreira_index; /*Guarda o id das carreiras associadas em formato de lista*/

} paragem;

/*Lista usada na tabela hash de forma a evitar colisoes */
typedef struct node_p
{
    paragem *paragem;
    struct node_p *next;

} node_p;

int *add_paragem(int *n_paragens, node_p **hash_paragem, int *locations_p);
void dados_paragem(char *s, node_p *hash_paragem);
void lista_paragens(int n_paragens, node_p **hash_paragem, int *locations_p);
int check_paragem(char *s, node_p *hash_paragem);
char *get_paragem_name(int index, node_p *hash_paragem);
paragem *get_paragem_by_index(int index, node_p *hash_paragem);
paragem *get_paragem(char *s, node_p *hash_paragem);

#endif