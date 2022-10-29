#include<stdio.h>
#include<stdlib.h>

struct rb{
	char cor;
	int info;
	struct rb *pai;
	struct rb *esq;
	struct rb *dir;
};

struct arvoreRB{
	struct rb *raiz;
};

void preorder(struct rb *no){
	if(no == NULL)
		return;

	printf("%d ", no->info);
	if(no->cor == 'p')
		puts("BLACK");
	else
		puts("RED");
	preorder(no->esq);
	preorder(no->dir);
}

void teste(struct rb *no){
	if(no == NULL)
		return;

	printf("%d, end: %p,	pai: %p		esq: %p		dir: %p		cor: ", no->info, no, no->pai, no->esq, no->dir);
	if(no->cor == 'p')
		puts("BLACK");
	else
		puts("RED");
	teste(no->esq);
	teste(no->dir);
}

void LeftRotate(struct rb *x){
	struct rb *aux;
	aux = x->dir;
	if(aux->esq != NULL){
		aux->esq->pai = x;
	}
	x->dir = aux->esq;
	aux->esq = x;
	aux->pai = x->pai;
	if(x->pai != NULL){
		if(x->pai->esq == x){
			x->pai->esq = aux;
		}
		else{
			x->pai->dir = aux;
		}
	}
	x->pai = aux;
//	puts("Rodou");
}

void RightRotate(struct rb *x){
	struct rb *aux;
	aux = x->esq;
	if(aux->dir != NULL){
		aux->dir->pai = x;
	}
	x->esq = aux->dir;
	aux->dir = x;
	aux->pai = x->pai;
	if(x->pai != NULL){
		if(x->pai->esq == x){
			x->pai->esq = aux;
		}
		else{
			x->pai->dir = aux;
		}
	}
	x->pai = aux;
//	puts("Rodou");
}

void ajuste(struct arvoreRB *arvore, struct rb *no){// (raiz, e o no novov)
	while(no->pai != NULL && no->pai->cor == 'v'){ //se o pai é preto, não precisa fazer nada
		if(no->pai == no->pai->pai->esq){//está na subarvore esquerda
			struct rb *tio = no->pai->pai->dir;
			if(tio != NULL && tio->cor == 'v'){ //pai vermelho e tio vermelho
				no->pai->cor = 'p';
				tio->cor = 'p';
				no->pai->pai->cor = 'v';
				no = no->pai->pai; //nó recebeu endereço do avô
			}
			else{ //pai vermelho e tio preto ou null (cor e rotações)
				if (no == no->pai->dir){
					no = no->pai;
					LeftRotate(no);
				}
				no->pai->cor = 'p';
				if(no->pai->pai != NULL){
					no->pai->pai->cor = 'v';
					RightRotate(no->pai->pai);
				}
			}
		}
		else{ //está na subarvore direita
			//puts("subarvore direita");
			struct rb *tio = no->pai->pai->esq;
			if(tio != NULL && tio->cor == 'v'){ //pai vermelho e tio vermelho
				//puts("tio vermelho incio");
				no->pai->cor = 'p';
				tio->cor = 'p';
				no->pai->pai->cor = 'v';
				no = no->pai->pai;
				//puts("tio vermelho fim");
			}
			else{ //pai vermelho e tio preto ou null (rotações e alteração de cores)
				if(no == no->pai->esq){
					no = no->pai;
					RightRotate(no);
				}
				no->pai->cor = 'p';
				if(no->pai->pai !=NULL){
					no->pai->pai->cor = 'v';
					LeftRotate(no->pai->pai);
				}
			}
		}
	}
	if(no->pai == NULL)
		arvore->raiz = no;
	else if(no->pai->pai == NULL)
		arvore->raiz = no->pai;
	arvore->raiz->cor = 'p';
}

