void remocao(noRN **raiz) {
    noRN *NoAremover;
    noRN *irmao;
    noRN *aux = (*raiz);
    noRN *aux_pai = NULL;
    while (arvore->esq != NULL) {
        aux_pai = aux;
        aux = arvore->esq; //busca menor
    }

    if (aux_pai == (*raiz)) { //caso raiz - nó removido é a raiz
        NoAremover = aux_pai;
        (*raiz) = NULL;
        free(NoAremover);
    }else if(aux_pai->cor == VERMELHO){ // caso 1 - nó removido vermelho. Pode ter no máximo filho da direita, basta copiar o filho pro lugar dele.
        if(aux_pai->dir != NULL){ //tem filho na direita
            NoAremover = aux_pai;
            aux_pai->pai->esq = aux_pai->dir;
            aux_pai->dir->pai = aux_pai->pai;
            free(NoAremover);
        }else{ //nn tem filho na direita
            NoAremover = aux_pai;
            aux_pai->pai->esq = NULL;
            free(NoAremover);
        }
    }else if(aux_pai->cor == PRETO && aux_pai->dir != NULL){ //caso 2 - nó removido preto com apenas um filho (da direita)
        NoAremover = aux_pai;
        aux_pai->dir->cor = PRETO;
        aux_pai->pai->esq = aux_pai->dir;
        aux_pai->dir->pai = aux_pai->pai;
        free(NoAremover);
    }else{ // caso 3 - nó removido preto e sem filho. Problema de duplo preto. Subcasos:
        NoAremover = aux_pai;
        irmao = aux_pai->pai->dir;
        while(){
            if(irmao == VERMELHO){
                irmao->cor = PRETO;
                irmao->pai->cor = VERMELHO;
                LL(irmao->pai);
            }else if(irmao == PRETO && ((irmao->dir == NULL && irmao->esq == NULL) || (irmao->dir->cor == PRETO && irmao->esq->cor == PRETO))){
                if(irmao->pai == VERMELHO){
                    irmao->cor = VERMELHO;
                    irmao->pai->cor = PRETO;
                    break;
                }
                irmao->cor = VERMELHO;
                irmao->pai->cor = PRETO;
                aux_pai = aux->pai;
            }else if(irmao == PRETO && (irmao->esq != NULL && irmao->esq->cor == VERMELHO) && irmao->dir == NULL){
                irmao->cor = VERMELHO;
                irmao->esq->cor = PRETO;
                RR(irmao); 
            }else if(irmao == PRETO && (irmao->dir != NULL && irmao->esq->cor == VERMELHO)){
                irmao->cor = irmao->pai->cor;
                irmao->pai->cor = PRETO;
                irmao->dir->cor = PRETO;
                LL(irmao->pai);
                break;
            }

        }
        free(NoAremover);
    }
    

   
    

// caso 3.1 - irmão vermelho -> Pinta o irmão de preto e pinta pai de vermelho. LL(Pai). Verifica caso.
// caso 3.2 - irmão preto sem filho / filhos pretos -> Pinta irmão de vermelho, pinta pai de preto, caso pai seja vermelho break(pinta antes); no = no->pai. Verifica caso.
// caso 3.3 - irmão preto com apenas filho da esq (vermelho) -> pinta irmão de vermelho e pinta filho da esq do irmão de preto. RR(irmão). Cai no 3.4
// caso 3.4 - irmão preto com filho da direita vermelho (independente de ter outro filho) -> Irmão copia cor antiga do pai, pinta pai de preto, pega filho direito do irmào e pinta de preto. LL(Pai). Acabou.
}