/* iaed-23 - ist1103368 - project1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_PARAGEM 50  /*Tamanho maximo do nome de uma paragem*/
#define MAX_NAME_CARREIRA 20 /*Tamanho maximo do nome de uma carreira*/
#define MAX_PARAGENS 10000   /*Numero maximo de paragens*/
#define MAX_CARREIRAS 200    /*Numero maximo de carreiras*/
#define MAX_LIGACOES 30000   /*Numero maximo de ligacoes*/

typedef struct paragem_description /*Estrutura que guarda todas as informacoes necessarias de uma paragem*/
{
    char nome[MAX_NAME_PARAGEM]; /*Nome da paragem*/
    double longitude;            /*Longitude*/
    double latitude;             /*Latitude*/
    int carreiras;               /*Numero de carreiras associadas a paragem*/
    int *index_carreira;         /*Indexes das carreiras associadas as paragens*/

} paragem_description;

typedef struct carreira_description /*Estrutura que guarda todas as informacoes necessarias de uma carreira*/
{

    int *index;                   /*Indexes das paragens associadas a carreira*/
    char nome[MAX_NAME_CARREIRA]; /*Nome da carreira*/
    float preco;                  /*Preco total da carreira*/
    float tempo;                  /*Tempo total da carreira*/
    int numero_de_paragens;       /*Numero de paragens associadas a carreira*/

} carreira_description;

/*Variaveis globais*/
int n_paragens = 0;  /*Numero total de paragens*/
int n_carreiras = 0;  /*Numero total de carreiras*/
int n_ligacoes = 0;  /*Numero total de ligacoes*/

