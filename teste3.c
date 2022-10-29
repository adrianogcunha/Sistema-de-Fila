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
            printf(" PRETO\n");
        }else{
            printf(" VERMELHO\n");
        }
        if(raiz->esq != NULL){
            printf("ESQ = %d   ",raiz->esq->chave);
        }
        if(raiz->dir != NULL){
            printf("DIR = %d\n", raiz->dir->chave);
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
    puts("Saiu LL");
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
    puts("Saiu LL");
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

void remocao(noRN **raiz) {
    noRN *NoAremover;
    noRN *irmao;
    noRN *aux;
    noRN *aux_pai = (*raiz);
    while (aux_pai->esq != NULL) {
        puts("teste 1");
        //aux_pai = aux;
        aux_pai = aux_pai->esq; //busca menor
    }

    printf("Removendo: %d\n", aux_pai->chave);
    //printf("%d", aux->chave);
    if (aux_pai == (*raiz)) { //caso raiz - nó removido é a raiz
        puts("Caso 0");
        NoAremover = aux_pai;
        if(aux_pai->dir != NULL){ //tem filho na direita
            puts("Caso 0.1");
            //printf("%d\n", aux_pai->dir->chave);
            //printf("%d\n", (*raiz)->chave);
            (*raiz) = aux_pai->dir;
            aux_pai->dir->pai = NULL;
            (*raiz)->cor = PRETO;
            //printf("%d\n", (*raiz)->chave);
        }else{ //nn tem filho na direita
            puts("Caso 0.2");
            (*raiz) = NULL;
        }
        //raiz = NULL;
        free(NoAremover);
    }else if(aux_pai->cor == VERMELHO){ // caso 1 - nó removido vermelho. Pode ter no máximo filho da direita, basta copiar o filho pro lugar dele.
        NoAremover = aux_pai;
        if(aux_pai->dir != NULL){ //tem filho na direita
            puts("Caso 1.1");
            aux_pai->pai->esq = aux_pai->dir;
            aux_pai->dir->pai = aux_pai->pai;    
        }else{ //nn tem filho na direita
            puts("Caso 1.2");
            aux_pai->pai->esq = NULL;
        }
        free(NoAremover);
    }else if(aux_pai->cor == PRETO && aux_pai->dir != NULL){ //caso 2 - nó removido preto com apenas um filho (da direita)
        puts("Caso 2");
        NoAremover = aux_pai;
        aux_pai->dir->cor = PRETO;
        aux_pai->pai->esq = aux_pai->dir;
        aux_pai->dir->pai = aux_pai->pai;
        free(NoAremover);
    }else{ // caso 3 - nó removido preto e sem filho. Problema de duplo preto. Subcasos:
        NoAremover = aux_pai;
        aux = aux_pai->pai;
        while(aux_pai != (*raiz)){
            puts("Caso 3");
            irmao = aux_pai->pai->dir;

            printf("%d\n", irmao->cor);
            printf("%p\n", irmao->esq);

            if(irmao->cor == VERMELHO){
                puts("Caso 3.1");
                irmao->cor = PRETO;
                irmao->pai->cor = VERMELHO;
                LL(raiz, irmao->pai);
            }else if(irmao->cor == PRETO && (irmao->dir == NULL && irmao->esq == NULL) || (irmao->dir->cor == PRETO && irmao->esq->cor == PRETO)){
                puts("Caso 3.2");
                if(irmao->pai->cor == VERMELHO){
                    irmao->cor = VERMELHO;
                    irmao->pai->cor = PRETO;
                    break;
                }
                irmao->cor = VERMELHO;
                irmao->pai->cor = PRETO;
                aux_pai = aux_pai->pai;
            }else if(irmao->cor == PRETO && (irmao->esq != NULL && irmao->esq->cor == VERMELHO) && irmao->dir == NULL){
                puts("Caso 3.3");
                irmao->cor = VERMELHO;
                irmao->esq->cor = PRETO;
                RR(raiz, irmao); 
            }else{
                puts("Caso 3.4");
                irmao->cor = irmao->pai->cor;
                irmao->pai->cor = PRETO;
                irmao->dir->cor = PRETO;
                LL(raiz, irmao->pai);
                break;
            }
        }
        aux->esq = NULL;
        free(NoAremover);
    }
}

void RB_insert(noRN **raiz, int num){
    noRN *aux = (*raiz);
    noRN *aux2 = NULL;
    while (aux != NULL){
        aux2 = aux;
        if (aux->chave > num){ // lado direito
            aux = aux->esq;
        }else{ // lado esquerdo
            aux = aux->dir;
        }
    }
    aux = (noRN *)malloc(sizeof(noRN)); // alocar memoria
    // printf("%p\n", aux);

    aux->pai = aux2;

    if (aux2 == NULL){ // verificando se a arvore e vazia
        (*raiz) = aux;
    }else if (aux2->chave < num){
        aux2->dir = aux;
    }else{
        aux2->esq = aux;
    }

    aux->chave = num;
    aux->esq = NULL;
    aux->dir = NULL;
    aux->cor = VERMELHO; // vermelho

    Fix_up(raiz, aux);
}

int main(){
    noRN *raiz = NULL; // Ponteiro que aponta para a raiz da árvore
    int num;
    RB_insert(&raiz, 30);
    remocao(&raiz);
    RB_insert(&raiz, 41);
    RB_insert(&raiz, 17);
    RB_insert(&raiz, 34);
    RB_insert(&raiz, 43);
    remocao(&raiz);
    RB_insert(&raiz, 24);
    RB_insert(&raiz, 25);
    RB_insert(&raiz, 49);
    RB_insert(&raiz, 32);
    RB_insert(&raiz, 36);
    remocao(&raiz);
    remocao(&raiz);
    remocao(&raiz);
    remocao(&raiz);
    remocao(&raiz);
    imprimir_pre_ordem(raiz);
    printf("\n");
    return 0;
}
