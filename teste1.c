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

void imprimir_pre_ordem(noRN *raiz)
{
    if (raiz != NULL)
    {
        printf("\n%d ", raiz->chave);
        if (raiz->cor == 0)
        {
            printf(" PRETO");
        }
        else
        {
            printf(" VERMELHO");
        }

        imprimir_pre_ordem(raiz->esq);
        imprimir_pre_ordem(raiz->dir);
    }
}

void LL(noRN *no){
    puts("Entrou LL");
    noRN *aux;
    aux = no->dir;
    if (aux->esq != NULL){
        aux->esq->pai = no;
    }
    no->dir = aux->esq;
    aux->esq = no;
    aux->pai = no->pai;
    if (no->pai != NULL){
        if (no->pai->esq == no){
            no->pai->esq = aux;
        }else{
            no->pai->dir = aux;
        }
    }
    no->pai = aux;
}

void RR(noRN *no){
    puts("Entrou RR");
    noRN *aux;
    aux = no->esq;
    if (aux->dir != NULL){
        aux->dir->pai = no;
    }
    no->esq = aux->dir;
    aux->dir = no;
    aux->pai = no->pai;
    if (no->pai != NULL){
        if (no->pai->esq == no){
            no->pai->esq = aux;
        }else{
            no->pai->dir = aux;
        }
    }
    no->pai = aux;
}

void TESTE_fix_up(noRN **raiz, noRN *arvore)
{
    // Caso 1 - Nenhuma alteraçõa, logo não muda nada
    while (arvore->pai != NULL && arvore->pai->cor == VERMELHO)
    {
        noRN *aux_tio;
        // pai na subararvore esquerda
        if (arvore->pai == arvore->pai->pai->esq)
        {
            aux_tio = arvore->pai->pai->dir;
            // caso 2 - pai vermelho e tio vermelho só mudo cores
            if (aux_tio != NULL && aux_tio->cor == VERMELHO)
            {
                arvore->pai->cor = PRETO;
                aux_tio->cor = PRETO;
                arvore->pai->pai->cor = VERMELHO;
                arvore = arvore->pai->pai;
                puts("Caso2");
            }
            // caso 3 - pai vermelho e tio preto mudo cor e faz rotações
            else
            {
                if (arvore == arvore->pai->dir)
                { // RL
                    arvore = arvore->pai;
                    LL(arvore);
                }
                arvore->pai->cor = PRETO;
                if (arvore->pai->pai != NULL)
                {
                    arvore->pai->pai->cor = VERMELHO;
                    RR(arvore->pai->pai);
                }
                puts("Caso3-L");
            }
            // pai na subararvore direita
        }
        else
        {
            aux_tio = arvore->pai->pai->esq;
            // caso 2 - pai vermelho e tio vermelho só mudo cores
            if (aux_tio != NULL && aux_tio->cor == VERMELHO)
            {
                arvore->pai->cor = PRETO;
                aux_tio->cor = PRETO;
                arvore->pai->pai->cor = VERMELHO;
                arvore = arvore->pai->pai;
                puts("Caso2-D");
            }
            // caso 3 - pai vermelho e tio preto mudo cor e faz rotações
            else
            {
                if (arvore == arvore->pai->esq)
                { // LR
                    arvore = arvore->pai;
                    RR(arvore);
                }
                arvore->pai->cor = PRETO;
                if (arvore->pai->pai != NULL)
                {
                    arvore->pai->pai->cor = VERMELHO;
                    LL(arvore->pai->pai);
                }
                puts("Caso3-D");
            }
        }
    }

    if (arvore->pai == NULL)
        (*raiz) = arvore;
    else if (arvore->pai->pai == NULL)
        (*raiz) = arvore->pai;

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

    TESTE_fix_up(raiz, aux);
}

int main()
{
    noRN *raiz = NULL; // Ponteiro que aponta para a raiz da árvore
    int num;
    RB_insert(&raiz, 9);
    // printf("%p\n", raiz->dir);
    RB_insert(&raiz, 8);
    // printf("%p\n", raiz->dir);
    RB_insert(&raiz, 7);
    RB_insert(&raiz, 6);
    RB_insert(&raiz, 1);
    //RB_insert(&raiz, 2);
    //RB_insert(&raiz, 3);
    imprimir_pre_ordem(raiz);
    printf("\n");
    // LL(&raiz, &v);
    // imprimir_pre_ordem(raiz);

    return 0;
}

