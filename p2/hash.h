#ifndef _HASH_H_
#define _HASH_H_

#define HASH_SIZE 1117

#include "paragem.h"
#include "carreira.h"

int hash_function(char *s); /*Funcao hash utilizada*/
node_c *remove_from_table_c(int index, node_c *hash_carreira);
node_p *remove_from_table_p(int index, node_p *hash_paragem);
node_p **insert_into_table_p(int index, paragem *x, node_p **hash_paragem);   /**Encontra a uktima posicao da linked list respetiva da posicao da tabela de paragens*/
node_c **insert_into_table_c(int index, carreira *x, node_c **hash_carreira); /*Encontra a uktima posicao da linked list respetiva da posicao da tabela de carreiras*/
node_p *insert_new_p_value(node_p *head, paragem *x);                         /*Insere a nova paragem*/
node_c *insert_new_c_value(node_c *head, carreira *x);                        /*Insere a nova carreira*/
void free_list_p(node_p **hash_paragem);
void free_list_c(node_c **hash_carreira);
node_p **init_hash_p();
node_c **init_hash_c();

#endif