#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50

typedef struct pessoas{
    int tipo;
    void *item;
    struct pessoas *prox;
}Pessoa;

typedef struct professores{
    int mat;
    char nome[N];
    float salario;
}Professor;

typedef struct alunos{
    int mat;
    char nome[N];
    char curso[N];
    int ano;
}Aluno;

Pessoa* inicializar(){
    return NULL;
}

Pessoa *existe(Pessoa *p, int mat){
    if(p != NULL){
        Pessoa *pe;
        for(pe = p; pe != NULL; pe = pe->prox){
            if(pe->tipo == 1){
                Professor *pro = (Professor*)pe->item;
                if(pro->mat == mat)
                    return pe;
            } else if(pe->tipo == 2){
                Aluno *a = (Aluno*)pe->item;
                if(a->mat == mat)
                    return pe;
            }
        }
        return NULL;
    }
    return NULL;
}

Pessoa* inserir(Pessoa* l, int cod){
    Pessoa* novo = (Pessoa*)malloc(sizeof(Pessoa));
    int mat;

    printf("Digite a matricula: ");
    scanf("%d", &mat);
    fflush(stdin);
    Pessoa *x = existe(l, mat);
    if(x == NULL){

        if(cod == 1){

            novo->tipo = 1;
            Professor *p = (Professor*)malloc(sizeof(Professor));
            p->mat = mat;
            printf("Digite o nome: ");
            gets(p->nome);
            fflush(stdin);
            printf("Digite o salario: ");
            scanf("%f", &p->salario);
            novo->item = p;

        } else if (cod == 2){

            novo->tipo = 2;
            Aluno *a = (Aluno*)malloc(sizeof(Aluno));
            a->mat = mat;
            printf("Digite o nome: ");
            gets(a->nome);
            fflush(stdin);
            printf("Digite o curso: ");
            gets(a->curso);
            fflush(stdin);
            printf("Digite o ano de ingresso: ");
            scanf("%d", &a->ano);
            novo->item = a;

        }
        novo->prox = l;
        return novo;

    }else{
        printf("Matricula ja cadastrada.\n");
        return l;
    }
}

void imprimir(Pessoa* p){
    Pessoa *q;
    for(q = p; q != NULL; q = q->prox){
        if(q->tipo == 1){
            Professor *pro = (Professor*)q->item;
            printf("%d\n%s\n%.2f\n", pro->mat, pro->nome, pro->salario);
        }else if(q->tipo == 2){
            Aluno *a = (Aluno*)q->item;
            printf("%d\n%s\n%s\n%d\n", a->mat, a->nome, a->curso, a->ano);
        }
        printf("\n");
    }
}

Pessoa *remover(Pessoa *p, int mat){
    Pessoa *pe = existe(p, mat);
    if(pe == NULL){
        printf("Pessoa nao encontrada.\n");
        return p;
    }else{
        if(pe->tipo == 1){
            Professor *pro = (Professor*)pe->item;
            Pessoa *q = pe;
            pe = pe->prox;
            free(q);
            return p;
        }else if(pe->tipo == 2){
            Aluno *a = (Aluno*)pe->item;
            Pessoa *q = pe;
            pe = pe->prox;
            free(q);
            return p;
        }
    }
}

void buscar_pessoa(Pessoa *p, int mat){
    Pessoa *pe = existe(p, mat);
    if(pe == NULL)
        printf("Pessoa nao encontrada.\n");
    else{
        if(pe->tipo == 1){
            Professor *pro = (Professor*)pe->item;
            printf("\nMatricula: %d\nNome: %s\nSalario: %.2f\n\n", pro->mat, pro->nome, pro->salario);
        }else if (pe->tipo ==2){
            Aluno *a = (Aluno*)pe->item;
            printf("\nMatricula: %d\nNome: %s\nCurso: %s\nAno de ingresso: %d\n\n", a->mat, a->nome, a->curso, a->ano);
        }
    }
}

int conta_alunos(Pessoa *p, char* curso){
    if(p == NULL)
        return 0;
    else{
        Pessoa *pe;
        int cont = 0;
        for(pe = p; pe != NULL; pe = pe->prox){
            if(pe->tipo == 2){
                Aluno *a = (Aluno*)pe->item;
                if(strcmp(strlwr(curso), strlwr(a->curso))==0)
                    cont++;
            }
        }
        return cont;
    }
}

void imprimir_professores(Pessoa* p){
    if(p == NULL)
        printf("Nao existem professores cadastrados.\n");
    else{
        Pessoa *pe;
        int aux = 0;
        for(pe = p; pe != NULL; pe = pe->prox){
            if(pe->tipo == 1){
                Professor *pro = (Professor*)pe->item;
                if(aux < pro->salario)
                    aux = pro->salario;
            }
        }
        for(pe = p; pe != NULL; pe = pe->prox){
            if(pe->tipo == 1){
                Professor *pro = (Professor*)pe->item;
                if(pro->salario == aux)
                    printf("\nMatricula: %d\nNome: %s\nSalario: %.2f\n\n", pro->mat, pro->nome, pro->salario);
            }
        }
    }
}

void menu(){
    int op,cod, mat, num;
    char curso[50];
    Pessoa *pe;

    pe = inicializar();


    while(op!=6){
        printf("O que deseja fazer?\n1-Inserir uma pessoa na lista\n2-Remover uma pessoa pela matricula\n3-Buscar uma pessoa pela matricula"
               "\n4-Contar o numero de alunos em um determinado curso\n5-Imprimir os professores de maior salario.\n6-Sair\n\n");
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("O que deseja inserir?\n1-Professor\n2-Aluno\n");
                scanf("%d", &cod);
                if(cod != 1 && cod != 2)
                    printf("Opcao invalida.\n");
                else
                    pe = inserir(pe,cod);
                break;
            case 2:
                printf("Digite a matricula: ");
                scanf("%d", &mat);
                pe = remover(pe, mat);
                break;
            case 3:
                printf("Digite a matricula: ");
                scanf("%d", &mat);
                buscar_pessoa(pe, mat);
                break;
            case 4:
                printf("Digite o nome do curso: ");
                fflush(stdin);
                gets(curso);
                num = conta_alunos(pe,curso);
                printf("O curso %s tem %d alunos.\n\n", curso, num);
                break;
            case 5:
                imprimir_professores(pe);
                break;
            default:
                if(op!=6)
                    printf("Opcao invalida!\n");
        }
    }
}

void main(){
    menu();
}
