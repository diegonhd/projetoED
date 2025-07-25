#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// typedef unsigned char byte;

typedef struct {
    float value;
    char type[15];
    char date[20];
} Operation;

typedef struct tagElementoLista {
    Operation *data;// ponteiro para o dado a ser armazenado na lista
    void *nextElemento;// ponteiro para o proximo elemento da lista;
    void *prevElemento;// ponteiro para o elemento anterior da lista;
} TElementoLista;

typedef struct tagLista {
    int nElementos; // numero de elementos da lista
    int sizeElemento;// tamanho do elemento da lista
    float saldo;
    TElementoLista *first;// ponteiro para o primeiro elemento da lista
    TElementoLista *last;// ponteiro para ultimo elemento da lista
    TElementoLista *current;// ponteiro para ultimo elemento da lista
} TLista;

void Lista_cria(TLista *lista);
void Lista_destroi(TLista *lista);
bool Lista_next(TLista *lista);
bool Lista_prev(TLista *lista);
int  Lista_getSize(TLista *lista);
bool Lista_inserir(TLista *lista, Operation *data);
void Lista_goFirst(TLista *lista);
void Lista_goLast(TLista *lista);

// Código adaptado para facilitar a transição e integração com Python.
bool realizar_deposito(TLista *lista, float valor, char *date);
bool realizar_saque(TLista *lista, float valor, char *date);
Operation *get_currentOperation(TLista *lista);
Operation *get_firstOperation(TLista *lista);
Operation *get_lastOperation(TLista *lista);
bool get_operacoes(TLista *lista, Operation *buffer, int max);
float get_saldo();



void Lista_cria(TLista *lista){
    lista->nElementos = 0;
    lista->sizeElemento = sizeof(TElementoLista);
    lista->first = NULL;// ponteiro para o primeiro elemento da lista
    lista->last  = NULL;// ponteiro para ultimo elemento da lista
    lista->current = NULL;
}

void Lista_destroi(TLista *lista){
    TElementoLista *atual = lista->first;
    while (atual != NULL) {
        TElementoLista *proximo = atual->nextElemento;
        free(atual->data);
        free(atual);
        atual = proximo;
    }
    lista->nElementos = 0;
    lista->sizeElemento = 0;
    lista->first = NULL;
    lista->last = NULL;
    lista->current = NULL;
}

bool Lista_inserir(TLista *lista, Operation *data){
    TElementoLista *novo = (TElementoLista *) malloc(sizeof(TElementoLista));
    if (novo == NULL) return false;
    
    novo->data = (Operation *) malloc(sizeof(lista->sizeElemento));
    
    memcpy(novo->data, data, lista->sizeElemento);
    novo->nextElemento = NULL;
    novo->prevElemento = NULL;
    
    if (lista->nElementos == 0) {
        lista->first = novo;
        lista->last = novo;
        lista->current = novo;
    }
    else {
        novo->prevElemento = lista->last;
        lista->last->nextElemento = novo;
        lista->last = novo;
    }
    
    lista->nElementos++;
    return true;
}

bool Lista_next(TLista *lista){
    if (lista->current == NULL || lista->current->nextElemento == NULL) return false;
    lista->current = lista->current->nextElemento;
    return true;
}

bool Lista_prev(TLista *lista){
    if (lista->current == NULL || lista->current->prevElemento == NULL) return false;
    lista->current = lista->current->prevElemento;
    return true;
}

void Lista_goFirst(TLista *lista){
    if(lista->first != NULL){
        lista->current = lista->first;  
    }
}

void Lista_goLast(TLista *lista){
  if(lista->last != NULL){
        lista->current = lista->last;  
  }
}

int Lista_getSize(TLista *lista){
    return lista->nElementos;
}




// Insere um depósito, retorna 0 sucesso, -1 erro (valor inválido)
bool realizar_deposito(TLista *lista, float valor, char *date) {
    if (valor <= 0) return false;

    Operation op;
    op.value = valor;
    strcpy(op.type, "DEPOSITO");
    strcpy(op.date, date);

    lista->saldo += valor;

    if (!Lista_inserir(lista, &op)) {
        lista->saldo -= valor; // desfazer saldo
        return false;
    }

    lista->current = lista->last;

    return true;
}

// Insere um saque, valida saldo e retorna 0 sucesso, -1 erro
bool realizar_saque(TLista *lista, float valor, char *date) {
    if (valor <= 0 || valor > lista->saldo) return false;

    Operation op;
    op.value = valor;
    strcpy(op.type, "SAQUE");
    strcpy(op.date, date);

    lista->saldo -= valor;

    if (!Lista_inserir(lista, &op)) {
        lista->saldo += valor;  // devolver saldo
        return false;
    }

    lista->current = lista->last;

    return true;
}

// Retorna ponteiro para operação atual ou NULL
Operation *get_currentOperation(TLista *lista) {
    if (lista->current == NULL) return NULL;
    return lista->current->data;
}

// Retorna ponteiro para primeira operação ou NULL
Operation *get_firstOperation(TLista *lista){
    if (lista->first == NULL) return NULL;
    return lista->first->data;
}

// Retorna ponteiro para ultima operação ou NULL
Operation *get_lastOperation(TLista *lista){
    if (lista->last == NULL) return NULL;
    return lista->last->data;
}

// Preenche um array externo com até max operações, retorna quantas copiou
bool get_operacoes(TLista *lista, Operation *buffer, int max) {
    if (lista->nElementos == 0) return true;

    int count = 0;
    TElementoLista *item = lista->first;
    while (item != NULL && count < max) {
        memcpy(&buffer[count], item->data, sizeof(Operation));
        count++;
        item = item->nextElemento;
        if (item == lista->first) break; // se circular
    }
    return count;
}

float get_saldo(TLista *lista) {
    return lista->saldo;
}




int main()
{

    return 0;
}
