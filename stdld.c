#include "stdld.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define SWAP(a,b)({a^=b;b^=a;a^=b;})
#define descobreSize(arr,n)({n=sizeof(arr)/sizeof(arr[0]);})

struct elementos
{
    struct informacao dados;
    struct elementos* prox,* ant;
};
struct noDiscritor
{
    struct elementos* pInicio,* pFinal;
    unsigned long qtd;
};

/**Funções proprias da .c*/
void fazTroca( struct informacao* dado1, struct informacao* dado2 )
{
    info temp = *dado1;
    *dado1 = *dado2;
    *dado2 = temp;
}
short encontraNoPosicao( struct elementos** no, long pos )
{
    register long i;

    if ( !no )
        return -1;

    for ( i = 0; (i < pos) && ((*no)->prox != NULL); ++i, (*no) = (*no)->prox );

    if ( (i != pos) && ((*no)->prox == NULL) )
        return 0;

    return 1;
}
short heapify( struct elementos* pInicio, unsigned long tam, unsigned long pos )
{
    unsigned long posMaior = pos, posEsq = 2*pos + 1, posDir = 2*pos + 2;
    short bol = 0;
    elem* noEsq = pInicio,* noDir = pInicio,* noMaior,* no = pInicio;

    if ( !no )
        return -1;

    if ( (pos != 0) && (pos < tam) )
    {
        bol = encontraNoPosicao(&no, pos);

        if ( bol != 1 )
            return bol;
    }

    noMaior = no;
    encontraNoPosicao(&noEsq, posEsq);
    encontraNoPosicao(&noDir, posDir);

    if ( (posEsq < tam) && (noEsq->dados.num > noMaior->dados.num) )
    {
        noMaior = noEsq;
        posMaior = posEsq;
    }

    if ( (posDir < tam) && (noDir->dados.num > noMaior->dados.num) )
    {
        noMaior = noDir;
        posMaior = posDir;
    }

    if ( posMaior != pos )
    {
        fazTroca(&(no->dados), &(noMaior->dados));

        bol = heapify(pInicio, tam, posMaior);
        if( bol != 1 )
            return bol;
    }

    return 1;
}

/**Funções que estão na .h*/
short criaLista( lista** li )
{
    *li = (lista*)malloc(sizeof(lista));

    if ( !li )
        return -1;

    (*li)->pInicio = NULL;
    (*li)->pFinal = NULL;
    (*li)->qtd = 0;

    return 1;
}
short criaNo( elem** no, info dado )
{
    *no = (elem*)malloc(sizeof(elem));

    if ( no == NULL )
        return -1;

    (*no)->dados = dado;
    (*no)->prox = NULL;
    (*no)->ant = NULL;

    return 1;
}
short liberaLista( lista* li )
{
    elem* no;

    if ( !li )
        return -1;

    while ( (li->pInicio) != NULL )
    {
        no = li->pInicio;
        li->pInicio = li->pInicio->prox;

        free(no);
    }

    free(li);

    return 1;
}

short listaVazia( lista* li )
{
    if ( !li )
        return -1;

    return (li->qtd == 0) ? (1) : (0);
}
short listaCheia( lista* li )
{
    if ( !li )
        return -1;

    return (li->qtd == MAX) ? (1) : (0);
}
short listaTamanho( lista* li )
{
    if ( !li )
        return -1;

    return li->qtd;
}

short insereListaInicio( lista* li, info dado )
{
    elem* no;
    short bol = criaNo(&no, dado);

    if ( (!li) || (!bol) )
        return -1;

    if ( listaCheia(li) )
        return 0;

    no->prox = li->pInicio;

    if ( listaVazia(li) )
        li->pFinal = no;

    else
        li->pInicio->ant = no;

    li->pInicio = no;
    ++li->qtd;

    return 1;
}
short insereListaMeio( lista* li, info dado )
{
    elem* no,* aux;
    short bol;

    if ( !li )
        return -1;

    if ( listaCheia(li) )
        return 0;

    if ( listaVazia(li) )
    {
        bol = insereListaInicio(li, dado);
        return bol;
    }

    bol = criaNo(&no, dado);

    if ( !bol )
        return -1;

    if ( li->pFinal->dados.num <= dado.num )
    {
        bol = insereListaFinal(li, dado);
        return bol;
    }

    if ( li->pInicio->dados.num >= dado.num )
    {
        bol = insereListaInicio(li, dado);
        return bol;
    }

    for ( aux = li->pInicio; (aux->prox != NULL) && (aux->dados.num <= dado.num); aux = aux->prox );

    no->prox = aux;
    no->ant = aux->ant;
    aux->ant->prox = no;
    aux->ant = no;

    ++li->qtd;

    return 1;
}
short insereListaFinal( lista* li, info dado )
{
    elem* no;
    short bol = criaNo(&no, dado);

    if ( (!li) || (!bol) )
        return -1;

    if ( listaCheia(li) )
        return 0;

    no->ant = li->pFinal;

    if ( listaVazia(li) )
        li->pInicio = no;

    else
        li->pFinal->prox = no;

    li->pFinal = no;
    ++li->qtd;

    return 1;
}

