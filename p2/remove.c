#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "remove.h"

#include "ligacao.h"
#include "hash.h"
#include "linked_int.h"

/*Remove uma carreira*/
int *remove_carreira(int *locations_c, node_c **hash_carreira, node_p **hash_paragem, int *locations_p)
{

    char *nome_da_carreira = NULL;
    int hash_id, id_paragem;
    carreira *y;
    paragem *z;
    linked_int *lista;

    /*Le o nome da carreira e o seu hash id*/
    nome_da_carreira = lelinha(nome_da_carreira);
    hash_id = hash_function(nome_da_carreira);

    if (hash_carreira[hash_id] == NULL)
    {
        y = NULL;
    }
    else
    {
        y = get_carreira(nome_da_carreira, hash_carreira[hash_id]);
    }

    /*Caso a carreira nao exista*/
    if (y == NULL)
    {
        printf("%s: no such line.\n", nome_da_carreira);
        free(nome_da_carreira);
        return locations_c;
    }

    /*Remove os ids duplicados*/
    y->paragem_index = removeDuplicates(y->paragem_index);
    lista = y->paragem_index;

    while (lista != NULL)
    {   
        /*Remove o id da carreira das paragens associadas a esta*/
        id_paragem = lista->val;
        z = get_paragem_by_index(id_paragem, hash_paragem[locations_p[id_paragem]]);
        z->carreira_index = remove_from_linked_int(y->id, z->carreira_index);
        /*Diminui o numero de carreiras associadas a paragem*/
        z->numero_de_carreiras--;
        lista = lista->next;
    }

    /*Torna o seu locations_c -1, ou seja, informa ao sistema que a carreira foi eliminada e que a deve saltar ao dar print nas carreiras*/
    locations_c[y->id] = -1;
    /*Remove a carreira da tabela*/
    hash_carreira[hash_id] = remove_from_table_c(y->id, hash_carreira[hash_id]);
    free(nome_da_carreira);

    return locations_c;
}

/*Remove uma paragem*/
int *remove_paragem(int *locations_c, node_c **hash_carreira, node_p **hash_paragem, int *locations_p)
{

    char *nome_da_paragem = NULL;
    int hash_id, id_paragem;
    carreira *y;
    paragem *z, *aux;
    linked_int *lista;

    /*Le o nome da paragem e o seu hash id*/
    nome_da_paragem = lelinha(nome_da_paragem);
    hash_id = hash_function(nome_da_paragem);

    if (hash_paragem[hash_id] == NULL)
    {
        z = NULL;
    }
    else
    {
        z = get_paragem(nome_da_paragem, hash_paragem[hash_id]);
    }

    /*Caso a paragem nao exista*/
    if (z == NULL)
    {
        printf("%s: no such stop.\n", nome_da_paragem);
        free(nome_da_paragem);
        return locations_p;
    }

    lista = z->carreira_index;

    while (lista != NULL)
    {   
        /*Remove o id da paragem de todas as carreiras associadas a esta*/
        id_paragem = lista->val;
        y = get_carreira_by_index(id_paragem, hash_carreira[locations_c[id_paragem]]);
        y = remove_all_n(z->id, y);

        /*Caso a carreira fique com apenas 1 paragem o seu preco e tempo voltam a
        0 e a paragem e removida*/
        if (y->numero_de_paragens == 1)
        {
            y->numero_de_paragens = 0;
            y->preco_total = 0;
            y->tempo_total = 0;
            aux = get_paragem_by_index(y->paragem_index->val, hash_paragem[locations_p[y->paragem_index->val]]);
            aux->carreira_index = remove_from_linked_int(y->id, aux->carreira_index);
            aux->numero_de_carreiras--;
            free_lista_f(y->preco);
            free_lista_f(y->tempo);
            free_lista(y->paragem_index);
            y->preco = NULL;
            y->tempo = NULL;
            y->paragem_index = NULL;
        }
        lista = lista->next;
    }

    /*Torna o seu locations_p -1, ou seja, informa ao sistema que a paragem foi eliminada e que a deve saltar ao dar print nas paragens*/
    locations_p[z->id] = -1;
    /*Remove a paragem da tabela*/
    hash_paragem[hash_id] = remove_from_table_p(z->id, hash_paragem[hash_id]);
    free(nome_da_paragem);

    return locations_p;
}
