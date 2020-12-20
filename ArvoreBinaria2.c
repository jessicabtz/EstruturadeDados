#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Diego Maia
//Guilherme Silva
//Jéssica Beatriz
//Thyago Azeredo

///Cria, inicia e libera a estrutura da arvore
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

///Le a arvore de um arquivo
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

///Calcula altura da arvore
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

///Imprime a arvore
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

void imprimirEmLargura (arvore *arv){
	for (int cont =0; cont < altura(arv); cont ++){
      imprimirnivel (arv,0,cont);
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

void mostrarNivel(arvore *a, int n, int cont){

	if(a!= NULL){
        if(a->info == n){
            printf("Nivel: %d\n\n", cont);
        }else{
            mostrarNivel(a->esq, n, cont+1);
            mostrarNivel(a->dir, n, cont+1);
        }
	}
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

///Checa caracteristicas da arvore: balanceamento,existencia de x,qtd de elementos e se e cheia
int Balanceada(arvore *a){

    if(a==NULL)
        return 0;
    else{

        if(abs(altura(a->esq)-altura(a->dir))<=1)
            return 0 + Balanceada(a->esq) + Balanceada(a->dir);
        else
            return 1 + Balanceada(a->esq) + Balanceada(a->dir);
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
    else if (arv != NULL){
        count ++;
        soma = count + qtdelementos(arv->esq) + qtdelementos(arv->dir);
    }
    return soma;
}

int cheia (arvore *arv){
	int qtd = qtdelementos (arv);
  	int h = altura(arv);
  	if (qtd == (pow(2,h)-1) )
        return 1;
  	else
        return 0;
}

void Menu(){
    int op, fi, x, num,n,nivel; // op-para gerenciar as opções do menu geral;fi-para gerenciar as opções do submenu de impressão; x-para receber o numero que se deseja saber se existe na arvore; num-para o numero de elementos na arvore;
    char nome[20]; // String pra receber o nome do arquivo texto
    arvore *a;
    a = inicia(a);

    do{//Menu principal
        printf("O que deseja fazer?\n1-Ler uma arvore;\n2-Imprimir arvore;\n3-Verificar se um elemento existe na arvore;\n4-Numero de elementos na arvore;\n5-Imprimir os nos folhas da arvore;\n6-Verificar se a arvore esta balanceada;\n7-Verificar se uma arvore e cheia;\n8-Imprimir o nivel de um no x;\n9-Sair.\n");
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

            case 4:// Contar numero de elementos na arvore
                num = qtdelementos(a);
                printf("Existe(m) %d elemento(s)\n\n", num);
                break;

            case 5:
                ImprimeFolhas(a);
                printf("\n");
                break;

            case 6://verificar se a arvore esta balanceada
                if(Balanceada(a))
                    printf("Nao Balanceada!\n\n");
                else
                    printf("Esta balanceada!\n\n");
                break;

            case 7://verificar se a arvore e cheia
                if(cheia(a)==1)
                    printf("A arvore e cheia\n\n");
                else
                    printf("A arvore nao e cheia\n\n");
                break;

            case 8://imprimir o nivel de um no
                printf("Insira o numero que deseja consultar o nivel\n");
                scanf("%d",&x);
                if(Existe(a,x)==1)
                    mostrarNivel(a,x,0);
                else
                    printf("Numero nao existe na arvore");
                break;

            default:
                if(op!=9)printf("Opcao invalida\n\n");
        }
    }while(op!=9);
a = Libera(a);
}

int main (){
	Menu();
}
