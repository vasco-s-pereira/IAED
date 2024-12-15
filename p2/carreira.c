#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "carreira.h"
#include "hash.h"

#define MAX_TAMANHO_LINHA BUFSIZ

/*Da print as paragens de uma carreira de ordem inversa*/
void print_paragens_associadas_reverse(carreira z, int *locations_p, node_p **hash_paragem)
{
    int i, j;
    linked_int *aux;

    for (i = 0; i < z.numero_de_paragens; i++)
    {

        aux = z.paragem_index;

        for (j = 0; j < z.numero_de_paragens - 1 - i; j++)
        {
            aux = aux->next;
        }

        printf("%s", get_paragem_name(aux->val, hash_paragem[locations_p[aux->val]]));

        if (i != z.numero_de_paragens - 1)
        {
            printf(", ");
        }
    }

    if (z.numero_de_paragens > 0)
    {
        printf("\n");
    }
}

/*Da print as paragens de uma carreira*/
void print_paragens_associadas(carreira z, int *locations_p, node_p **hash_paragem)
{
    int i;
    linked_int *aux = z.paragem_index;

    for (i = 0; i < z.numero_de_paragens; i++)
    {

        printf("%s", get_paragem_name(aux->val, hash_paragem[locations_p[aux->val]]));
        aux = aux->next;

        if (i != z.numero_de_paragens - 1)
        {
            printf(", ");
        }
    }

    if (z.numero_de_paragens > 0)
    {
        printf("\n");
    }
}

/*Da print as carreiras todas existentes*/
void print_carreiras(int n_carreiras, node_c **hash_carreira, node_p **hash_paragem, int *locations_c, int *locations_p)
{
    int i;
    node_c *z;
    linked_int *aux1, *aux2;

    for (i = 0; i < n_carreiras; i++)
    {
        /*Caso a carreira tenha sido removida*/
        if (locations_c[i] != -1)
        {

            z = hash_carreira[locations_c[i]];

            while (z->carreira->id != i)
            {
                z = z->next;
            }

            if (strlen(z->carreira->nome) < 6)
            {
                printf("%s ", z->carreira->nome);

                if (z->carreira->numero_de_paragens > 1)
                {
                    aux1 = z->carreira->paragem_index;
                    aux2 = z->carreira->paragem_index;

                    while (aux2->next != NULL)
                    {
                        aux2 = aux2->next;
                    }

                    printf("%s %s ",
                           get_paragem_name(aux1->val, hash_paragem[locations_p[aux1->val]]),
                           get_paragem_name(aux2->val, hash_paragem[locations_p[aux2->val]]));
                }

                printf("%i %.2f %.2f\n", z->carreira->numero_de_paragens, z->carreira->preco_total, z->carreira->tempo_total);
            }
        }
    }
}

/*Retorna a carreira atraves do seu nome*/
carreira *get_carreira(char *s, node_c *hash_carreira)
{

    node_c *z = hash_carreira;

    while (z != NULL)
    {

        if (strcmp(z->carreira->nome, s) == 0)
        {
            return z->carreira;
        }

        z = z->next;
    }

    return NULL;
}

/*Retorna a carreira atraves do seu id*/
carreira *get_carreira_by_index(int index, node_c *hash_carreira)
{

    node_c *z = hash_carreira;

    while (z != NULL)
    {

        if (z->carreira->id == index)
        {
            return z->carreira;
        }

        z = z->next;
    }

    return NULL;
}

/*Remove todas paragens com id = index e ajusta
o tempo e o custo da carreira*/
carreira *remove_all_n(int index, carreira *y)
{

    linked_int *ptr = y->paragem_index;
    linked_double *curr_t, *prev_t, *curr_d, *prev_d, *aux;
    int counter = 0;

    curr_d = y->preco;
    curr_t = y->tempo;

    while (ptr != NULL)
    {

        if (ptr->val == index)
        {
            /*Caso o valor seja igual ao retirar o valo e retirado e o numero de paragens diminui*/
            y->paragem_index = remove_from_linked_int(index, y->paragem_index);

            ptr = y->paragem_index;
            y->numero_de_paragens--;

            if (counter == 0)
            {
                /*Caso a paragem retirada seja a primeira*/
                if (curr_t != NULL)
                {

                    y->preco = curr_d->next;
                    y->tempo = curr_t->next;
                    y->preco_total -= curr_d->val;
                    y->tempo_total -= curr_t->val;
                    free(curr_d);
                    free(curr_t);
                }
            }
            else
            {
                /*Caso a paragem retirada nao seja nenhum extremo*/
                if (prev_d->next != NULL)
                {

                    prev_d->next = curr_d->next;
                    prev_d->val += curr_d->val;
                    free(curr_d);

                    prev_t->next = curr_t->next;
                    prev_t->val += curr_t->val;
                    free(curr_t);
                }
                else
                {
                    /*Caso a paragem retirada seja a ultima*/
                    aux = y->preco;
                    if (aux->next == NULL)
                    {
                        free(aux);
                        aux = y->tempo;
                        free(aux);
                        y->preco = NULL;
                        y->tempo = NULL;
                        break;
                    }
                    while (aux->next->next != NULL)
                    {
                        aux = aux->next;
                    }

                    aux->next = NULL;
                    y->preco_total -= prev_d->val;
                    free(prev_d);

                    aux = y->tempo;
                    while (aux->next->next != NULL)
                    {
                        aux = aux->next;
                    }

                    aux->next = NULL;
                    y->tempo_total -= prev_t->val;
                    free(prev_t);
                }
            }

            curr_d = y->preco;
            curr_t = y->tempo;

            counter = 0;
            /*Caso ja nao hajam paragens o numero de paragens e reduzido a 0*/
            if (y->paragem_index == NULL)
            {
                y->numero_de_paragens = 0;
                break;
            }
        }
        else
        {
            /*Caso a paragem atual nao seja removida passa-se ao proximo elemento*/
            if (curr_d != NULL)
            {

                prev_d = curr_d;
                curr_d = curr_d->next;
                prev_t = curr_t;
                curr_t = curr_t->next;
            }

            ptr = ptr->next;
            counter++;
        }
    }

    return y;
}

