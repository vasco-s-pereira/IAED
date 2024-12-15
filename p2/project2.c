/* iaed-23 - ist1103368 - project2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paragem.h"
#include "hash.h"
#include "carreira.h"
#include "ligacao.h"
#include "linked_int.h"
#include "remove.h"

int main()
{   
    /*Conta o numero de paragens e carreiras existentes */
    int c, n_paragens = 0, n_carreiras = 0;
    /*Guarda o local na tabela hash das paragens e das carreiras
    Por exemplo uma carreira com indice 0 estaria na posicao 0 de locations_c e la estaria 
    guardado o numero retornado pela funcao hash*/
    int *locations_p = NULL, *locations_c = NULL;
    /*Tabelas hash que guardam as paragens e as carreiras
    Sao iniciadas pelas funcoes init_hash_p e init_hash_c respetivamente*/
    node_p **hash_paragem = init_hash_p();
    node_c **hash_carreira = init_hash_c();

    /*a variavel c le o input atraves da funcao getchar*/
    while ((c = getchar()) != 'q')
    {
        switch (c)
        {

        case 'p':
            locations_p = add_paragem(&n_paragens, hash_paragem, locations_p);
            break;

        case 'c':
            locations_c = add_carreira(&n_carreiras, hash_carreira, hash_paragem, locations_c, locations_p);
            break;

        case 'l':
            add_ligacao(hash_carreira, hash_paragem);
            break;

        case 'i':
            print_carreiras_associadas(n_paragens, hash_paragem, hash_carreira, locations_p, locations_c);
            break;

        case 'r':
            locations_c = remove_carreira(locations_c, hash_carreira, hash_paragem, locations_p);
            break;

        case 'e':
            locations_p = remove_paragem(locations_c, hash_carreira, hash_paragem, locations_p);
            break;

        case 'a':
        /*Caso o comando seja -a o programa da free a todo o espacao utilizado 
        e de seguida inicializa as tabelas hash novamente*/
            free(locations_c);
            free(locations_p);
            locations_p = NULL;
            locations_c = NULL;
            free_list_p(hash_paragem);
            free_list_c(hash_carreira);
            n_paragens = 0;
            n_carreiras = 0;
            hash_paragem = init_hash_p();
            hash_carreira = init_hash_c();
            break;

        case 'f':
            teste_pratico(locations_c, hash_carreira, hash_paragem,  n_carreiras);
        }
    }

    /*Liberta a memoria*/
    free(locations_p);
    free(locations_c);
    free_list_p(hash_paragem);
    free_list_c(hash_carreira);

    return 0;
}