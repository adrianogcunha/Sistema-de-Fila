#include <stdio.h>
#include <stdlib.h>
#include <stdin.h>\

typedef struct noRN{
     int chave;
     int cor;
     noRN *pai;
     noRN *esq;
     noRN *dir;
}noRN;

int busca_menor(noRN *arvore) {
    noRN* aux = arvore;
    while (avore->esq != NULL) {
        aux = arvore->esq;
    }
    return(current->chave);
}
//Inserir
//Remover
//Printar

int main(){
     noRN *arvore = (noRN *)malloc(sizeof(noRN));
     int num;
     while( != EOF){
          scanf("%d", &num);
          if(num == -1){
               int menor = busca_menor(); //buscar o menor valor da árvore
               remover(menor);
               //remover o de menor valor, logo deve fazer uma busca
          }else{
               //inserir
          }
     }
     //printar em pre-ordem
     return 0;
}
