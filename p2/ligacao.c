#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ligacao.h"

#include "hash.h"

#define MAX_TAMANHO_LINHA BUFSIZ

/*Verifica se as paragens dadas na ligacao equivalem a algum extremo da linha*/
int check_extremos(linked_int *paragem_index, int p1id, int p2id)
{

    linked_int *aux1 = paragem_index, *aux2 = paragem_index;

    while (aux2->next != NULL)
    {
        aux2 = aux2->next;
    }

    if (aux2->val == p1id)
    {

        return 1;
    }

    if (aux1->val == p2id)
    {
        return 2;
    }

    return 0;
}

/*Adiciona a ligacao*/
void check_ligacao(char *carreira_nome, char *origem, char *destino, node_c **hash_carreira, node_p **hash_paragem, double custo, double tempo)
{
    int hash_id, exist, pos;
    carreira *c;
    paragem *p1, *p2;

    /*Verifica se a carreira e as 2 paragens
    existem*/
    hash_id = hash_function(carreira_nome);
    c = get_carreira(carreira_nome, hash_carreira[hash_id]);

    if (c == NULL)
    {
        printf("%s: no such line.\n", carreira_nome);
        free(carreira_nome);
        free(origem);
        free(destino);
        return;
    }

    hash_id = hash_function(origem);
    p1 = get_paragem(origem, hash_paragem[hash_id]);

    if (p1 == NULL)
    {
        printf("%s: no such stop.\n", origem);
        free(carreira_nome);
        free(origem);
        free(destino);
        return;
    }

    hash_id = hash_function(destino);
    p2 = get_paragem(destino, hash_paragem[hash_id]);

    if (p2 == 0)
    {
        printf("%s: no such stop.\n", destino);
        free(carreira_nome);
        free(origem);
        free(destino);
        return;
    }

    /*Caso sejam as primeiras paragens da carreira*/
    if (c->numero_de_paragens == 0)
    {

        c->numero_de_paragens = 2;                                      /*Iguala o numero de paragens da carreira a 2 */
        p1->carreira_index = insert_val_end(c->id, p1->carreira_index); /*Insere as paragens na linked list a carreira*/
        p2->carreira_index = insert_val_end(c->id, p2->carreira_index);
        c->paragem_index = insert_val_end(p1->id, c->paragem_index); /*Iguala a primeira posicao ao index da origem*/
        c->paragem_index = insert_val_end(p2->id, c->paragem_index); /*Iguala a segunda posicao ao index do destino*/
        /*Incrementa o numero de carreiras das paragens origem e destino*/
        p1->numero_de_carreiras++;
        p2->numero_de_carreiras++;
        /*Adiciona o preco e o tempo a carreira*/
        c->preco_total = c->preco_total + custo;
        c->tempo_total = c->tempo_total + tempo;
        /*Insere os valores nas linked list do preco e do tempo*/
        c->preco = insert_val_begin_f(custo, c->preco);
        c->tempo = insert_val_begin_f(tempo, c->tempo);

        /*Caso as duas paragens sejam iguais o numero
        de carreiras associadas a paragem e diminuido por 1*/
        if (p1 == p2)
        {
            p1->numero_de_carreiras--;
        }
        free(carreira_nome);
        free(origem);
        free(destino);

        return;
    }

    exist = check_extremos(c->paragem_index, p1->id, p2->id);

    switch (exist)
    {
    case 0:
        /*Caso em que nenhumas das paragens e um extremo da carreira*/
        printf("link cannot be associated with bus line.\n");
        break;

    /*Caso em que a primeira paragem e o extremo direito da linha*/
    case 1:
        /*Guarda a posicao da paragem na carreira caso estas
        ja estejam associadas previamente*/
        pos = lookup(p2->id, c->paragem_index);
        /*Adiciona o custo e o tempo*/
        c->preco_total = c->preco_total + custo;
        c->tempo_total = c->tempo_total + tempo;
        /*Insere o preco e o tempo nas linked lists*/
        c->preco = insert_val_end_f(custo, c->preco);
        c->tempo = insert_val_end_f(tempo, c->tempo);
        /*Incrementa o numero de paragens associadas*/
        c->numero_de_paragens++;
        /*Insere a nova paragem no final da linked list*/
        c->paragem_index = insert_val_end(p2->id, c->paragem_index);

        /*Caso a paragem nao esteja ja associada a carreira
        o id desta e adicionado a linked lista da paragem
        e o seu numero de carreira e aumentado 1*/
        if (pos == -1)
        {
            p2->carreira_index = insert_val_end(c->id, p2->carreira_index);
            p2->numero_de_carreiras++;
        }

        break;
    /*Caso em que a segunda paragem e o extremo esquerdo da linha*/
    case 2:
        /*Guarda a posicao da paragem na carreira caso estas
            ja estejam associadas previamente*/
        pos = lookup(p1->id, c->paragem_index);
        /*Adiciona o custo e o tempo*/
        c->preco_total = c->preco_total + custo;
        c->tempo_total = c->tempo_total + tempo;
        /*Insere o preco e o tempo nas linked lists*/
        c->preco = insert_val_begin_f(custo, c->preco);
        c->tempo = insert_val_begin_f(tempo, c->tempo);
        /*Incrementa o numero de paragens associadas*/
        c->numero_de_paragens++;
        /*Insere a nova paragem no principio da linked list*/
        c->paragem_index = insert_val_begin(p1->id, c->paragem_index);
        /*Caso a paragem nao esteja ja associada a carreira
        o id desta e adicionado a linked lista da paragem
        e o seu numero de carreira e aumentado 1*/
        if (pos == -1)
        {

            p1->carreira_index = insert_val_end(c->id, p1->carreira_index);
            p1->numero_de_carreiras++;
        }
        break;
    }

    /*Caso as duas paragens sejam iguais o numero
    de carreiras associadas a paragem e diminuido por 1*/
    if (p1 == p2)
    {
        p1->numero_de_carreiras--;
    }

    free(carreira_nome);
    free(origem);
    free(destino);
}