short removeInicio( lista* li )
{
    elem* no;

    if ( !li )
        return -1;

    if ( listaVazia(li) )
        return 0;

    no = li->pInicio;

    if ( li->qtd == 1 )
    {
        li->pFinal = NULL;
        li->pInicio = NULL;
    }

    else
    {
        li->pInicio = li->pInicio->prox;
        li->pInicio->ant = NULL;
    }

    --li->qtd;

    free(no);

    return 1;
}
short removeMeio( lista* li, info dado )
{
    elem* no;
    short bol;

    if ( !li )
        return -1;

    if ( listaVazia(li) )
        return 0;

    if ( li->pInicio->dados.num == dado.num )
    {
        bol = removeInicio(li);
        return bol;
    }

    if ( li->pFinal->dados.num == dado.num )
    {
        bol = removeFinal(li);
        return bol;
    }

    for ( no = li->pInicio->prox; (no->prox != NULL) && (no->dados.num != dado.num); no = no->prox );

    if ( no->prox == NULL )
        return 0;

    no->ant->prox = no->prox;
    no->prox->ant = no->ant;

    --li->qtd;

    free(no);

    return 1;
}
short removeFinal( lista* li )
{
    elem* no;

    if ( !li )
        return -1;

    if ( listaVazia(li) )
        return 0;

    no = li->pFinal;

    if ( li->qtd == 1 )
    {
        li->pFinal = NULL;
        li->pInicio = NULL;
    }

    else
    {
        li->pFinal = li->pFinal->ant;
        li->pFinal->prox = NULL;
    }

    --li->qtd;

    free(no);

    return 1;
}

short consultaListaPos( lista* li, unsigned long pos, info* dado )
{
    elem* no;
    register unsigned long i;

    if ( !li )
        return -1;

    if ( (listaVazia(li)) || (pos <= 0) || (pos > li->qtd) )
        return 0;

    for(i = 1, no = li->pInicio; (i != pos) && (no != NULL); ++i, no = no->prox);

    if(no == NULL)
        return 0;

    *dado = no->dados;

    return 1;
}
short consultaListaCont(lista* li, unsigned long num, info* dado)
{
    elem* no;

    if(!li)
        return -1;

    if(listaVazia(li))
        return 0;

    for(no = li->pInicio; (no != NULL) && (no->dados.num != num); no = no->prox);

    if(no == NULL)
        return 0;

    *dado = no->dados;

    return 1;
}

short imprimeConteudo(lista* li)
{
    elem* no;
    register unsigned long i;

    setlocale(LC_ALL, "");

    if(!li)
        return -1;

    if(listaVazia(li))
        return 0;

    printf("\n\t##### ...Começando a imprimir... #####\n");
    for(no = li->pInicio, i = 1; no != NULL; no = no->prox, ++i)
        printf("%luº numero: %lu\n", i, no->dados.num);
    printf("\n\t##### ...Termino da impreção... #####\n");

    return 1;
}
short imprimeElemento(lista* li, unsigned long num)
{
    info dado;
    short bol;

    setlocale(LC_ALL, "");

    if(!li)
        return -1;

    if(listaVazia(li))
        return 0;

    bol = consultaListaCont(li, num, &dado);

    if(bol != 1)
        return bol;

    printf("numero: %lu\n", dado.num);

    return 1;
}

