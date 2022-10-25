#include <stdio.h>
#include <stdlib.h>


typedef struct noRN{
     int chave;
     int cor; // 1 = vermelho, 0 = preto
     struct noRN *pai;
     struct noRN *esq;
     struct noRN *dir;
}noRN;