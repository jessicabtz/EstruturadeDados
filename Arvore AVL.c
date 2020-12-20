#include <stdio.h>
#include <stdlib.h>
#include <math.h>

///Diego Maia
///Guilherme Silva
///Jéssica Beatriz
///Thyago Azeredo

typedef struct arvore{
  int info ;
  int fb;
  struct arvore *esq;
  struct arvore *dir;
}AVL;

AVL *inicia(AVL *a){
    return NULL;
}

AVL *Libera(AVL* a){
    if(a!=NULL){
        a->esq = Libera(a->esq);
        a->dir = Libera(a->dir);
        free(a);
    }
    return NULL;
}

int altura (AVL *arv){
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

AVL *ler_arvore(FILE *arq){
 	char c;
  	int n;

  	fscanf(arq, "%c", &c);	 // ler os parenteses
  	fscanf(arq, "%d", &n);   //  ler os numeros

  	if(n==-1){
        fscanf(arq, "%c", &c);
        return NULL;
      }
  	else{
        AVL *a=(AVL*)malloc(sizeof(AVL));
        a->info = n;
        a->esq = ler_arvore(arq);
        a->dir = ler_arvore(arq);
        fscanf(arq, "%c", &c); // aqui vai fechando os parenteses
        return a;
      }
}

void ajustar_fb(AVL* a){
    int he, hd;
    if(a!=NULL){
        he = altura(a->esq);
        hd = altura(a->dir);
        a->fb = hd-he;

        ajustar_fb(a->esq);
        ajustar_fb(a->dir);
    }
}

AVL *le_avl(FILE *arq){
    AVL *arv;
    arv = ler_arvore(arq);
    ajustar_fb(arv);

    return arv;
}

void imprimirpre (AVL *arv){
	if (arv != NULL){
        printf ("\n \t %d \t", arv->info);
        imprimirpre(arv->esq);
        imprimirpre(arv->dir);
	}
}

void imprimirpos (AVL *arv){
	if (arv != NULL){
        imprimirpos(arv->esq);
        imprimirpos(arv->dir);
        printf ("\n \t %d \t", arv->info);
	}
}

void imprimirordem (AVL *arv){
	if (arv != NULL){
        imprimirordem(arv->esq);
        printf ("\n \t %d \t", arv->info);
        imprimirordem(arv->dir);
	}
}

void imprimirnivel (AVL *arv, int cont, int nivel){

    if (arv != NULL){
      if (cont == nivel)
        printf ("%d  ",arv->info);
      else {
        imprimirnivel(arv->esq,cont+1,nivel);
        imprimirnivel(arv->dir,cont+1,nivel);
        }
      }
}

void imprimirEmLargura (AVL *arv){
	for (int cont =0; cont < altura(arv); cont ++){
      imprimirnivel (arv,0,cont);
    }
}

int Nivel(AVL *a, int elem, int nv){

   if(a!=NULL){
        if(elem == a->info)
            return nv;
        else if(elem < a->info)
            return Nivel(a->esq, elem, nv +1);
        else
            return Nivel(a->dir, elem, nv + 1);
   }
}

int ImprimeFolhas(AVL *a, int x){
    if(a != NULL){
        if(a->info >= x)
            return ImprimeFolhas(a->esq,x);
        else{
            ImprimeFolhas(a->esq,x);
            ImprimeFolhas(a->dir,x);
            if(a->esq == NULL && a->dir == NULL){
                printf("%d ",a->info);
                return 1;
            }
        }
    }else
        return 0;
}

int Existe(AVL *a, int x){
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

AVL *rotacao_es(AVL *arv){ // rotação esquerda simples
    AVL *a = arv;
    AVL *b = a->dir;

    a->dir = b->esq;
    b->esq = a;

    if( b->fb == 1){
        a->fb = 0;
        b->fb = 0;

    }else{
        a->fb = 1;
        b->fb = -1;
    }

    arv = b;
    return arv;
}

AVL *rotacao_ed(AVL * arv){//rotação esquerda dupla
    AVL *a = arv;
    AVL *c = a->dir;
    AVL *b = c->esq;

    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;

    switch(b->fb){
        case -1:
            a->fb = 0;
            c->fb = 1;
            break;
        case 0:
            a->fb = 0;
            c->fb = 0;
            break;
        case 1:
            a->fb = -1;
            c->fb = 0;
            break;
    }
    b->fb = 0;
    arv   = b;

    return arv;
}

AVL *rotacao_esq (AVL *arv){

    if (arv->dir->fb == -1)
        arv = rotacao_ed(arv);
    else
        arv = rotacao_es(arv);
    return arv;
}

AVL *rotacao_ds(AVL *arv){//rotação direita simples
    AVL *a = arv->esq;
    AVL *b = arv;

    b->esq = a->dir;
    a->dir = b;

    if (a->fb == -1){

        a->fb = 0;
        b->fb = 0;

    }else{

        a->fb = 1;
        b->fb = -1;

    }
    arv = a;
    return arv;
}

AVL *rotacao_dd(AVL *arv){//rotação esquerda dupla

    AVL *c = arv;
    AVL *a = c->esq;
    AVL *b = a->dir;

    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;

    switch(b->fb){
        case -1:
            a->fb = 0;
            c->fb = 1;
            break;
        case 0:
            a->fb = 0;
            c->fb = 0;
            break;
        case +1:
            a->fb = -1;
            c->fb = 0;
            break;
    }

    b->fb = 0;
    arv = b;
    return arv;
}

AVL *rotacao_dir(AVL *arv){
    if (arv->esq->fb == 1)
        arv = rotacao_dd(arv);
    else
        arv = rotacao_ds(arv);
    return arv;
}

AVL *Inserir(AVL *arv, int x, int *hMudou){
    if (arv == NULL){

        arv = (AVL*) malloc (sizeof(AVL));
        arv->info = x;
        arv->esq  = NULL;
        arv->dir  = NULL;
        arv->fb   = 0;
        *hMudou   = 1;

    }else{
        if (x <= arv->info){

            arv->esq = Inserir (arv->esq,x,hMudou);

            if (*hMudou == 1){

                switch (arv->fb){

                    case -1:
                        arv = rotacao_dir(arv);
                        *hMudou = 0;
                        break;
                    case 0:
                        arv->fb = -1;
                        *hMudou = 1;
                        break;
                    case +1:
                        arv->fb = 0;
                        *hMudou = 0;
                        break;
                }
            }

        }else{

            arv->dir = Inserir(arv->dir, x, hMudou);

            if (*hMudou == 1){

                switch (arv->fb){

                    case -1:
                        arv->fb = 0;
                        *hMudou = 0;
                        break;
                    case 0:
                        arv->fb = 1;
                        *hMudou = 1;
                        break;
                    case +1:
                        arv = rotacao_esq(arv);
                        *hMudou = 0;
                        break;
                }
            }
        }
    }
    return arv;
}

AVL *Remover (AVL *arv, int x, int *hMudou){
    if(arv != NULL){

        if(arv->info == x){

            if(arv->esq == NULL && arv->dir == NULL){

                arv = Libera(arv);
                *hMudou = 1;
                return NULL;

            }else if(arv->esq == NULL || arv->dir == NULL){

                AVL *aux;
                if(arv->esq == NULL)
                    aux = arv->dir;
                else
                    aux = arv->esq;
                *hMudou = 1;
                return aux;

            }else{

                AVL *maior_esq = arv->esq;
                while(maior_esq->dir != NULL)
                    maior_esq = maior_esq->dir;

                arv->info = maior_esq->info;
                arv->esq  = Remover(arv->esq, arv->info, hMudou);

                if(*hMudou == 1){

                    switch(arv->fb){

                        case -1:
                            arv->fb = 0;
                            *hMudou = 1;
                            break;
                        case 0:
                            arv->fb = 1;
                            *hMudou = 0;
                            break;
                        case 1:
                        {
                            int aux = arv->dir->fb;
                            arv = rotacao_esq(arv);

                            if(aux == 0)
                                *hMudou = 0;
                            else
                                *hMudou = 1;
                            break;
                        }
                    }
                }
            }

        }else if(x < arv->info){

            arv->esq = Remover(arv->esq,x,hMudou);

            if(*hMudou == 1){

                switch(arv->fb){
                    case -1:
                        arv->fb = 0;
                        *hMudou = 1;
                        break;
                    case  0:
                        arv->fb = 1;
                        *hMudou = 0;
                        break;
                    case  1:
                    {
                        int aux = arv->dir->fb;
                        arv = rotacao_esq(arv);

                        if(aux == 0)
                            *hMudou = 0;
                        else
                            *hMudou = 1;
                        break;
                    }
                }
            }
        }else{

            arv->dir = Remover(arv->dir,x,hMudou);

            if(*hMudou == 1){
                switch(arv->fb){
                    case  1:
                        arv->fb = 0;
                        *hMudou = 1;
                        break;
                    case  0:
                        arv->fb = -1;
                        *hMudou = 1;
                        break;
                    case -1:
                    {
                        int aux = arv->esq->fb;
                        arv = rotacao_dir(arv);

                        if(aux == 0)
                            *hMudou = 0;
                        else
                            *hMudou = 1;
                        break;
                    }
                }
            }
        }
         return arv;
    }
}

void Menu(){
    int  op, fi, x, num,n,nivel;
    char nome[20];
    AVL  *a;

    int *hMudou = 0;
    a           = inicia(a);


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
                	a = le_avl(arq);
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
                a = Inserir(a,x,&hMudou);
                break;

            case 7:
                printf("Digite o valor que deseja remover\n");
                scanf("%d",&x);
                a = Remover(a,x,&hMudou);
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
