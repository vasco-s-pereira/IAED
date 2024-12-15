#ifndef _LIGACAO_H_
#define _LIGACAO_H_

#include "carreira.h"
#include "paragem.h"
#include "linked_int.h"

void add_ligacao(node_c **hash_carreira, node_p **hash_paragem);
char *lelinha(char* s);
void check_ligacao(char *carreira, char *origem, char *destino, node_c **hash_carreira, node_p **hash_paragem, double custo, double tempo);
int check_extremos(linked_int *paragem_index, int p1id, int p2id);
void print_carreiras_associadas(int n_paragens, node_p **hash_paragem, node_c **hash_carreira, int *locations_p, int *locations_c);
char **sort_carreiras(int numero_de_carreiras, linked_int *carreira_index, node_c **hash_carreira, int *locations_c);


#endif
