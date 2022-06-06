#include "stdld.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main()
{
    lista* li;
    short bol;

    setlocale(LC_ALL, "");

    bol = criaLista(&li);
    if(bol == 1)
        printf("Lista criada com sucesso.\n");
    else
    {
        printf("Erro ao criar a lista.\n");
        exit(1);
    }

    bol = insereFileRandom("in.txt");
    if(bol == 1)
        printf("File criado e inserido com sucesso.\n");
    else
    {
        printf("Erro ao criar e inserir file.\n");
        exit(1);
    }

    bol = insereFileListaInicio(li, "in.txt");
    if(bol == 1)
        printf("File inserido na lista com sucesso.\n");
    else
    {
        if(bol == -1)
        {
            printf("lista inexistente.\n");
            exit(1);
        }

        else
        {
            printf("Erro ao criar e inserir file.\n");
            exit(1);
        }
    }

    bol = heapSort(li);
    if(bol == 1)
        printf("Lista organizada com sucesso.\n");
    else
    {
        if(bol == -1)
        {
            printf("lista inexistente.\n");
            exit(1);
        }

        else
        {
            printf("Erro ao organizar a lista.\n");
            exit(1);
        }
    }

    bol = insereListaFile(li, "out.txt");
    if(bol == 1)
        printf("Lista inserida no file com sucesso.\n");
    else
    {
        if(bol == -1)
        {
            printf("lista inexistente.\n");
            exit(1);
        }

        else
        {
            printf("Erro ao criar e inserir lista no file.\n");
            exit(1);
        }
    }

    bol = liberaLista(li);
    if(bol == 1)
        printf("Lista liberada com sucesso.\n");
    else
    {
        printf("Erro ao liberar a lista.\n");
        exit(1);
    }


    return 0;
}
