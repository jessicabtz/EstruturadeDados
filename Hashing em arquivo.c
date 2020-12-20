#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 97

///Diego Maia
///Guilherme Silva
///Jéssica Beatriz
///Thyago Azeredo

typedef struct aluno{
    int matricula;
    char nome[100];
    char curso[50];
    int disponibilidade;
}aluno;

void inicializa(char *nome_arq){
    FILE *arq = fopen(nome_arq, "wb");
    aluno a;
    int i;

    if(!arq)
        printf("Erro ao abrir arquivo para escrita");

    a.disponibilidade = 1;
    for(i = 0; i < N; i++){
        fwrite(&a, sizeof(aluno), 1, arq);
    }

    fclose(arq);
}

int hash(int key){
    return key % N;
}

int hash2(int key){
    return N - 2 - (key % (N - 2));
}

int acha_posicao(char *nome_arq, int x){
    FILE *arq;
    aluno a;
    int pos, desl;

    pos = hash(x);
    desl = hash2(x);
    arq = fopen(nome_arq, "rb");
    fseek(arq, pos*sizeof(aluno), SEEK_SET);
    fread(&a, sizeof(aluno), 1, arq);

    while(a.disponibilidade == 0){
        pos = (pos+desl) % N;
        fseek(arq, pos*sizeof(aluno), SEEK_SET);
        fread(&a, sizeof(aluno), 1, arq);
    }

    fclose(arq);
    return pos;
}

void insere_aluno(char *nome_arq, int x){
    FILE *arq;
    aluno a;
    int pos;
    char nome[100], curso[50];

    fflush(stdin);
    printf("Digite o nome do aluno\n");
    scanf("%[^\n]s", nome);
    fflush(stdin);
    printf("Digite o curso do aluno\n");
    scanf("%[^\n]s", curso);
    fflush(stdin);

    pos = acha_posicao(nome_arq, x);
    arq = fopen(nome_arq, "r+b");
    a.matricula = x;
    a.disponibilidade = 0;
    strcpy(a.nome, nome);
    strcpy(a.curso, curso);

    fseek(arq, pos*sizeof(aluno), SEEK_SET);
    fwrite(&a, sizeof(aluno), 1, arq);

    fclose(arq);
}

int busca_aluno(char *nome_arq, int x, int *ret){
    FILE *arq;
    aluno a;
    int pos, desl;

    pos = hash(x);
    desl = hash2(x);
    arq = fopen(nome_arq, "rb");
    fseek(arq, pos*sizeof(aluno), SEEK_SET);
    fread(&a, sizeof(aluno), 1, arq);

    while(a.matricula!= x && a.disponibilidade != 1){
        pos = (pos+desl) % N;
        fseek(arq, pos*sizeof(aluno), SEEK_SET);
        fread(&a, sizeof(aluno), 1, arq);
    }

    if(a.disponibilidade == 1)
        return 0;
    else{
        *ret = pos;
        return 1;
    }

    fclose(arq);
}

void imprime_aluno(char *nome_arq, int x){
    FILE* arq;
    aluno a;
    int r, pos;

    arq = fopen(nome_arq, "rb");
    r = busca_aluno(nome_arq, x, &pos);
    if(r == 0)
        printf("O aluno nao esta cadastrado\n");
    else{
        fseek(arq, pos*sizeof(aluno), SEEK_SET);
        fread(&a, sizeof(aluno), 1, arq);
        printf("Matricula: %d\nNome:%s\nCurso:%s\n\n", a.matricula, a.nome, a.curso);
    }

}

void imprime_dispersao(char *nome_arq){
    FILE *arq;
    aluno a;
    int i;

    arq = fopen(nome_arq, "rb");
    for(i=0; i<N; i++){
        fread(&a, sizeof(aluno), 1, arq);
        if(a.disponibilidade == 1)
            printf("%d :Disponivel\n\n", i);
        else
            printf("Matricula: %d\nNome:%s\nCurso:%s\n\n", a.matricula, a.nome, a.curso);
    }

    fclose(arq);
}

void menu(){
    int op,mat;
    char nome_arq[50];

    strcpy(nome_arq, "turmaA.bin");
    inicializa(nome_arq);

    do{
        printf("O que deseja fazer?\n1-Inserir um novo aluno\n2-Imprimir as informacoees de um determinado aluno\n3-Imprimir a tabela de dispersao\n4-Sair\n");
        scanf("%d", &op);

        switch(op){
            case 1:
                printf("Digite a matricula do aluno aqui\n");
                scanf("%d", &mat);
                insere_aluno(nome_arq, mat);
                break;
            case 2:
                printf("Digite a matricula do aluno\n");
                scanf("%d", &mat);
                imprime_aluno(nome_arq,mat);
                break;
            case 3:
                imprime_dispersao(nome_arq);
                break;
            default:
                if(op!=4)
                    printf("Opcao invalida!\n\n");
        }
    }while(op != 4);
}

void main(){
    menu();
}
