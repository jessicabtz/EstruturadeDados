#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int destino;
    int custo;
    struct lista *prox;
}lista;

void inicializar(lista **g, int n){
    for(int i=0; i<=n; i++)
        g[i] = NULL;
}

int existe(lista*l, int x){
    if(l!=NULL){
        if(l->destino == x)
            return 1;
        else
            return existe(l->prox, x);
    }else
        return 0;
}

lista *inserirLista(lista *l, int dest, int cost){
    if(existe(l, dest) == 0){
        lista *no = (lista *)malloc(sizeof(lista));
        no->destino = dest;
        no->custo = cost;
        no->prox = l;
        return no;
    }else{
        printf("Essa aresta ja existe\n");
        return l;
    }
}

void inserirAresta(lista **g, int origem, int destino, int custo){
    g[origem] = inserirLista(g[origem], destino, custo);
}

lista *removeLista(lista *l, int dest){
    lista *aux;
    if(l == NULL)
        return l;
    else{
        if(l->destino == dest){
            aux = l;
            l = l->prox;
            free(aux);
        }
        else
            l->prox = removeLista(l->prox, dest);
        return l;
    }
}

void removerAresta(lista **g, int origem, int destino){
    g[origem] = removeLista(g[origem], destino);
}

void imprimirLista(lista *l){
    if(l != NULL){
        printf("(%d, %d) ", l->destino, l->custo);
        imprimirLista(l->prox);
    }
}

void imprimirGrafo(lista **g, int n){
    for(int i=1; i<=n; i++){
        printf("%d - ", i);
        imprimirLista(g[i]);
        printf("\n");
    }
}

int grauEnt(lista *l, int n){
    int cont = 0;
    while(l != NULL){
        if(l->destino == n)
            cont ++;
        l = l->prox;
    }
    return cont;
}

int grauSaida(lista *l){
    int cont = 0;
    while(l !=NULL){
        cont++;
        l = l->prox;
    }
    return cont;
}

void grausVertice(lista **g, int vertice, int tam){
    int grauent = 0, grausaida = 0;
    for(int i=1; i<=tam; i++)
        grauent += grauEnt(g[i], vertice);
    grausaida = grauSaida(g[vertice]);
    printf("Grau de saida: %d\nGrau entrada: %d\n", grausaida, grauent);
}

int completo(lista **g, int tam){
    lista *aux;
    for(int i=1; i<=tam; i++){
        aux = g[i];
        int cont = 0;
        while(aux != NULL){
            cont++;
            aux = aux->prox;
        }
        if(cont != tam-1)
            return 0;
    }
    return 1;
}

int existe2(int *vet, int v, int n){
    for(int i=0; i<n; i++){
        if(vet[i]==v)
            return 1;
    }
    return 0;
}

void caminhos(lista **g, int dest, int *vet, int pos){ // vet[0] = origem na primeira vez
    if(vet[pos-1] == dest){
        for(int i=0; i<pos; i++)
            printf("%d ", vet[i]);
        printf("\n");
    }else{
        lista *p = g[vet[pos-1]]; // p recebe o vertice atual que nao e o destino
        while(p != NULL){ // se tem caminho para outro vertice
            if(!existe2(vet, p->destino, pos)){ // ve se o vertice atual ja nao foi usado nesse caminho atual
                vet[pos] = p->destino; // insere o vertice o proximo vertice no caminho
                caminhos(g, dest, vet, pos+1); // chama para adicionar na proxima posicao do caminho
            }
            p = p->prox; // caso o vertice ja exista no caminho atual entao recebe o proximo
        }
    }
}

void caminhoCurto(lista **g, int dest, int *vet, int pos, int *aux, int *tam){
    if(vet[pos-1] == dest){
        //fazer um vetor auxiliar receber esse caminho se tamanho pos dele for menor que o pos anterior
        if(pos < *tam){
            for(int i=0; i<pos; i++)
                aux[i] = vet[i];
            *tam = pos;
        }
    }else{
        lista *p = g[vet[pos-1]];
        while(p != NULL){
            if(!existe2(vet, p->destino, pos)){
                vet[pos] = p->destino;
                caminhoCurto(g, dest, vet, pos+1, aux, tam);
            }
            p = p->prox;
        }
    }
}

