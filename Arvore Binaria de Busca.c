#include <stdio.h>
#include <stdlib.h>
#include <math.h>

///Diego Maia
///Guilherme Silva
///Jéssica Beatriz
///Thyago Azeredo

typedef struct arvore{
  int info ;
  struct arvore *esq;
  struct arvore *dir;
}arvore;

arvore *inicia(arvore *a){
    return NULL;
}

arvore *Libera(arvore* a){
    if(a!=NULL){
        a->esq = Libera(a->esq);
        a->dir = Libera(a->dir);
        free(a);
    }
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

int altura (arvore *arv){
  int he, hd;
  if (arv == NULL)
	return 0;
  else
  {
  	he= altura(arv->esq);
    	hd = altura(arv->dir);
    	if (he > hd)
            return he +1;
    	else
            return hd+1;
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

void imprimirnivel (arvore *arv, int cont, int nivel){

    if (arv != NULL){
      if (cont == nivel)
        printf ("%d  ",arv->info);
      else {
        imprimirnivel(arv->esq,cont+1,nivel);
        imprimirnivel(arv->dir,cont+1,nivel);
        }
      }
}

void imprimirEmLargura (arvore *arv){
	for (int cont =0; cont < altura(arv); cont ++){
      imprimirnivel (arv,0,cont);
    }
}

int Nivel(arvore *a, int elem, int nv){

   if(a!=NULL){
      if(elem == a->info)
         return nv;
      else if(elem < a->info)
          Nivel(a->esq, elem, nv +1);
      else
          Nivel(a->dir, elem, nv + 1);
   }
}

int ImprimeFolhas(arvore *a, int x){
    if(a != NULL){
        if(a->info >= x)
            ImprimeFolhas(a->esq,x);
        else{
            ImprimeFolhas(a->esq,x);
            ImprimeFolhas(a->dir,x);
            if(a->esq == NULL && a->dir == NULL){
                printf("%d ",a->info);
                return 1;
            }
        }
    }
}

int Existe(arvore *a, int x){
	if(a == NULL){
		return 0;
	}else if(x == a->info){
		return 1;
	}
	else if(x < a->info){
		return Existe(a->esq, x);
	}else{
		return Existe(a->dir, x);
	}
}

arvore *inserir(arvore *a, int x){
    if(a == NULL){
        a = (arvore*) malloc(sizeof(arvore));
        a->info = x;
        a->esq  = NULL;
        a->dir  = NULL;
    }else if(x <= a->info)
        a->esq = inserir(a->esq,x);
    else
        a->dir = inserir(a->dir,x);
    return a;
}

arvore *remover(arvore *a,int x){
    if(a!=NULL){
        if(a->info == x){
            if(a->esq == NULL && a->dir == NULL){
                a = Libera(a);
                return NULL;
            }else if(a->esq == NULL){
                arvore *aux = a->dir;
                a = Libera(a);
                return aux;
            }else if(a->dir == NULL){
                arvore *aux = a->esq;
                a = Libera(a);
                return aux;
            }else{
                arvore *aux = a->esq;
                while(aux ->dir != NULL)
                    aux = aux->dir;
                a->info = aux->info;
                a->esq = remover(a->esq,aux->info);
            }
        }else if(x < a->info)
            a->esq = remover(a->esq,x);
        else
            a->dir = remover(a->dir,x);
    }
    return a;
}

void Menu(){
    int op, fi, x, num,n,nivel; // op-para gerenciar as opções do menu geral;fi-para gerenciar as opções do submenu de impressão; x-para receber o numero que se deseja saber se existe na arvore; num-para o numero de elementos na arvore;
    char nome[20]; // String pra receber o nome do arquivo texto
    arvore *a;
    a = inicia(a);

    do{//Menu principal
        printf("O que deseja fazer?\n1-Ler uma arvore;\n2-Imprimir arvore;\n3-Verificar se um elemento existe na arvore;\n4-Imprimir o nivel de um no x;\n5-Imprimir folhas menores que um valor x;\n6-Inserir o no x na arvore;\n7-Remover o no x da arvore;\n8-Sair.\n");
        scanf("%d", &op);

        switch (op){
            case 1://Ler a arvore
                if(a != NULL)
                    a =Libera(a);

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
                    printf("De qual forma?\n1-Pre-ordem;\n2-em-ordem;\n3-pos-ordem;\n4-em largura.\n");
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
                        case 4:
                            imprimirEmLargura(a);
                            printf("\n\n");
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

            case 4://imprimir o nivel de um no
                printf("Insira o numero que deseja consultar o nivel\n");
                scanf("%d",&x);
                if(Existe(a,x)==1)
                    printf("Nivel: %d\n", Nivel(a,x,0));
                else
                    printf("Numero nao existe na arvore");
                break;

            case 5:
                printf("Digite o valor de x\n");
                scanf("%d",&x);
                n = ImprimeFolhas(a,x);
                if(n == 0)
                    printf("Nenhuma folha e menor que %d",x);
                printf("\n");
                break;

            case 6:
                printf("Digite o valor que deseja inserir\n");
                scanf("%d",&x);
                a = inserir(a,x);
                break;

            case 7:
                printf("Digite o valor que deseja remover\n");
                scanf("%d",&x);
                a = remover(a,x);
                break;

            default:
                if(op!=8)printf("Opcao invalida\n\n");
        }
    }while(op!=8);
a = Libera(a);
}

int main (){
	Menu();
}
