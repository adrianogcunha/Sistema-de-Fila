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
}noRN;


void imprimir_pre_ordem(noRN *raiz){
     if(raiz != NULL){
          printf("\n%d ", raiz->chave);
          if (raiz->cor == 0){
               printf(" PRETO");
          }else{
               printf(" VERMELHO\n");
          }
             
          imprimir_pre_ordem(raiz->esq);
          imprimir_pre_ordem(raiz->dir);
     }
}


void LL(noRN **raiz, noRN **no){
     noRN *aux;
     aux = (*no)->dir; // lado direito
     if (aux->esq != NULL) {
          aux->esq->pai = (*no);
     }
     (*no)->dir = aux->esq; //ok
     aux->esq = (*no);
     aux->pai = (*no)->pai;
     if ((*no)->pai != NULL) { //não é raiz
          aux->pai = (*no)->pai;
     }else{//é raiz
          (*raiz) = aux;
          aux->pai = NULL;
     }
     (*no)->pai = aux;
     //(*no) = aux;
}

void RR(noRN **raiz, noRN **no){
     noRN *aux;
     aux = (*no)->esq; // lado direito
     if (aux->dir != NULL) {
          aux->dir->pai = (*no);
     }
     (*no)->esq = aux->dir; //ok
     aux->dir = (*no);
     if ((*no)->pai != NULL) { //não é raiz
          aux->pai = (*no)->pai;
     }else{//é raiz
          (*raiz) = aux;
          aux->pai = NULL;
     }
     (*no)->pai = aux;
     //(*no) = aux;
}



void TESTE_fix_up(noRN **raiz, noRN *arvore){
     //Caso 1 - Nenhuma alteraçõa, logo não muda nada
     while (arvore->pai != NULL && arvore->pai->cor == VERMELHO){
          noRN *aux_tio;
          // pai na subararvore esquerda
          if (arvore->pai == arvore->pai->pai->esq){
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
                    if (arvore == arvore->pai->dir){ // RL
                         arvore = arvore->pai;
                         //LL(raiz, &arvore);
                    }
                    arvore->pai->cor = PRETO;
                    if(arvore->pai->pai != NULL){
                         arvore->pai->pai->cor = VERMELHO;
                         //RR(raiz, &arvore->pai->pai);
                    }
                    puts("Caso3");
               }
          // pai na subararvore direita
          }else{
               aux_tio = arvore->pai->pai->esq;
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
                    if (arvore == arvore->pai->esq){ // LR
                         arvore = arvore->pai;
                         RR(raiz, &arvore);
                    }
                    arvore->pai->cor = PRETO;
                    if(arvore->pai->pai != NULL){
                         arvore->pai->pai->cor = VERMELHO;
                         LL(raiz, &arvore->pai->pai);
                    
                    }
                    puts("Caso3");
               }
          }
     }
     /*
     if(arvore->pai == NULL)
          (*raiz) = arvore;
     else if(arvore->pai->pai == NULL)
          (*raiz) = arvore->pai;
     */

     (*raiz)->cor = PRETO;
}


void RB_insert_fix_up(noRN *raiz, noRN *arvore){
     //se o pai for preto n muda nada.
     while (arvore->pai->cor == VERMELHO){
          noRN *aux;
          //pai na subararvore esquerda
          if (arvore->pai == arvore->pai->pai->esq){
               aux = arvore->pai->pai->dir;
               //caso 2 - pai vermelho e tio vermelho só mudo cores
               if (aux->cor == VERMELHO) {
                    arvore->pai->cor = PRETO;
                    aux->cor = PRETO;
                    arvore->pai->pai->cor = VERMELHO;
                    arvore = arvore->pai->pai;
               //caso 3 - pai vermelho e tio preto mudo cor e faz rotações
               }else{
                    if (arvore == arvore->pai->dir){ //RL
                         arvore = arvore->pai;
                         //LL();
                    }
                    //RR();
                    arvore->pai->cor = PRETO;
                    arvore->pai->pai->cor = VERMELHO;
               }
          }
          //pai na subararvore direita
          else{
               aux = arvore->pai->pai->esq;
               // caso 2 - pai vermelho e tio vermelho só mudo cores
               if (aux->cor == VERMELHO) {
                    arvore->pai->cor = PRETO;
                    aux->cor = PRETO;
                    arvore->pai->pai->cor = VERMELHO;
                    arvore = arvore->pai->pai;
               // caso 3 - pai vermelho e tio preto mudo cor e faz rotações
               }else{
                    if (arvore == arvore->pai->esq){ //LR
                         arvore = arvore->pai;
                         //RR();
                    }
                    //LL();
                    arvore->pai->cor = PRETO;
                    arvore->pai->pai->cor = VERMELHO;
               }
          }
     }//FIM while
     raiz->cor = PRETO;
}

void RB_insert(noRN **raiz, int num){
     noRN *aux = (*raiz);
     noRN *aux2 = NULL;
     while (aux != NULL) {
          aux2 = aux;
          if (aux->chave > num){ //lado direito
               aux = aux->esq;
          }else{ //lado esquerdo
               aux = aux->dir;
          }
     }
     aux = (noRN *)malloc(sizeof(noRN)); //alocar memoria
     //printf("%p\n", aux);

     aux->pai = aux2;

     if (aux2 == NULL){ //verificando se a arvore e vazia
          (*raiz) = aux;
     }else if (aux2->chave < num){
          aux2->dir = aux;
     }else{
          aux2->esq = aux;
     }

     aux->chave = num;
     aux->esq = NULL;
     aux->dir = NULL;
     aux->cor = VERMELHO; //vermelho

     //RB_insert_fix_up(raiz, &aux);

     TESTE_fix_up(raiz, aux);
}


int main() {
     noRN *raiz = NULL;// Ponteiro que aponta para a raiz da árvore
     int num;
     RB_insert(&raiz, 5);
     //printf("%p\n", raiz->dir);
     RB_insert(&raiz, 7);
     //printf("%p\n", raiz->dir);
     RB_insert(&raiz, 9);
     imprimir_pre_ordem(raiz);
     //LL(&raiz, &v);
     //imprimir_pre_ordem(raiz);

     return 0;
}
