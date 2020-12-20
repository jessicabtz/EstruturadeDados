#include <stdio.h>
#include <stdlib.h>

#define N 100

int indice_filho_esq(int x, int total_elementos){
    int indice;

    indice = (2 * x) + 1;
    if(x >= total_elementos || indice >= total_elementos)
        return -1;
    else
        return indice;
}

int indice_filho_dir(int x, int total_elementos){
    int indice;

    indice = (2 * x) + 2;
    if(x >= total_elementos || indice >= total_elementos)
        return -1;
    else
        return indice;
}

int indice_pai(int x, int total_elementos){

    int indice;
    indice = (int)floor((x-1)/2);

    if(x <= 0 || x >= total_elementos)
        return -1;
    else
        return indice;
}

void ajustar_subindo(int *heap, int pos, int total_elementos){
    int pai,aux;

    if(pos != -1){
        pai = indice_pai(pos, total_elementos);
        if(pai != -1){
            if(heap[pos] < heap[pai]){
                aux = heap[pos];
                heap[pos] = heap[pai];
                heap[pai] = aux;

                ajustar_subindo(heap,pai,total_elementos);
            }
        }
    }

}

void ajustar_descendo(int *heap, int pos, int total_elementos){

    int esq = indice_filho_esq(pos, total_elementos);

    if(pos != -1 && esq != -1){

        int dir                = indice_filho_dir(pos,total_elementos);
        int indice_menor_filho = esq;

        if(dir!= -1 && heap[dir] < heap[indice_menor_filho])
            indice_menor_filho = dir;
        if(heap[indice_menor_filho] < heap[pos]){
            int aux                  = heap[pos];
            heap[pos]                = heap[indice_menor_filho];
            heap[indice_menor_filho] = aux;

            ajustar_descendo(heap, indice_menor_filho, total_elementos);
        }
    }
}

void inserir(int *heap, int x, int *total_elementos){
    int i;
    heap[*total_elementos] = x;
    *total_elementos +=1;

    ajustar_subindo(heap, *total_elementos-1, *total_elementos);

    for(i = 0; i < *total_elementos; i++){
        printf("%d ",heap[i]);
    }
    printf("\n");
}

int remover(int *heap, int *total_elementos){
    if(*total_elementos == 0)
        return -1;
    else{
        int retorno = heap[0];
        heap[0] = heap[*total_elementos-1];
        *total_elementos -=1;

        ajustar_descendo(heap, 0, *total_elementos);
        return retorno;
    }
}

void menu(){
    int heap[N];
    int total_elementos = 0;
    int op,x;

    do{
        printf("O que deseja fazer? \n1- Inserir um elemento x no heap\n2-Remover um elemento\n3-Sair\n");
        scanf("%d",&op);

        switch(op){
            case 1:
                printf("Digite x\n");
                scanf("%d",&x);
                inserir(heap,x, &total_elementos);
                break;
            case 2:
                x = remover(heap, &total_elementos);
                if(x == -1)
                    printf("Nao ha elemento para remover\n");
                else
                    printf("O elemento removido foi: %d\n",x);
                break;
            default:
                if(op!=3)printf("Opcao invalida\n\n");
        }
    }while(op != 3);
}

void main(){
    menu();
}