void inserir(struct arvoreRB *arvore, int k){
	struct rb *y = NULL;
	struct rb *x = arvore->raiz;
	while (x != NULL){
		y = x;
		if (k < x->info)
			x = x->esq;
		else
			x = x->dir;
	}
	struct rb *no = malloc(sizeof(struct rb));
	no->info = k;
	no->pai = y;

	if(y == NULL){
		arvore->raiz = no;
		arvore->raiz->cor = 'p';
		arvore->raiz->esq = NULL;
		arvore->raiz->dir = NULL;
		arvore->raiz->pai = NULL;
		return;
	}
	else if (no->info < y->info){
		y->esq = no;
	}
	else{
		y->dir = no;
	}

	no->esq = NULL;
	no->dir = NULL;
	no->cor = 'v';
//	printf("%d, end: %p,	pai: %p		esq: %p		dir: %p\n", no->info, no, no->pai, no->esq, no->dir);
//	printf("pai->%d, end: %p,	pai: %p		esq: %p		dir: %p\n", no->pai->info, no->pai, no->pai->pai, no->pai->esq, no->pai->dir);
	ajuste(arvore, no);

}

struct rb *busca_no(struct arvoreRB *arvore, int k){
	struct rb *aux = arvore->raiz;
	while(aux != NULL){
		if(k < aux->info){
			aux = aux->esq;
		}
		else{
			if(k == aux->info){
				break;
			}
			aux = aux->dir;
		}
	}
	return aux;
}

void remover(struct arvoreRB *arvore){
	struct rb *no = arvore->raiz;
	while(no->esq != NULL){
		no = no->esq;
	}
	printf("%d\n", no->info);

	if(no->dir == NULL && no->pai == NULL){
		free(no);
		arvore->raiz = NULL;
		return;
	}
	else if (no->dir != NULL && no->pai == NULL){
		arvore->raiz = no->dir;
		no->dir->pai = NULL;
		no->dir->cor = 'p';
		free(no);
		return;
	}

	if(no->pai != NULL)
		no->pai->esq = NULL;


	//puts("ta nos ifs");
	if(no->cor == 'v'){ //se o nó for vermelho, não altera o balanceamento da árvore
		puts("caso 0");
		free(no);
	}
	else if(no->dir != NULL){
		puts("caso 1");
		struct rb *aux = no;
		no->pai->esq = no->dir;
		no->dir->pai = no->pai;
		if(no->dir->cor == 'v'){
			no->dir->cor = 'p';
		}
		else{
			no->dir->cor = 'v';
		}
		no = no->pai;
		free(aux);
	}
	else if(no->pai->dir->esq != NULL){
		puts("caso 2");
		no = no->pai;
		free(no->esq);
		no->cor = 'p';
		LeftRotate(no);
		no->dir->cor = 'v';
		no->pai->cor = 'v';
		if(no->pai->dir != NULL){
			no->pai->dir->cor = 'p';
		}
	}
	else if(no->pai->dir->dir != NULL){
		puts("caso extra");
		no = no->pai;
		free(no->esq);
		LeftRotate(no);
		no->pai->dir->cor = 'p';
	}
	else{
		puts("caso 3");
		no = no->pai;
		free(no->esq);
		no->cor = 'p';
		no->dir->cor = 'v';
		if(no->pai != NULL){
			no->pai->dir->cor = 'p';
			no->pai->dir->esq->cor = 'v';
			no->pai->dir->dir->cor = 'v';
		}
	}
	//printf("no: %d, pai: %d\n", no->info, no->pai->info);

	if(no->pai == NULL){
		arvore->raiz = no;
		arvore->raiz->cor = 'p';
		return;
	}
	if(no->pai->pai == NULL){
		arvore->raiz = no->pai;
		arvore->raiz->cor = 'p';
		//printf("raiz: %d\n", no->pai->info);
	}



}

void desalocar(struct rb *no){ //Limpar arvore
	if(no == NULL)
		return;

	desalocar(no->esq);
	desalocar(no->dir);
	free(no);
}

int main(){
	//inicializando a arvore RN
	struct arvoreRB arvore;
	arvore.raiz = NULL;
	int k;

	//Lendo os dados da entrada:
	//while (scanf(" %d", &k) != EOF) {
	//	inserir(&arvore, k);
	//}
	/*remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	preorder(arvore.raiz);
	desalocar(arvore.raiz);*/



	inserir(&arvore, 9);
	//remover(&arvore);
	inserir(&arvore, 8);
	inserir(&arvore, 7);
	inserir(&arvore, 6);
	inserir(&arvore, 1);
	//remover(&arvore);
	//inserir(&arvore, 24);
	//inserir(&arvore, 25);
	//inserir(&arvore, 49);
	//inserir(&arvore, 32);
	//inserir(&arvore, 36);
	//remover(&arvore);
	preorder(arvore.raiz);

	return 0;
}
