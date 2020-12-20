#include <stdio.h>
#include <stdlib.h>

//Diego Maia
//Guilherme Silva
//Jéssica Beatriz
//Thyago Azeredo

typedef struct arvore{
  int info;
  struct arvore *esq;
  struct arvore *dir;
}arvore;

arvore *inicia(arvore *a){
    return NULL;
}

arvore *LerArvore(FILE *arq){
 	char c;
  	int n;

  	fscanf(arq, "%c", &c);	 // ler os parenteses
  	fscanf(arq, "%d", &n);   //  ler os numeros

  	if(n==-1){
        fscanf(arq, "%c", &c);
        return NULL;
      }
  	else{
        arvore *a=(arvore*)malloc(sizeof(arvore));
        a->info = n;
        a->esq = LerArvore(arq);
        a->dir = LerArvore(arq);
        fscanf(arq, "%c", &c); // aqui vai fechando os parenteses
        return a;
      }
}

void imprimirpre (arvore *arv){
	if (arv != NULL){
        printf ("\n \t %d \t", arv->info);
        imprimirpre(arv->esq);
        imprimirpre(arv->dir);
	}
}

void imprimirpos (arvore *arv){
	if (arv != NULL){
        imprimirpos(arv->esq);
        imprimirpos(arv->dir);
        printf ("\n \t %d \t", arv->info);
	}
}

void imprimirordem (arvore *arv){
	if (arv != NULL){
        imprimirordem(arv->esq);
        printf ("\n \t %d \t", arv->info);
        imprimirordem(arv->dir);
	}
}

int Existe(arvore *a, int x){

  if (a==NULL)
     return 0 ;
  else{
     if(a->info==x)
        return 1;
     else
        return 0 + Existe(a->esq, x) + Existe(a->dir, x);
  }

}

int qtdelementos (arvore *arv){
int soma, count=0;
    if (arv == NULL)
        return 0;
    else if(arv != NULL){
        count ++;
        soma = count + qtdelementos(arv->esq) + qtdelementos(arv->dir);
    }
    return soma;
}


void ImprimeFolhas(arvore *a){
    if(a != NULL){
        if(a->esq == NULL && a->dir == NULL)
            printf("%d ",a->info);
        else{
            ImprimeFolhas(a->esq);
            ImprimeFolhas(a->dir);
        }
    }
}

arvore *Libera(arvore* a){
    if(a!=NULL){
        Libera(a->esq);
        Libera(a->dir);
        free(a);
        return NULL;
    }
}

void Menu(){
    int op, fi, x, num; // op-para gerenciar as opções do menu geral;fi-para gerenciar as opções do submenu de impressão; x-para receber o numero que se deseja saber se existe na arvore; num-para o numero de elementos na arvore;
    char nome[20]; // String pra receber o nome do arquivo texto
    arvore *a;
    a = inicia(a);

    do{//Menu principal
        printf("O que deseja fazer?\n1-Ler uma arvore;\n2-Imprimir arvore;\n3-Verificar se um elemento existe na arvore;\n4-Numero de elementos na arvore;\n5-Imprimir os nos folhas da arvore;\n6-Sair.\n");
        scanf("%d", &op);

        switch (op){
            case 1://Ler a arvore

                printf("Insira o nome do arquivo com extensao\n");
                scanf("%s", nome);
                FILE *arq;

                arq = fopen(nome, "r");
                if(!arq)
                  printf("Erro ao abrir o arquivo");
                else{
                	a = LerArvore(arq);
            	printf("Arvore lida com sucesso\n");
                  fclose(arq);
                }
                break;

            case 2:// Imprimir
                if(a == NULL)
                    printf("VAZIA");
                else{
                    printf("De qual forma?\n1-Pre-ordem;\n2-em-ordem;\n3-pos-ordem.\n");
                    scanf("%d", &fi);
                    switch (fi){
                        case 1:
                            imprimirpre(a);
                            printf("\n");
                            break;
                        case 2:
                            imprimirordem(a);
                            printf("\n");
                            break;
                        case 3:
                            imprimirpos(a);
                            printf("\n");
                            break;
                        default:
                            printf("opcao invalida\n\n");
                    }
                }break;

            case 3:// Verificar se um elemento existe
                printf("Digite o numero a ser verificado\n");
                scanf("%d", &x);

                if(Existe(a, x))
                    printf("Existe\n\n");
                else
                    printf("Nao existe\n\n");

                break;

            case 4:// Contar numero de elementos na arvore
                num = qtdelementos(a);
                printf("Existe(m) %d elemento(s)\n\n", num);
                break;

            case 5:
                ImprimeFolhas(a);
                printf("\n");
                break;

            default:
                if(op!=6)printf("Opcao invalida\n\n");
        }
    }while(op!=6);
    a = Libera(a);

}

int main (){
	Menu();
}
