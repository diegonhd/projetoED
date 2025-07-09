#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define TYPE_PILHA 1
#define TYPE_FILA 2

typedef struct tagFila {
    int        type;// tipo da estrutura Pilha ou Fila
    char    *buffer;// Buffer para guardar os elementos
    char     *first;// ponteiro para primeiro elemento
    char      *last;// ponteiro para ultimo
    int        size;// tamanho da fila
    int sizeElement;// tamanho do elemento da fila
    int  maxElement;// numero maximo de elementos
} TFila;

bool Fila_create(TFila *fila, int sizeElement, int max, int type);
void Fila_destroy(TFila *fila);
bool Fila_put(TFila *fila,char *data);
bool Fila_get(TFila *fila,char *data);
bool Fila_isEmpty(TFila *fila);
bool Fila_isFull(TFila *fila);
int Fila_size(TFila *fila);

bool Fila_create(TFila *fila, int sizeElement, int max, int type)
{
    // verifica se paramentros da funçao sao validos
    if(fila == NULL){
        return false;
    }
    if((sizeElement==0)||(max==0)){
        return false;
    }
    // aloca area para a fila
    if( (fila->buffer = malloc(sizeElement *max))==NULL){
        return false;
    }
    // inicializa propriedades da fila
    fila->size = 0;
    fila->sizeElement = sizeElement;
    fila->maxElement = max;
    fila->first = fila->buffer;
    fila->last  = fila->buffer;
    fila->size = 0;
    fila->type = type;
   
    return true;
}

void Fila_destroy(TFila *fila){
    // libera a area da fila
    free(fila->buffer);
    // zera propriedades
    fila->size = 0;
    fila->sizeElement = 0;
    fila->maxElement = 0;
    fila->first = NULL;
    fila->last  = NULL;
    fila->size = 0;
}
   

bool Fila_put(TFila *fila,char *data){
    if(data == NULL){
        return false;
    }
    if(Fila_isFull(fila)==false){
        // copia o dado para a Fila
        memcpy(fila->last,data,fila->sizeElement);
        // incremento o ponteiro do ultimo
        if (fila->size < fila->maxElement){
            // Incrementa ponteiro
            fila->last += fila->sizeElement;
            // checa se nao deve circular o ponteiro
            if(fila->type == TYPE_FILA){
                if(fila->last >= fila->buffer + fila->maxElement*fila->sizeElement)
                   fila->last = fila->buffer;
            }
           
            // increnta o numero de elementos na fila
            fila->size++;
            return true;
        }
    }
    return false;
   
}
bool Fila_get(TFila *fila,char *data){

    if(data == NULL){
        return false;
    }
    if (fila->type == TYPE_PILHA){  
        if(Fila_isEmpty(fila)==false){
            // Decrementa o ponteiro do ultimo
            if (fila->size > 0){
                // decrementa o last
                fila->last -= fila->sizeElement;
                memcpy(data,fila->last, fila->sizeElement);
                // decrementa o numero de elementos na fila
                fila->size--;
                return true;
            }
            else{
                return false;
            }
        }
        return false;
    }
    else{
        // Caso Fila
        if(Fila_isEmpty(fila)==false){
            // copia o dado para a Fila
            memcpy(data,fila->first, fila->sizeElement);
            // incremento o ponteiro do ultimo
            if (fila->size > 0){
                // Incrementa ponteiro
                fila->first += fila->sizeElement;
                // checa se nao deve circular o ponteiro
                if(fila->first>= fila->buffer + fila->maxElement*fila->sizeElement)
                   fila->first = fila->buffer;
               
                // increnta o numero de elementos na fila
                fila->size--;
                return true;
            }
            else{
                return false;
            }
        }
        return false;
    }
}
bool Fila_isEmpty(TFila *fila){
    if(fila->size == 0)
        return true;
    return false;
}
bool Fila_isFull(TFila *fila){
    if(fila->size == fila->maxElement){
        return true;
    }
    return false;
}

int Fila_size(TFila *fila){
    return fila->size;
}

void Fila_dump(TFila *fila){
    char *current,*j;
    int i;
    printf("*************************\n");
    printf("buffer = %04x\n", fila->buffer);
    printf("SizeElem = %d\n",fila->sizeElement);
    printf("Size     = %d\n",fila->size);
    printf("Max      = %d\n",fila->maxElement);
    printf("first  = %04x\n",fila->first);
    printf("Last   = %04x\n",fila->last);
    printf("-----------------------\n");
    current = fila->first;
    for( i =0; i< fila->size;i++){
        printf("Elemento [%d]\n",i);
        for(j=current; j < current + fila->sizeElement;j++){
            printf("%04x : %02x\n",j,(*j));
        }
        current += fila->sizeElement;
        if(current>= fila->buffer + fila->maxElement*fila->sizeElement)
           current = fila->buffer;
        printf("-----------------------\n");
    }
}

int main(){
    return 0;
}