/*Le o nome da carreira, das 2 paragens, do custo e do tempo*/
void add_ligacao(node_c **hash_carreira, node_p **hash_paragem)
{

    int unused __attribute__((unused));
    char *carreira = NULL, *origem = NULL, *destino = NULL;
    double custo, tempo;

    carreira = lelinha(carreira);
    origem = lelinha(origem);
    destino = lelinha(destino);

    unused = scanf("%lf %lf", &custo, &tempo);

    if (custo < 0 || tempo < 0)
    {
        printf("negative cost or duration.\n");
        free(carreira);
        free(origem);
        free(destino);
        return;
    }

    check_ligacao(carreira, origem, destino, hash_carreira, hash_paragem, custo, tempo);
}

/*Da print as carreiras associadas a todas as paragens com pelo menos 2 carreiras associadas*/
void print_carreiras_associadas(int n_paragens, node_p **hash_paragem, node_c **hash_carreira, int *locations_p, int *locations_c)
{
    int i, j;
    char *nome_da_paragem, **nomes_das_carreiras_associadas;
    paragem *y;

    for (i = 0; i < n_paragens; i++)
    {
        if (locations_p[i] != -1)
        {
            nome_da_paragem = get_paragem_name(i, hash_paragem[locations_p[i]]);
            y = get_paragem(nome_da_paragem, hash_paragem[locations_p[i]]);
            if (y->numero_de_carreiras > 1)
            {
                printf("%s %i:", y->nome, y->numero_de_carreiras);
                nomes_das_carreiras_associadas = (char **)malloc(sizeof(char *) * y->numero_de_carreiras);
                nomes_das_carreiras_associadas = sort_carreiras(y->numero_de_carreiras, y->carreira_index, hash_carreira, locations_c);

                for (j = 0; j < y->numero_de_carreiras; j++)
                {
                    printf(" %s", nomes_das_carreiras_associadas[j]);
                    free(nomes_das_carreiras_associadas[j]);
                }

                free(nomes_das_carreiras_associadas);
                printf("\n");
            }
        }
    }
}

/*Da sort ao nome das carreiras (Bubble Sort)*/
char **sort_carreiras(int numero_de_carreiras, linked_int *carreira_index, node_c **hash_carreira, int *locations_c)
{

    char **nomes_das_carreiras_associadas = (char **)malloc(sizeof(char *) * numero_de_carreiras);
    int i, j;
    char *aux;
    linked_int *indexes = carreira_index;

    for (i = 0; i < numero_de_carreiras; i++)
    {

        aux = get_carreira_nome(indexes->val, hash_carreira[locations_c[indexes->val]]);

        indexes = indexes->next;
        nomes_das_carreiras_associadas[i] = (char *)malloc(sizeof(char) * (strlen(aux) + 1));
        strcpy(nomes_das_carreiras_associadas[i], aux);
    }

    for (j = 0; j < numero_de_carreiras; j++)
    {
        for (i = 0; i < numero_de_carreiras - 1 - j; i++)
        {
            if (strcmp(nomes_das_carreiras_associadas[i], nomes_das_carreiras_associadas[i + 1]) > 0)
            {
                aux = nomes_das_carreiras_associadas[i];
                nomes_das_carreiras_associadas[i] = nomes_das_carreiras_associadas[i + 1];
                nomes_das_carreiras_associadas[i + 1] = aux;
            }
        }
    }

    return nomes_das_carreiras_associadas;
}

/*Funcao para ler a linha*/
char *lelinha(char *ret)
{

    int c, length = 0;
    char s[MAX_TAMANHO_LINHA];

    c = getchar();

    if (c == ' ')
    {
        c = getchar();
    }

    if (c == '"')
    {

        while ((c = getchar()) != '"')
        {
            s[length++] = c;
        }

        c = getchar();
    }
    else
    {
        while (c != ' ' && c != '\n')
        {
            s[length++] = c;
            c = getchar();
        }
    }

    s[length] = '\0';
    ret = (char *)malloc(sizeof(char) * (length + 1));
    strcpy(ret, s);

    return ret;
}
