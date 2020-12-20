#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main(){
    int op, valor;

    Fila f;
    f = CriaFila();

    do{
        printf("\n\n");
        printf(" O que deseja fazer?\n\n 1-Inserir;\n 2-Remover;\n 3-Imprimir fila;\n 4-Sair; \n\n Opcao: ");

        scanf("%d", &op);

        switch (op){
            case 1:
                printf("\n Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                Insere(f, valor);
                break;

            case 2:
                Remove(f);
                break;

            case 3:
                Imprime(f);
                break;

            case 4:
                return 0;

            default: printf("Opcao invalida!");

        }
    }while(op>=1 && op<=4);

     f = LiberaFila(f);
     printf("\n Fila liberada!");

    return 0;
}

