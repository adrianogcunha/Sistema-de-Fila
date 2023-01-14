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

noRN *buscar_no(noRN *raiz, int num){
    noRN *aux = raiz;
    noRN *aux2 = NULL;
    while (aux != NULL){
        if (aux->chave == num){
            return aux;//retorna o nó buscado
        }
        aux2 = aux;
        if (aux->chave > num){ // lado direito
            aux = aux->esq;
        }else{ // lado esquerdo
            aux = aux->dir;
        }
    }
    return aux2;//retornando o nó
}

void imprimir_pre_ordem(noRN *raiz){
    if (raiz != NULL){
        printf("%d ", raiz->chave);
        if (raiz->cor == 0){
            puts("BLACK");
        }else{
            puts("RED");
        }
    
        imprimir_pre_ordem(raiz->esq);
        imprimir_pre_ordem(raiz->dir);
    }
}

void LL(noRN **raiz, noRN *no){
    noRN *aux;
  
    aux = no->dir; // lado direito
    if (aux->esq != NULL){
        aux->esq->pai = no;
    }
    no->dir = aux->esq; // ok
    aux->esq = no;
    aux->pai = no->pai;
    if (no->pai != NULL){ // não é raiz
        if (no->pai->esq == no){//nó está a esquerda
            no->pai->esq = aux;
        }else{//nó está a direita
            no->pai->dir = aux;
        }
    }
    else{ //é raiz
        aux->pai = NULL;
        (*raiz) = aux;
    }
    no->pai = aux;
}

void RR(noRN **raiz, noRN *no){
    noRN *aux;

    aux = no->esq; // lado esquerdo
    if (aux->dir != NULL){
        aux->dir->pai = no;
    }
    no->esq = aux->dir; // ok
    aux->dir = no;
    aux->pai = no->pai;
    if (no->pai != NULL){ // não é raiz
        if (no->pai->esq == no){//nó está a esquerda
            no->pai->esq = aux;
        }else{//nó está a direita
            no->pai->dir = aux;
        }
    }else{ //é raiz
        (*raiz) = aux;
        aux->pai = NULL;
    }
    no->pai = aux;
}

