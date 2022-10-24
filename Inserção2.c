#include <stdio.h>
#include <stdlib.h>


typedef struct noRN{
     int chave;
     int cor; // 1 = vermelho, 0 = preto
     struct noRN *pai;
     struct noRN *esq;
     struct noRN *dir;
}noRN;


void imprimir_pre_ordem(noRN *raiz){
     if(raiz != NULL){
             printf("\n%i", raiz->chave);
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


void RB_insert_fix_up(noRN *raiz, noRN *arvore){
     //se o pai for preto n muda nada.
     while (arvore->pai->cor == 1){
          noRN *aux;
          //pai na subararvore esquerda
          if (arvore->pai == arvore->pai->pai->esq){
               aux = arvore->pai->pai->dir;
               //pai vermelho e tio vermelho só mudo cores
               if (aux->cor == 1) {
                    arvore->pai->cor = 0;
                    aux->cor = 0;
                    arvore->pai->pai->cor = 1;
                    arvore = arvore->pai->pai;
               //pai vermelho e tio preto mudo cor e faz rotações
               }else{
                    if (arvore == arvore->pai->dir){ //RL
                         arvore = arvore->pai;
                         //LL();
                    }
                    //RR();
                    arvore->pai->cor = 0;
                    arvore->pai->pai->cor = 1;
               }
          }
          //pai na subararvore direita
          else{
               aux = arvore->pai->pai->esq;
               //pai vermelho e tio vermelho só mudo cores
               if (aux->cor == 1) {
                    arvore->pai->cor = 0;
                    aux->cor = 0;
                    arvore->pai->pai->cor = 1;
                    arvore = arvore->pai->pai;
               //pai vermelho e tio preto mudo cor e faz rotações
               }else{
                    if (arvore == arvore->pai->esq){ //LR
                         arvore = arvore->pai;
                         //RR();
                    }
                    //LL();
                    arvore->pai->cor = 0;
                    arvore->pai->pai->cor = 1;
               }
          }
     }//FIM while
     raiz->cor = 0;
}

noRN *RB_insert(noRN **raiz, int num){
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
     aux->cor = 1;

     return aux;
     //RB_insert_fix_up(raiz, arvore);
}


int main() {
     noRN *raiz = NULL;// Ponteiro que aponta para a raiz da árvore
     int num;
     noRN *v = RB_insert(&raiz, 5);
     //printf("%p\n", raiz->dir);
     RB_insert(&raiz, 7);
     //printf("%p\n", raiz->dir);
     RB_insert(&raiz, 9);
     imprimir_pre_ordem(raiz);
     LL(&raiz, &v);
     imprimir_pre_ordem(raiz);

     return 0;
}