short insereFileListaInicio(lista* li, const char* fileName)
{
    info dado;
    unsigned long aux;
    char c;
    short bol;
    FILE* fp;

    if(!li)
        return -1;

    if(!(fp = fopen(fileName, "r")) || (listaCheia(li)))
        return 0;

    for(dado.num = 0; (c = fgetc(fp)) != EOF;)
    {
        if(c == ' ')
        {
            bol = insereListaInicio(li, dado);

            if(bol != 1)
                return bol;

            dado.num = 0;
        }

        else
        {
            aux = c - '0';
            dado.num = dado.num * 10 + aux;
        }
    }

    fclose(fp);

    return 1;
}
short insereFileListaMeio(lista* li, const char* fileName)
{
    info dado;
    unsigned long aux;
    char c;
    short bol;
    FILE* fp;

    if(!li)
        return -1;

    if(!(fp = fopen(fileName, "r")) || (listaCheia(li)))
        return 0;

    for(dado.num = 0; (c = fgetc(fp)) != EOF;)
    {
        if(c == ' ')
        {
            bol = insereListaMeio(li, dado);

            if(bol != 1)
                return bol;

            dado.num = 0;
        }

        else
        {
            aux = c - '0';
            dado.num = dado.num * 10 + aux;
        }
    }

    fclose(fp);

    return 1;
}
short insereFileListaFinal(lista* li, const char* fileName)
{
    info dado;
    unsigned long aux;
    char c;
    short bol;
    FILE* fp;

    if(!li)
        return -1;

    if(!(fp = fopen(fileName, "r")) || (listaCheia(li)))
        return 0;

    for(dado.num = 0; (c = fgetc(fp)) != EOF;)
    {
        if(c == ' ')
        {
            bol = insereListaFinal(li, dado);

            if(bol != 1)
                return bol;

            dado.num = 0;
        }

        else
        {
            aux = c - '0';
            dado.num = dado.num * 10 + aux;
        }
    }

    fclose(fp);

    return 1;
}

short insereListaFile(lista* li, const char* fileName)
{
    elem* no;
    FILE* fp;

    if(!li)
        return -1;

    if((listaVazia(li)) || !(fp = fopen(fileName, "w")))
        return 0;

    for(no = li->pInicio; no != NULL; no = no->prox)
        fprintf(fp, "%lu ", no->dados.num);

    fclose(fp);

    return 1;
}
short insereFileRandom(const char* fileName)
{
    register unsigned long i;
    unsigned long *vet, numAle;
    FILE* fp;

    vet = (unsigned long*)malloc(sizeof(unsigned long) * MAX);

    srand(time(NULL));

    if(!(fp = fopen(fileName, "w")))
        return 0;

    for(i = 0; i < MAX; ++i)
        vet[i] = i + 1;

    if(MAX >= 1000000)
        for(i = 0; i < MAX; ++i)
        {
            numAle = rand();
            numAle <<= 15;
            numAle ^= rand();
            numAle %= MAX + 1;

            SWAP(vet[i], vet[numAle]);
        }

    else
        for(i = 0; i < MAX; ++i)
        {
            numAle = rand() % MAX;

            SWAP(vet[i], vet[numAle]);
        }

    for(i = 0; i < MAX; ++i)
        fprintf(fp, "%lu ", vet[i]);

    fclose(fp);

    return 1;
}

short shellSort(lista* li)
{
    elem* no,* aux,* comp;
    info temp;
    register long j, gap;
    register unsigned long i;
    short bol;

    if(!li)
        return -1;

    if(listaVazia(li))
        return 0;

    for(gap = li->qtd/2, no = li->pInicio; gap > 0; gap /= 2, no = li->pInicio)
    {
        bol = encontraNoPosicao(&no, gap);
        if(bol != 1)
            return bol;

        for(i = gap; (no != NULL) && (i < li->qtd); no = no->prox, ++i)
        {
            temp = no->dados;

            aux = no;
            j = i;
            comp = li->pInicio;
            bol = encontraNoPosicao(&comp, j - gap);
            if(bol != 1)
                return bol;
            while((j >= gap) && (comp->dados.num > temp.num))
            {
                aux->dados = comp->dados;

                aux = comp;
                j -= gap;
                comp = li->pInicio;

                if(j - gap > 0)
                {
                    bol = encontraNoPosicao(&comp, j - gap);
                    if(bol != 1)
                        return bol;
                }
            }

            aux->dados = temp;
        }
    }

    return 1;
}
short heapSort(lista* li)
{
    elem* no;
    register long i;
    short bol;

    if( !li )
        return -1;

    if( listaVazia(li) )
        return 0;

    for( i = li->qtd/2 - 1; i >= 0; --i )
    {
        bol = heapify(li->pInicio, li->qtd, i);
        if( bol != 1 )
            return bol;
    }

    for( i = li->qtd - 1, no = li->pFinal; (i >= 1) && (no != NULL); --i, no = no->ant )
    {
        fazTroca(&(li->pInicio->dados), &(no->dados));

        bol = heapify(li->pInicio, i, 0);
        if(bol != 1)
            return bol;
    }

    if( (i == 0) && (no == NULL) )
        return 0;

    return 1;
}