/*Adiciona uma carreira nova*/
int *add_carreira(int *n_carreiras, node_c **hash_carreira, node_p **hash_paragem, int *locations_c, int *locations_p)
{
    int c = getchar(), length = 0, reverse = 0, hash_id, exist = 0;
    char s[BUFSIZ], inv[8] = "inverso";
    carreira *z, *y;

    /*Caso o comando seja apenas -c da print
    as carreiras existentes*/
    if (c == '\n')
    {
        print_carreiras(*n_carreiras, hash_carreira, hash_paragem, locations_c, locations_p);
        return locations_c;
    }

    /*Caso contrario le o nome da carreira*/
    while ((c = getchar()) != '\n' && c != ' ')
    {
        s[length++] = c;
    }

    /*Inicia os valores da estrutura carreira*/
    s[length] = '\0';
    z = (carreira *)malloc(sizeof(carreira));
    z->nome = (char *)malloc(sizeof(char) * (length + 1));
    strcpy(z->nome, s);
    z->id = *n_carreiras;
    z->numero_de_paragens = 0;
    z->paragem_index = NULL;
    z->preco_total = 0;
    z->tempo_total = 0;
    z->preco = NULL;
    z->tempo = NULL;

    /*Verifica se a palavra a seguir e inverso ou alguma abreviacao*/
    if (c != '\n')
    {

        length = 0;
        while ((c = getchar()) != '\n')
        {
            s[length++] = c;
        }

        s[length] = '\0';

        if (length > 8 || length < 3)
        {
            printf("incorrect sort option.\n");
            free(z->nome);
            free(z);
            return locations_c;
        }

        for (c = 0; c < length; c++)
        {
            if (s[c] != inv[c])
            {
                printf("incorrect sort option.\n");
                free(z->nome);
                free(z);
                return locations_c;
            }
        }

        reverse = 1;
    }

    /*Verifica se a carreira existe*/
    hash_id = hash_function(z->nome);
    exist = check_carreira_exist(z->nome, hash_carreira[hash_id]);

    /*Caso exista da print das paragens associadas a carreira da ordem prevista*/
    if (exist == 1)
    {
        y = get_carreira(z->nome, hash_carreira[hash_id]);
        if (reverse == 0)
        {
            print_paragens_associadas(*y, locations_p, hash_paragem);
        }
        else
        {

            print_paragens_associadas_reverse(*y, locations_p, hash_paragem);
        }
        free(z->nome);
        free(z);
    }
    else
    {
        /*Caso nao exista insere a carreira na tabela e
        o seu hash id no array locations_c*/
        hash_carreira = insert_into_table_c(hash_id, z, hash_carreira);

        if ((*n_carreiras)++ == 0)
        {
            locations_c = (int *)malloc(sizeof(int));
        }
        else
        {
            locations_c = (int *)realloc(locations_c, sizeof(int) * (*n_carreiras));
        }

        if (locations_c == NULL)
        {
            printf("No memory.");
            exit(0);
        }

        locations_c[*n_carreiras - 1] = hash_id;
    }

    return locations_c;
}

/*Retorna o nome de uma carreira atraves do seu id*/
char *get_carreira_nome(int index, node_c *hash_carreira)
{
    node_c *x = hash_carreira;

    while (x->carreira->id != index && x != NULL)
    {
        x = x->next;
    }

    return x->carreira->nome;
}

/*Verifica se uma carreira existe ou nao*/
int check_carreira_exist(char *s, node_c *hash_carreira)
{

    node_c *z = hash_carreira;

    while (z != NULL)
    {

        if (strcmp(z->carreira->nome, s) == 0)
        {
            return 1;
        }

        z = z->next;
    }

    return 0;
}

void teste_pratico(int *locations_c, node_c **hash_carreira, node_p **hash_paragem, int n_carreiras)
{
    int c, i = 0, hash_id, space = 0;
    char s[MAX_TAMANHO_LINHA];
    paragem *x;
    carreira *y;
    linked_int *z;

    c = getchar();
    c = getchar();

    if (c == '"')
    {
        while ((c = getchar()) != '"')
        {
            s[i++] = c;
        }

        s[i] = '\0';
    }
    else
    {
        while (c != '\n')
        {
            s[i++] = c;
            c = getchar();
        }

        s[i] = '\0';
    }

    hash_id = hash_function(s);

    if (hash_paragem[hash_id] == NULL)
    {
        printf("%s: no such stop.\n", s);
        return;
    }

    x = get_paragem(s, hash_paragem[hash_id]);

    if (x == NULL)
    {
        printf("%s: no such stop.\n", s);
        return;
    }

    for (i = 0; i < n_carreiras; i++)
    {
        if (locations_c[i] != -1)
        {
            y = get_carreira_by_index(i, hash_carreira[locations_c[i]]);
            z = y->paragem_index;
            if (z != NULL)
            {
                while (z->next != NULL)
                {   
                    z = z->next;
                }

                if (z->val == x->id)
                {
                    printf("%s", y->nome);
                    space++;

                    if (i < n_carreiras - 1)
                    {
                        printf(" ");
                    }
                }
            }
        }
    }

    if (space != 0)
        printf("\n");
}