void caminhoBarato(lista **g, int dest, int *vet, int pos, int *aux, int *tam, int *custo, int *vetCusto){
    if(vet[pos-1] == dest){
        int temp = 0;
        for(int i=1; i<pos; i++)
            temp += vetCusto[i];
        if(*custo == 0 || temp<*custo){ //se for a primeira vez ou se custo atual menor do que o anterior, atualiza o vetor custo
            *custo = temp;
            for(int i=0; i<pos; i++)
                aux[i] = vet[i];
            *tam = pos;
        }
    }else{
        lista *p = g[vet[pos-1]];
        while(p != NULL){
            if(!existe2(vet, p->destino, pos)){
                vet[pos] = p->destino;
                vetCusto[pos] = p->custo;
                caminhoBarato(g, dest, vet, pos+1, aux, tam, custo, vetCusto);
            }
            p = p->prox;
        }
    }
}

//Menu principal do programa
void Menu(){

    int op, o, d, c, v, n, tam;
    printf("Quantos vertices tera o grafo? ");
    scanf("%d", &n);
    lista **g; // declaracao dinamica
    g = (lista**)malloc((n+1)*sizeof(lista*)); //onde n e o numero de nos do grafo e n+1 pq a 0 nao e usada
    inicializar(g, n+1);
    int vet[n], vetAux[n], vetCusto[n];

    do{//Menu principal
        printf("O que deseja fazer?\n1-Inserir uma aresta no grafo;\n2-Remover uma aresta do grafo;\n3-Imprimir grafo;\n4-Imprimir os graus de entrada e saida de um vertice;\n5-Verificar se um grafo e completo;\n6-Imprimir todos os caminhos entre uma origem e um destino;\n7-Imprimir o caminho mais curto entre uma origem e um destino;\n8-Imprimir o caminho de menor custo entre uma origem e um destino;\n9-Sair.\n");
        scanf("%d", &op);

        switch (op){
            case 1:
                printf("Qual a origem?");
                scanf("%d", &o);
                printf("Qual o destino?");
                scanf("%d", &d);
                printf("Qual o custo?");
                scanf("%d", &c);
                if(o > n || o <=0 || d > n || d <=0 || o == d)
                    printf("Valores de vertice invalidos.\n");
                else
                    inserirAresta(g, o, d, c);
                break;

            case 2:
                printf("Qual a origem?");
                scanf("%d", &o);
                printf("Qual o destino?");
                scanf("%d", &d);
                if(o > n || o <=0 || d > n || d <=0)
                    printf("Valor de vertice invalido.\n");
                else
                    removerAresta(g, o, d);
                break;

            case 3:
                imprimirGrafo(g, n);
                break;

            case 4:
                printf("Qual vertice deseja saber os graus?");
                scanf("%d", &v);
                grausVertice(g, v, n);
                break;

            case 5:
                if(completo(g, n))
                    printf("Grafo e completo\n");
                else
                    printf("Grafo nao e completo\n");
                break;
            case 6:
                printf("Qual a origem?");
                scanf("%d", &o);
                printf("Qual o destino?");
                scanf("%d", &d);
                vet[0] = o;
                caminhos(g, d, vet, 1);
                break;

            case 7:
                tam = n;
                printf("Qual a origem?");
                scanf("%d", &o);
                printf("Qual o destino?");
                scanf("%d", &d);
                vet[0] = o;
                caminhoCurto(g, d, vet, 1, vetAux, &tam);
                printf("Menor caminho: ");
                for(int i=0; i<tam; i++)
                    printf("%d ", vetAux[i]);
                printf("\n\n");
                break;
            case 8:
                c = 0;
                tam = n;
                printf("Qual a origem?");
                scanf("%d", &o);
                printf("Qual o destino?");
                scanf("%d", &d);
                vet[0] = o;
                caminhoBarato(g, d, vet, 1, vetAux, &tam, &c, vetCusto);
                printf("Caminho mais barato: ");
                for(int i=0; i<tam; i++)
                    printf("%d ", vetAux[i]);
                printf("\n\n");
                break;

            default:
                if(op!=9)printf("Opcao invalida\n\n");
        }
    }while(op!=9);

}

int main()
{
    Menu();

    return 0;
}
