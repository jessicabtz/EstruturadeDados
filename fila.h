#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#define MAX 5

typedef struct fila *Fila;
Fila CriaFila();
Fila LiberaFila(Fila f);
int TamanhoFila(Fila f);
int FilaCheia(Fila f);
int FilaVazia(Fila f);
int Insere(Fila f, int valor);
int Remove(Fila f);
void Imprime(Fila f);


#endif // FILA_H_INCLUDED
