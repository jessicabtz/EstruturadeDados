#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila{
	int inicio, fim, qtd;
	int vet[MAX];
};

Fila CriaFila(){
	Fila f = (Fila) malloc(sizeof(struct fila));
	if(f != NULL){
		f->inicio = 0;
		f->fim = 0;
		f->qtd = 0;
	}
	return f;
}

Fila LiberaFila(Fila f){
	free(f);
	return NULL;
}

int TamanhoFila(Fila f){
	if(f == NULL){
		return -1;
	}else{
		return f->qtd;
	}
}

int FilaCheia(Fila f){
	if(f == NULL){
        return -1;
    }
    if(f->qtd == MAX){
        return 1;
    }
	else{
		return 0;
    }
}

int FilaVazia(Fila f){
	if(f == NULL){
        return -1;
    }
	if(f->qtd == 0){
        return 1;
    }
	else{
		return 0;
    }
}

int Insere(Fila f, int valor){
	if(f == NULL){
        return 0;
	}
	if(FilaCheia(f)){
        printf("\n A fila esta cheia!");
        return 0;
    }

	f->vet[f->fim] = valor;
	f->fim = (f->fim+1);
	f->qtd++;
	return 1;
}

int Remove(Fila f){
	if(f == NULL || FilaVazia(f)){
        printf("\n A fila esta vazia!");
        return 0;
    }

	f->inicio = (f->inicio+1) ;
	f->qtd--;
    printf("\n O elemento %d foi removido!", f->vet[f->inicio -1]);
	return 1;
}

void Imprime(Fila f){
    if(FilaVazia(f)){
        printf("\n A fila esta vazia!");
    }
    for(int i=f->inicio; i<=(f->fim)-1; i++){
        printf("\n [%d]", f->vet[i]);
    }
}
