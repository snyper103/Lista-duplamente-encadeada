#ifndef STDLD_H_INCLUDED
#define STDLD_H_INCLUDED
#define MAX 100

typedef struct informacao
{
    unsigned long num;
}info;

typedef struct elementos elem;
typedef struct noDiscritor lista;

short criaLista( lista** );
short criaNo( elem**, info );
short liberaLista( lista* );

short listaVazia( lista* );
short listaCheia( lista* );
short listaTamanho( lista* );

short insereListaInicio( lista*, info );
short insereListaMeio( lista*, info );
short insereListaFinal( lista*, info );

short removeInicio( lista* );
short removeMeio( lista*, info );
short removeFinal( lista* );

short consultaListaPos( lista*, unsigned long, info* );
short consultaListaCont( lista*, unsigned long, info* );

short imprimeConteudo( lista* );
short imprimeElemento( lista*, unsigned long );

short insereFileListaInicio( lista*, const char* );
short insereFileListaMeio( lista*, const char* );
short insereFileListaFinal( lista*, const char* );

short insereListaFile( lista*, const char* );
short insereFileRandom( const char* );

short shellSort( lista* );
short heapSort( lista* );

#endif
