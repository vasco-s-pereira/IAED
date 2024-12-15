#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "paragem.h"
#include "hash.h"

#define MAX_TAMANHO_LINHA BUFSIZ

/*Retorna o nome de uma paragem atraves do seu id*/
char *get_paragem_name(int index, node_p *hash_paragem)
{

    node_p *x = hash_paragem;

    while (x->paragem->id != index)
    {
        x = x->next;
    }

    return x->paragem->nome;
}

/*Verifica se uma paragem existe ou nao
Caso exista retorna 1 e caso contrario retorna 0*/
int check_paragem(char *s, node_p *hash_paragem)
{
    node_p *y;

    y = hash_paragem;

    while (y != NULL)
    {
        if (strcmp(y->paragem->nome, s) == 0)
        {
            return 1;
        }
        y = y->next;
    }

    return 0;
}

/*Da print da latitude e da longitude de uma paragem*/
void dados_paragem(char *s, node_p *hash_paragem)
{
    node_p *y = hash_paragem;

    while (strcmp(y->paragem->nome, s) != 0)
    {
        y = y->next;
    }

    printf("%16.12f %16.12f\n", y->paragem->latitude, y->paragem->longitude);
}

/*Lista todas as paragens e os seus dados*/
void lista_paragens(int n_paragens, node_p **hash_paragem, int *locations_p)
{
    int i;
    node_p *y;
    for (i = 0; i < n_paragens; i++)
    {
        if (locations_p[i] != -1) /*Quando uma paragem e removida o seu lugar no array passa a ser -1*/
        {
            y = hash_paragem[locations_p[i]];
            while (y->paragem->id != i)
            {
                y = y->next;
            }

            printf("%s: %16.12f %16.12f %d\n", y->paragem->nome, y->paragem->latitude,
                   y->paragem->longitude, y->paragem->numero_de_carreiras);
        }
    }
}

/*Decide o que fazer apos o comando -p*/
int *add_paragem(int *n_paragens, node_p **hash_paragem, int *locations_p)
{
    int c, length = 0, hash_id, unused __attribute__((unused)), exist = 0;
    paragem *x;
    char s[MAX_TAMANHO_LINHA];

    c = getchar();

    /*Caso o comando seja apenas p lista as paragens*/
    if (c == '\n')
    {
        lista_paragens(*n_paragens, hash_paragem, locations_p); /*Lista as paragens todas*/
        return locations_p;
    }

    c = getchar();

    x = (paragem *)malloc(sizeof(paragem));

    /*Le o nome da paragem e guarda*/
    if (c == '"')
    {
        while ((c = getchar()) != '"')
        {
            s[length++] = c;
        }

        s[length] = '\0';
        x->nome = (char *)malloc(sizeof(char) * (length + 1));
        strcpy(x->nome, s);
        c = getchar();
    }
    else
    {
        while (c != ' ' && c != '\n')
        {
            s[length++] = c;
            c = getchar();
        }

        s[length] = '\0';
        x->nome = (char *)malloc(sizeof(char) * (length + 1));
        strcpy(x->nome, s);
    }

    /*Caso o comando seja -p nome de paragem o programa
    verifica se a paragem existe ou nao e , caso exista,
    escreve a sua latitude e longitude*/
    if (c == '\n')
    {
        hash_id = hash_function(x->nome);
        exist = check_paragem(x->nome, hash_paragem[hash_id]);

        if (exist == 1)
        {
            dados_paragem(x->nome, hash_paragem[hash_id]);
        }

        else
        {
            printf("%s: no such stop.\n", x->nome);
        }

        free(x->nome);
        free(x);
        return locations_p;
    }
    /*Le a longitude e a latitude e inicializa os valores da nova paragem*/
    unused = scanf("%lf %lf", &x->latitude, &x->longitude); /*Guarda a latitude e a longitude*/
    if (x->latitude < -90 || x->latitude > 90 || x->longitude < -180 || x->longitude > 180)
    {
        printf("invalid location.\n");
        free(x->nome);
        free(x);
        return locations_p;
    }
    x->numero_de_carreiras = 0; /*Iguala o numero de carreiras a 0*/
    x->carreira_index = NULL;   /*Iguala o id ao numero de paragens total atual*/
    x->id = *n_paragens;

    /*Guarda o id da tabela hash para a string e verifica se ja existe ou nao*/
    hash_id = hash_function(x->nome);
    exist = check_paragem(x->nome, hash_paragem[hash_id]);

    /*Caso exista da free da memoria alocada e da erro*/
    if (exist == 1)
    {

        printf("%s: stop already exists.\n", x->nome);
        free(x->nome);
        free(x);
        return locations_p;
    }
    /*Caso contrario insere a nova paragem na tabela hash*/
    hash_paragem = insert_into_table_p(hash_id, x, hash_paragem);

    /*Guarda o id da tabela hash no array locations_p
    na posicao igual ao id da paragem e em seguida incrementa o
    numero de paragens */
    if ((*n_paragens)++ == 0)
    {
        locations_p = (int *)malloc(sizeof(int));
    }
    else
    {
        locations_p = (int *)realloc(locations_p, sizeof(int) * (*n_paragens));
    }

    /*Caso a alocacao falhe*/
    if (locations_p == NULL)
    {
        printf("No memory.");
        exit(0);
    }

    locations_p[*n_paragens - 1] = hash_id;

    /*Retorna o array com os ids da tabela*/
    return locations_p;
}

/*Retorna uma paragem na tabela atraves do seu id*/
paragem *get_paragem_by_index(int index, node_p *hash_paragem)
{

    node_p *z = hash_paragem;

    while (z != NULL)
    {

        if (z->paragem->id == index)
        {
            return z->paragem;
        }

        z = z->next;
    }

    return NULL;
}

/*Retorna uma paragem na tabela atraves do seu nome*/
paragem *get_paragem(char *s, node_p *hash_paragem)
{

    node_p *z = hash_paragem;

    while (z != NULL)
    {

        if (strcmp(z->paragem->nome, s) == 0)
        {
            return z->paragem;
        }

        z = z->next;
    }

    return NULL;
}