void Fix_up(noRN **raiz, noRN *arvore){
    // Caso 1 - Nenhuma alteraçõa, logo não muda nada (pai preto)
    while (arvore->pai != NULL && arvore->pai->cor == VERMELHO){ //Verifica se entra no caso 1 ou se o nó criado é raiz
        noRN *aux_tio;
        // pai na subararvore esquerda
        if (arvore->pai == arvore->pai->pai->esq){
            aux_tio = arvore->pai->pai->dir;
            // caso 2 - pai vermelho e tio vermelho só mudo cores
            if (aux_tio != NULL && aux_tio->cor == VERMELHO){
                arvore->pai->cor = PRETO;
                aux_tio->cor = PRETO;
                arvore->pai->pai->cor = VERMELHO;
                arvore = arvore->pai->pai; //Árvore muda para o avó
            }else{// caso 3 - pai vermelho e tio preto mudo cor e faz rotações
                if (arvore == arvore->pai->dir){ // LL
                    arvore = arvore->pai;
                    LL(raiz, arvore);
                }
                arvore->pai->cor = PRETO;
                if (arvore->pai->pai != NULL){ //(evitar segfault)  RR
                    arvore->pai->pai->cor = VERMELHO;
                    RR(raiz, arvore->pai->pai);
                }
                
            }
        }else{  // pai na subararvore direita
            aux_tio = arvore->pai->pai->esq;
            // caso 2 - pai vermelho e tio vermelho só mudo cores
            if (aux_tio != NULL && aux_tio->cor == VERMELHO){
                arvore->pai->cor = PRETO;
                aux_tio->cor = PRETO;
                arvore->pai->pai->cor = VERMELHO;
                arvore = arvore->pai->pai; 
                
            }else{ // caso 3 - pai vermelho e tio preto mudo cor e faz rotações
                if (arvore == arvore->pai->esq){ // Rl
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
    noRN *aux; //nó pai 
    noRN *aux_pai = (*raiz); //nó que vai ser removido
    while (aux_pai->esq != NULL) {
        aux_pai = aux_pai->esq; //busca menor
    }

    if (aux_pai == (*raiz)) { //caso raiz - nó removido é a raiz

        NoAremover = aux_pai;
        if(aux_pai->dir != NULL){ //tem filho na direita
            (*raiz) = aux_pai->dir;
            aux_pai->dir->pai = NULL;
            (*raiz)->cor = PRETO;
        }else{ //nn tem filho na direita
            (*raiz) = NULL;
        }
        //raiz = NULL;
        free(NoAremover);
    }else if(aux_pai->cor == VERMELHO){ // caso 1 - nó removido vermelho. Pode ter no máximo filho da direita, basta copiar o filho pro lugar dele.
        NoAremover = aux_pai;
        if(aux_pai->dir != NULL){ //tem filho na direita

            aux_pai->pai->esq = aux_pai->dir;
            aux_pai->dir->pai = aux_pai->pai;    
        }else{ //nn tem filho na direita
            aux_pai->pai->esq = NULL;
        }
        free(NoAremover);
    }else if(aux_pai->cor == PRETO && aux_pai->dir != NULL){ //caso 2 - nó removido preto com apenas um filho (da direita)

        NoAremover = aux_pai;
        aux_pai->dir->cor = PRETO;
        aux_pai->pai->esq = aux_pai->dir;
        aux_pai->dir->pai = aux_pai->pai;
        free(NoAremover);
    }else{ // caso 3 - nó removido preto e sem filho. Problema de duplo preto. Subcasos:
        NoAremover = aux_pai;
        aux = aux_pai->pai;
        while(aux_pai != (*raiz)){
            irmao = aux_pai->pai->dir;

            if(irmao->cor == VERMELHO){ //caso 3.1
                irmao->cor = PRETO;
                irmao->pai->cor = VERMELHO;
                LL(raiz, irmao->pai);
            }else if(irmao->cor == PRETO && ((irmao->dir == NULL && irmao->esq == NULL) || (irmao->dir->cor == PRETO && irmao->esq->cor == PRETO))){ //caso 3.2
                if(irmao->pai->cor == VERMELHO){
                    irmao->cor = VERMELHO;
                    irmao->pai->cor = PRETO;
                    break;
                }
                irmao->cor = VERMELHO;
                irmao->pai->cor = PRETO;
                aux_pai = aux_pai->pai;
            }else if(irmao->cor == PRETO && ((irmao->esq != NULL && irmao->esq->cor == VERMELHO) && (irmao->dir == NULL || irmao->dir->cor == PRETO))){ //caso 3.3
                // filho da direita dp irmao pode ser preto
                irmao->cor = VERMELHO;
                irmao->esq->cor = PRETO;
                RR(raiz, irmao); 
            }else{ //caso 3.4 (caso final)
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
// caso 3.1 - irmão vermelho -> Pinta o irmão de preto e pinta pai de vermelho. LL(Pai). Volta no while
// caso 3.2 - irmão preto sem filho / filhos pretos -> Pinta irmão de vermelho, pinta pai de preto, caso pai seja vermelho, break; no = no->pai. Volta no while.
// caso 3.3 - irmão preto com apenas filho da esq (vermelho) -> pinta irmão de vermelho e pinta filho da esq do irmão de preto. RR(irmão). Cai no 3.4
// caso 3.4 - irmão preto com filho da direita vermelho (independente de ter outro filho) -> Irmão copia cor antiga do pai, pinta pai de preto, pega filho direito do irmào e pinta de preto. LL(Pai). Acabou.


void RB_insert(noRN **raiz, int num){
    noRN *aux; //Novo nó
    noRN *aux_pai = NULL; //Nó pai do novo nó
    
    aux_pai = buscar_no((*raiz), num);

    aux = (noRN *)malloc(sizeof(noRN)); // alocar memoria
   
    aux->pai = aux_pai;

    if (aux_pai == NULL){ // verificando se a arvore e vazia
        (*raiz) = aux;
    }else if (num > aux_pai->chave){
        aux_pai->dir = aux;
    }else{
        aux_pai->esq = aux;
    }

    aux->chave = num;
    aux->esq = NULL;
    aux->dir = NULL;
    aux->cor = VERMELHO; 

    Fix_up(raiz, aux);
}

int main(){
    noRN *raiz = NULL; // Ponteiro que aponta para a raiz da árvore
    int num;
 
    while(scanf("%d", &num) != EOF){
        if(num == -1){
            remocao(&raiz); //remover o nó de menor valor
        }else{
            RB_insert(&raiz, num);
        }
    }
    imprimir_pre_ordem(raiz);
/*
    RB_insert(&raiz, 30);
    RB_insert(&raiz, 29);
    RB_insert(&raiz, 40);
    RB_insert(&raiz, 70);
    RB_insert(&raiz, 80);
    imprimir_pre_ordem(raiz);

    //BUSCA
    int num_busca;
    noRN *end_buscado;
    printf("\n");
    puts("Digite o numero que você deseja buscar na árvore:");
    scanf("%d", &num_busca);
    end_buscado = buscar_no(raiz, num_busca);

    if(end_buscado->chave == num_busca){
        printf("Chave: %d encontrada!\n", num_busca);
    }else{
        printf("Chave: %d NÃO encontrada!\n", num_busca);
    }
*/
    return 0;
}
