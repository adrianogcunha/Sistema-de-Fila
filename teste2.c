#include <stdio.h>
#include <stdlib.h>

#define PRETO 0
#define VERMELHO 1

typedef struct noRN{
    int chave;
    int cor; // 1 = vermelho, 0 = preto
    struct noRN *pai;
    struct noRN *esq;
    struct noRN *dir;
} noRN;

void imprimir_pre_ordem(noRN *raiz){
    if (raiz != NULL){
        printf("\n%d ", raiz->chave);
        if (raiz->cor == 0){
            printf(" PRETO");
        }else{
            printf(" VERMELHO");
        }
        imprimir_pre_ordem(raiz->esq);
        imprimir_pre_ordem(raiz->dir);
    }
}

void LL(noRN **raiz, noRN *no){
    puts("Entrou LL");
    //printf("%d\n", no->chave);
    noRN *aux;
  
    aux = no->dir; // lado direito
    if (aux->esq != NULL){
        aux->esq->pai = no;
    }
    no->dir = aux->esq; // ok
    aux->esq = no;
    aux->pai = no->pai;
    if (no->pai != NULL){ // não é raiz
        if (no->pai->esq == no){
            no->pai->esq = aux;
        }else{
            no->pai->dir = aux;
        }
    }
    else{ //é raiz
        aux->pai = NULL;
        (*raiz) = aux;
    }
    //printf("%p\n", aux->pai);
    //printf("%p\n", no);
    //printf("%p\n", aux);
    no->pai = aux;
    //printf("%p\n", no->pai);
    // printf("%p\n", (*raiz));
}

void RR(noRN **raiz, noRN *no){
    puts("Entrou RR");
    //printf("%d\n", no->chave);

    noRN *aux;
    aux = no->esq; // lado direito
    if (aux->dir != NULL){
        aux->dir->pai = no;
    }
    no->esq = aux->dir; // ok
    aux->dir = no;
    aux->pai = no->pai;
    if (no->pai != NULL){ // não é raiz
        if (no->pai->esq == no){
            no->pai->esq = aux;
        }else{
            no->pai->dir = aux;
        }
    }else{ //é raiz
        (*raiz) = aux;
        aux->pai = NULL;
    }
    no->pai = aux;
}

void Fix_up(noRN **raiz, noRN *arvore){
    // Caso 1 - Nenhuma alteraçõa, logo não muda nada
    while (arvore->pai != NULL && arvore->pai->cor == VERMELHO){
        noRN *aux_tio;
        // pai na subararvore esquerda
        if (arvore->pai == arvore->pai->pai->esq){
            aux_tio = arvore->pai->pai->dir;
            // caso 2 - pai vermelho e tio vermelho só mudo cores
            if (aux_tio != NULL && aux_tio->cor == VERMELHO){
                puts("Caso2-L");

                arvore->pai->cor = PRETO;
                aux_tio->cor = PRETO;
                arvore->pai->pai->cor = VERMELHO;
                arvore = arvore->pai->pai;
            }else{// caso 3 - pai vermelho e tio preto mudo cor e faz rotações
                puts("Caso3-L");

                if (arvore == arvore->pai->dir){ // RL
                    arvore = arvore->pai;
                    LL(raiz, arvore);
                }
                arvore->pai->cor = PRETO;
                if (arvore->pai->pai != NULL){
                    arvore->pai->pai->cor = VERMELHO;
                    RR(raiz, arvore->pai->pai);
                }
                
            }
        }else{  // pai na subararvore direita
            aux_tio = arvore->pai->pai->esq;
            // caso 2 - pai vermelho e tio vermelho só mudo cores
            if (aux_tio != NULL && aux_tio->cor == VERMELHO){
                puts("Caso2-D");
                arvore->pai->cor = PRETO;
                aux_tio->cor = PRETO;
                arvore->pai->pai->cor = VERMELHO;
                arvore = arvore->pai->pai;
                
            }else{ // caso 3 - pai vermelho e tio preto mudo cor e faz rotações
                puts("Caso3-D");
                if (arvore == arvore->pai->esq){ // LR
                    arvore = arvore->pai;
                    RR(raiz, arvore);
                }
                arvore->pai->cor = PRETO;
                if (arvore->pai->pai != NULL){
                    arvore->pai->pai->cor = VERMELHO;
                    LL(raiz, arvore->pai->pai);
                }
            }
        }
    }
    (*raiz)->cor = PRETO;
}


void RB_insert(noRN **raiz, int num)
{
    noRN *aux = (*raiz);
    noRN *aux2 = NULL;
    while (aux != NULL)
    {
        aux2 = aux;
        if (aux->chave > num)
        { // lado direito
            aux = aux->esq;
        }
        else
        { // lado esquerdo
            aux = aux->dir;
        }
    }
    aux = (noRN *)malloc(sizeof(noRN)); // alocar memoria
    // printf("%p\n", aux);

    aux->pai = aux2;

    if (aux2 == NULL)
    { // verificando se a arvore e vazia
        (*raiz) = aux;
    }
    else if (aux2->chave < num)
    {
        aux2->dir = aux;
    }
    else
    {
        aux2->esq = aux;
    }

    aux->chave = num;
    aux->esq = NULL;
    aux->dir = NULL;
    aux->cor = VERMELHO; // vermelho

    // RB_insert_fix_up(raiz, &aux);

    Fix_up(raiz, aux);
}

int main(){
    noRN *raiz = NULL; // Ponteiro que aponta para a raiz da árvore
    int num;
    RB_insert(&raiz, 9);
    
    RB_insert(&raiz, 8);
    
    RB_insert(&raiz, 7);
    RB_insert(&raiz, 6);
    RB_insert(&raiz, 1);
    RB_insert(&raiz, 2);
    imprimir_pre_ordem(raiz);
    printf("\n");
    return 0;
}
