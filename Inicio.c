#include <stdio.h>
#include <stdlib.h>
#include <stdin.h>

typedef struct noRN{
     int chave;
     int cor;
     noRN *pai;
     noRN *esq;
     noRN *dir;
}noRN;

//Busca o menor elemento da árvore para ser removido
int busca_menor(noRN *arvore) {
    noRN* aux = arvore;
    while (arvore->esq != NULL) {
        aux = arvore->esq;
    }
    return(arvore->chave);
}

void remover(noRN *arvore, int chave){

}

void inserir(noRN *arvore, int chave){

}

void imprimir_pre_ordem(noRN *raiz){
     if(raiz != NULL){
             printf("\n%i", raiz->chave);
             exibirPreOrdem(raiz->esq);
             exibirPreOrdem(raiz->dir);
         }
     }
}

int main(){
     noRN *arvore = (noRN *)malloc(sizeof(noRN));
     int num;
     while( != EOF){
          scanf("%d", &num);
          if(num == -1){
               int menor = busca_menor(arvore); //buscar o menor valor da árvore
               remover(arvore, menor); //remover o nó de menor valor
          }else{
               inserir(arvore, num);
          }
     }
     //printar em pre-ordem
     return 0;
}