int check_paragem(char s[], paragem_description paragens[]) /*Caso exista uma paragem com o mesmo nome que a string recebida retorna 1, caso contrario retorna 0*/
{
    int i;

    for (i = 0; i < n_paragens; i++)
    {
        if (strcmp(s, paragens[i].nome) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void print_l_and_l(char s[], paragem_description paragens[]) /*Da print a latitude e a longitude de uma certa paragem*/
{
    int i, write = 0;

    /*Nesta funcao nao e utilizada a funcao check_paragem pois e necessario o index i*/

    for (i = 0; i < n_paragens; i++) /*Caso a paragem exista da print a latitude e a longitude*/
    {
        if (strcmp(s, paragens[i].nome) == 0)
        {
            write = 1;
            break;
        }
    }

    if (write == 1)
    {
        printf("%16.12f %16.12f\n", paragens[i].latitude, paragens[i].longitude);
    }
    else
    {
        printf("%s: no such stop.\n", s); /*Caso nao exista da print a este erro*/
    }

    return;
}

void print_paragens(paragem_description paragens[]) /*Da print do nome, longitude, latitude e numero de carreiras associadas de cada paragem*/
{

    int i;

    for (i = 0; i < n_paragens; i++)
    {
        printf("%s: %16.12f %16.12f %i\n", paragens[i].nome, paragens[i].latitude, paragens[i].longitude, paragens[i].carreiras);
    }
    return;
}

void add_p(paragem_description paragens[]) /*Le o que se segue ao comando -p e executa a acao pretendida*/
{
    int c, i = 0, unused __attribute__((unused)), existe;

    c = getchar();

    if (c == '\n')
    {
        print_paragens(paragens); /*Caso a linha seja apenas -p o programa realiza a funcao print_paragens*/
    }
    else
    { /*Caso o comando nao seja apenas -p e seja seguido pelo nome de uma paragem*/
        c = getchar();
        if (c == '"') /*Caso o nome da paragem esteja entre aspas*/
        {
            while ((c = getchar()) != '"')
            {
                paragens[n_paragens].nome[i] = c; /*Copia o nome da paragem para a primeira estrutura do tipo paragem_description que nao esteja a ser utilizada*/
                i++;
            }
            paragens[n_paragens].nome[i] = '\0'; /*Adiciona o carater de fim de string*/

            c = getchar();

            if (c == ' ') /*Caso o comando continue...*/
            {
                /*Guarda os valores da latitude e da longitude*/
                unused = scanf("%lf %lf", &paragens[n_paragens].latitude, &paragens[n_paragens].longitude); /*A variavel unused serve para resolver um erro do compilador em que se ignora o valor retornado pelo scanf*/
                existe = check_paragem(paragens[n_paragens].nome, paragens);                                /*Verifica se a paragem ja existe ou nao*/

                if (existe == 0 && n_paragens < MAX_PARAGENS)
                {
                    n_paragens++; /*Caso nao exista incrementa o valor de n_paragens, ou seja, adiciona-se mais uma paragem*/
                }
                else
                {
                    printf("%s: stop already exists.\n", paragens[n_paragens].nome); /*Caso nao exista da print ao seguinte erro*/
                }
            }
            else
            {

                print_l_and_l(paragens[n_paragens].nome, paragens); /*Caso o comando seja so -p NomeDeParagem o programa executa a funcao print_l_and_l*/
            }
        }

        else
        {
            /*Igual ao if acima mas neste caso o nome da paragem nao se encontra entre aspas*/
            while (c != '\n' && c != ' ')
            {
                paragens[n_paragens].nome[i] = c;
                i++;
                c = getchar();
            }
            paragens[n_paragens].nome[i] = '\0';

            if (c == ' ')
            {
                unused = scanf("%lf %lf", &paragens[n_paragens].latitude, &paragens[n_paragens].longitude);
                existe = check_paragem(paragens[n_paragens].nome, paragens);

                if (existe == 0 && n_paragens < MAX_PARAGENS)
                {
                    n_paragens++;
                }
                else
                {
                    printf("%s: stop already exists.\n", paragens[n_paragens].nome);
                }
            }
            else
            {
                print_l_and_l(paragens[n_paragens].nome, paragens);
            }
        }
    }

    return;
}

void check_carreira(char s[], carreira_description carreiras[], paragem_description paragens[], int reverse) /*Compara se a string recebida e igual a alguma carreira existente e da print as paragens associadas a essa carreira na ordem pretendida*/
{
    int i, exist = 0, j;

    for (i = 0; i < n_carreiras; i++) /*Verifica se a string e igual a alguma carreira*/
    {
        if (strcmp(s, carreiras[i].nome) == 0)
        {
            exist = 1;
            break;
        }
    }

    if (exist == 1) /*Caso exista da printf as paragens associadas...*/
    {
        if (reverse == 0) /*...na ordem em que foram associadas a carreira*/
        {
            for (j = 0; j < carreiras[i].numero_de_paragens; j++)
            {
                printf("%s", paragens[carreiras[i].index[j]].nome);

                if (j + 1 != carreiras[i].numero_de_paragens)
                {
                    printf(", ");
                }
            }
            if (carreiras[i].numero_de_paragens != 0)
            {
                printf("\n");
            }
        }
        else
        {

            for (j = carreiras[i].numero_de_paragens - 1; j >= 0; j--) /*... na ordem contraria em que foram associadas a carreira*/
            {
                printf("%s", paragens[carreiras[i].index[j]].nome);

                if (j != 0)
                {
                    printf(", ");
                }
            }
            if (carreiras[i].numero_de_paragens != 0)
            {
                printf("\n");
            }
        }
    }
    else
    {
        if (n_carreiras < MAX_CARREIRAS) /*Caso o numero de carreiras existentes nao exceda o numero de carreiras maximo incremente o numero de carreiras*/
        {
            n_carreiras++;
        }
    }
    return;
}

void printf_carreiras(carreira_description carreiras[], paragem_description paragens[]) /*Da print ao nome da carreira, nome das paragens extremo associadas a carreira, ao numero de paragens associadas, ao preco e ao tempo*/
{
    int i;

    for (i = 0; i < n_carreiras; i++)
    {

        printf("%s", carreiras[i].nome);

        if (carreiras[i].numero_de_paragens != 0)
        {
            printf(" %s %s", paragens[carreiras[i].index[0]].nome, paragens[carreiras[i].index[carreiras[i].numero_de_paragens - 1]].nome);
        }

        printf(" %i %.2f %.2f\n", carreiras[i].numero_de_paragens, carreiras[i].preco, carreiras[i].tempo);
    }

    return;
}

void add_c(carreira_description carreiras[], paragem_description paragens[]) /*Le o que se segue ao comando -c e executa a acao pretendida*/
{

    int c, i = 0, reverse;
    char sort[MAX_NAME_CARREIRA];

    c = getchar();

    if (c == '\n')
    {
        printf_carreiras(carreiras, paragens); /*Caso o comando seja apenas -c executa a funcao printf_carreiras*/
    }
    else
    {
        c = getchar();
        while (c != ' ' && c != '\n') /*Le o nome da carreira*/
        {
            carreiras[n_carreiras].nome[i] = c;
            i++;
            c = getchar();
        }
        carreiras[n_carreiras].nome[i] = '\0'; /*Adiciona o carater de fim de string*/

        if (c == '\n') /*Caso o comando seja apenas -c NomeDaCarreira executa a funcao check_carreira com a variavel reverse a 0*/
        {
            reverse = 0;
            check_carreira(carreiras[n_carreiras].nome, carreiras, paragens, reverse);
        }
        else
        {
            /*Caso contrario le a palavra seguinte e guarda-a na string sort*/
            i = 0;
            c = getchar();

            while (c != '\n')
            {

                sort[i] = c;

                i++;
                c = getchar();
            }

            sort[i] = '\0';

            /*Caso a string sort seja igual a inv/inve/inver/invers/inverso o programa executa a funcao check_carreira com a variavel reverse a 1*/
            if (strcmp(sort, "inv") == 0 || strcmp(sort, "inve") == 0 || strcmp(sort, "inver") == 0 || strcmp(sort, "invers") == 0 || strcmp(sort, "inverso") == 0)
            {
                reverse = 1;
                check_carreira(carreiras[n_carreiras].nome, carreiras, paragens, reverse);
            }
            else
            {
                /*Caso a string seja diferente das opcoes anteriores da print ao seguinte erro*/
                printf("incorrect sort option.\n");
            }
        }
    }

    return;
}

int check_origin_n_destiny(int origem, int destino, carreira_description carreira) /*Verifica se a origem/destino da ligacao coincide com algum dos extremos da carreira*/
{

    if (origem == carreira.index[carreira.numero_de_paragens - 1]) /*Caso a origem coincida com o fim da carreira retorna 2*/
    {

        return 2;
    }

    if (destino == carreira.index[0]) /*Caso o destino coincida com o inicio da carreira retorna 3*/
    {

        return 3;
    }

    return 0; /*Caso nenhumas das anteriores se verifique retorna 0*/
}

void sort_carreiras(paragem_description paragem, carreira_description carreiras[]) /* Bubble Sort para ordenar as carreiras quando o comando -i e invocado*/
{
    int j, i;
    int aux;

    /*O bubble sort compara os nomes das carreiras dados pelo parametro index_carreira da estrutura paragem.
    Caso seja necessario uma troca, os indexes sao trocados, permitindo que a ordem das carreiras se mantenha pela ordem de criacao*/

    for (j = 0; j < paragem.carreiras; j++)
    {
        for (i = 0; i < paragem.carreiras - 1 - j; i++)
        {

            if (strcmp(carreiras[paragem.index_carreira[i]].nome, carreiras[paragem.index_carreira[i + 1]].nome) > 0)
            {
                aux = paragem.index_carreira[i];
                paragem.index_carreira[i] = paragem.index_carreira[i + 1];
                paragem.index_carreira[i + 1] = aux;
            }
        }
    }

    return;
}

/*Verifica se ha algum erro com o nome da carreira, origem e destino passados na ligacao. Caso nao exista cria a ligacao*/
void check_ligacao(char nome_da_carreira[], char origem[], char destino[], carreira_description carreiras[], paragem_description paragens[], float custo, float tempo) 
{
    int i, j, k, z, exist = 0, action;

    for (i = 0; i < n_carreiras; i++) /*Verifica se o nome da carreira e igual a alguma carreira existente*/
    {
        if (strcmp(carreiras[i].nome, nome_da_carreira) == 0)
        {
            exist = 1;
            break;
        }
    }

    if (exist == 0) /*Caso nao exista da erro*/
    {
        printf("%s: no such line.\n", nome_da_carreira);
        return;
    }

    exist = 0;

    /*Verifica agora se tanto a origem como o destino existem como paragens. Caso nao existam da erro*/
    for (j = 0; j < n_paragens; j++)
    {
        if (strcmp(origem, paragens[j].nome) == 0)
        {
            exist = 1;
            break;
        }
    }

    if (exist == 0)
    {
        printf("%s: no such stop.\n", origem);
        return;
    }

    exist = 0;

    for (z = 0; z < n_paragens; z++)
    {

        if (strcmp(destino, paragens[z].nome) == 0)
        {
            exist = 1;
            break;
        }
    }

    if (exist == 0)
    {
        printf("%s: no such stop.\n", destino);
        return;
    }

    /*Caso existam todos a ligacao e criada*/

    /*Caso sejam as 2 primeiras paragens da carreira: */
    if (carreiras[i].numero_de_paragens == 0)
    {
        carreiras[i].numero_de_paragens = 2; /*Iguala o numero de paragens da carreira a 2 */
        carreiras[i].index = malloc(sizeof(int) * 2); /*Cria espaco para os 2 inteiros*/
        carreiras[i].index[0] = j; /*Iguala a primeira posicao ao index da origem*/
        carreiras[i].index[1] = z; /*Iguala a segunda posicao ao index do destino*/
        /*Incrementa o numero de carreiras das paragens origem e destino*/
        paragens[j].carreiras++;
        paragens[z].carreiras++;
        /*Adiciona o preco e o tempo a carreira*/
        carreiras[i].preco = carreiras[i].preco + custo;
        carreiras[i].tempo = carreiras[i].tempo + tempo;
        /*Incrementa o numero de ligacoes*/
        n_ligacoes++;

        /*Adiciona o index da carreira ao parametro index_carreira das paragens origem e destino*/

        /*Caso seja a primeira carreira associada utiliza o malloc. Caso contrario, utiliza o realloc*/
        if (paragens[j].carreiras > 1)
        {
            paragens[j].index_carreira = realloc(paragens[j].index_carreira, paragens[j].carreiras * sizeof(int));
            paragens[j].index_carreira[paragens[j].carreiras - 1] = i;
        }
        else
        {
            paragens[j].index_carreira = malloc(sizeof(int));
            paragens[j].index_carreira[0] = i;
        }

        if (paragens[z].carreiras > 1)
        {
            paragens[z].index_carreira = realloc(paragens[z].index_carreira, paragens[z].carreiras * sizeof(int));
            paragens[z].index_carreira[paragens[z].carreiras - 1] = i;
        }
        else
        {
            paragens[z].index_carreira = malloc(sizeof(int));
            paragens[z].index_carreira[0] = i;
        }
    }
    else
    {
        /*Caso nao sejam as primeiras paragens da carreira e executada a funcao check_origin_n_destiny.*/
        action = check_origin_n_destiny(j, z, carreiras[i]);
        exist = 0;

        switch (action)
        {

        case 2: /*Caso a nova paragem seja adicionada em ultimo lugar*/
            for (k = 0; k < carreiras[i].numero_de_paragens; k++)
            {
                if (carreiras[i].index[k] == z) /*Verifica se a carreira a adicionar ja existe*/
                {
                    exist = 1;
                    break;
                }
            }
            /*Adiciona o custo, o tempo e incremente o numero de ligacoes*/
            carreiras[i].preco = carreiras[i].preco + custo;
            carreiras[i].tempo = carreiras[i].tempo + tempo;
            n_ligacoes++;

            if (exist == 0 || (exist == 1 && k == 0)) /*Caso nao exista a paragem a ser adicionada ou caso exista e seja o primeiro lugar da carreira(caso em que e uma carreira circular)*/
            {
                carreiras[i].numero_de_paragens++; /*Incrementa o numero de paragens da carreira*/
                carreiras[i].index = realloc(carreiras[i].index, carreiras[i].numero_de_paragens * sizeof(int)); /*Aloca mais memoria para guardar o index da nova paragem*/
                carreiras[i].index[carreiras[i].numero_de_paragens - 1] = z; /*Guarda o index*/

                if (exist == 0) /*Apenas se a paragem nao fizer ainda parte da carreira*/
                {
                    paragens[z].carreiras++; /*Incrementa o numero de carreiras associadas a paragem*/
                    if (paragens[z].carreiras > 1) /*Caso nao hajam carreiras associadas a paragem usa-se o malloc. Caso contrario utiliza-se o realloc*/
                    {
                        paragens[z].index_carreira = realloc(paragens[z].index_carreira, paragens[z].carreiras * sizeof(int));
                    }
                    else
                    {
                        paragens[z].index_carreira = malloc(sizeof(int));
                    }

                    paragens[z].index_carreira[paragens[z].carreiras - 1] = i; /*Guarda o index da carreira*/
                }
            }

            break;

        case 3: /*Caso a nova paragem seja adicionada no inicio*/

            for (k = 0; k < carreiras[i].numero_de_paragens; k++) /*Verifica se a paragem ja se encontra associada a carreira*/
            {
                if (carreiras[i].index[k] == j)
                {
                    exist = 1;
                    break;
                }
            }

            /*Adiciona-se o custo, o tempo e o numero de ligacoes e incrementado*/
            carreiras[i].preco = carreiras[i].preco + custo;
            carreiras[i].tempo = carreiras[i].tempo + tempo;
            n_ligacoes++;
            if (exist == 0 || (exist == 1 && k == carreiras[i].numero_de_paragens - 1)) /*Caso nao exista paragem associada ainda ou caso esta paragem seja a ultima*/
            {
                carreiras[i].numero_de_paragens++; /*Incrementa-se o numero de paragens associadas a carreira*/
                carreiras[i].index = realloc(carreiras[i].index, carreiras[i].numero_de_paragens * sizeof(int)); /*Aloca-se mais memoria para guardar o index*/

                for (k = carreiras[i].numero_de_paragens - 1; k > 0; k--) /*Todos os elementos do vetor avancam uma posicao*/
                {
                    carreiras[i].index[k] = carreiras[i].index[k - 1];
                }

                carreiras[i].index[0] = j; /*A primeira posicao da carreira torna-se a nova paragem*/

                if (exist == 0) /*Apenas se a paragem nao estiver ja associada*/
                {
                    paragens[j].carreiras++; /*Incrementa-se o numero de carreiras asssociadas a paragem*/

                    if (paragens[j].carreiras > 1) /*Caso nao hajam carreiras associadas a paragem usa-se o malloc. Caso contrario utiliza-se o realloc*/
                    {
                        paragens[j].index_carreira = realloc(paragens[j].index_carreira, paragens[j].carreiras * sizeof(int));
                    }
                    else
                    {
                        paragens[j].index_carreira = malloc(sizeof(int));
                    }

                    paragens[j].index_carreira[paragens[j].carreiras - 1] = i; /*Guarda o index*/
                }
            }

            break;

        case 0: /*Caso em que nenhumas das paragens e um extremo da carreira*/
            printf("link cannot be associated with bus line.\n");
            break;
        }
    }

    return;
}

void add_l(carreira_description carreiras[], paragem_description paragens[]) /*Le o que se segue ao comando -l e executa a acao pretendida*/
{
    int c, i = 0, unused __attribute__((unused));
    char destino[MAX_NAME_PARAGEM], origem[MAX_NAME_PARAGEM], nome_da_carreira[MAX_NAME_CARREIRA];
    float tempo, custo;

    c = getchar();
    c = getchar();

    while (c != ' ') /*Le o nome da carreira*/
    {
        nome_da_carreira[i] = c;
        i++;
        c = getchar();
    }

    nome_da_carreira[i] = '\0';

    i = 0;
    c = getchar();

    if (c == '"') /*Guarda a primeira paragem na vaariavel origem*/
    {
        c = getchar();

        while (c != '"')
        {
            origem[i] = c;
            i++;
            c = getchar();
        }

        origem[i] = '\0';
    }
    else
    {

        while (c != ' ')
        {
            origem[i] = c;
            i++;
            c = getchar();
        }

        origem[i] = '\0';
    }

    c = getchar();
    i = 0;

    if (c == ' ')
    {
        c = getchar();
    }

    if (c == '"') /*Guarda a segunda paragem na variavel destino*/
    {
        c = getchar();

        while (c != '"')
        {
            destino[i] = c;
            i++;
            c = getchar();
        }

        destino[i] = '\0';
        c = getchar();
    }

    else
    {
        while (c != ' ')
        {
            destino[i] = c;
            i++;
            c = getchar();
        }

        destino[i] = '\0';
    }

    unused = scanf("%f %f", &custo, &tempo); /*Guarda o custo e o tempo da ligacao*/

    if (custo < 0 || tempo < 0)
    {
        printf("negative cost or duration.\n"); /*Erro caso o custo e/ou o tempo sejam negativos*/
    }
    else
    {

        check_ligacao(nome_da_carreira, origem, destino, carreiras, paragens, custo, tempo); /*Caso sejam positivos invoca a funcao check_ligacao*/
    }

    return;
}

/*Executa o comando -i e da print para cada paragem existente ao seu nome, numero de carreiras associadas e nome das carreiras associadas ordenas alfabeticamente*/
void add_i(carreira_description carreiras[], paragem_description paragens[]) 
{
    int i, j;

    for (i = 0; i < n_paragens; i++)
    {
        if (paragens[i].carreiras > 1)
        {
            sort_carreiras(paragens[i], carreiras); /*Da sort as carreiras associadas a paragem atual*/
            printf("%s %i: ", paragens[i].nome, paragens[i].carreiras); /*Da print ao nome da paragem e ao numero de carreiras a que esta esta associada */

            for (j = 0; j < paragens[i].carreiras; j++) /*Da print as carreiras associadas*/
            {
                printf("%s", carreiras[paragens[i].index_carreira[j]].nome);

                if (j + 1 != paragens[i].carreiras)
                {
                    printf(" ");
                }
            }

            printf("\n");
        }
    }
    return;
}

int main()
{
    int c, i;
    paragem_description paragens[MAX_PARAGENS];
    carreira_description carreiras[MAX_CARREIRAS];

    for (i = 0; i < MAX_PARAGENS; i++) /* Inicia as estruturas das paragens */
    {
        paragens[i].nome[0] = '\0';
        paragens[i].latitude = 0;
        paragens[i].longitude = 0;
        paragens[i].carreiras = 0;
    }

    for (i = 0; i < MAX_CARREIRAS; i++)
    { /* Inicia as estruturas das carreiras */

        carreiras[i].nome[0] = '\0';
        carreiras[i].preco = 0;
        carreiras[i].tempo = 0;
        carreiras[i].numero_de_paragens = 0;
    }

    

    while ((c = getchar()) != 'q') /*Obtem os comandos atraves do getchar(). Caso o comando seja q sai do ciclo e acaba o programa*/
    {

        if (c == 'p') /*Caso o comando seja p*/
        {
            add_p(paragens);
        }

        if (c == 'c') /*Caso o comando seja c*/
        {

            add_c(carreiras, paragens);
        }

        if (c == 'l') /*Caso o comando seja l e o numero de ligacoes nao e ja maximo*/
        {
            if (n_ligacoes > MAX_LIGACOES)
            {
                while (c != '\n')
                {
                    c = getchar();
                }
            }
            else
            {
                add_l(carreiras, paragens);
            }
        }

        if (c == 'i') /*Caso o comando seja i*/
        {
            add_i(carreiras, paragens);
        }
    }

    /*Frees das variaveis alocadas*/
    for (i = 0; i < n_paragens; i++)
    {
        if (paragens[i].carreiras != 0)
        {
            free(paragens[i].index_carreira);
        }
    }

    for (i = 0; i < n_carreiras; i++)
    {
        if (carreiras[i].numero_de_paragens != 0)
        {
            free(carreiras[i].index);
        }
    }

    return 0;
}
