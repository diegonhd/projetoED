#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

typedef struct {
    int id;
    float value;
    char type[15];
    char date[20];
    char instituicao[10];
    char destino[30];
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

EXPORT void Lista_cria(TLista *lista);
void Lista_destroi(TLista *lista);
EXPORT bool Lista_next(TLista *lista);
EXPORT bool Lista_prev(TLista *lista);
EXPORT int Lista_getSize(TLista *lista);
bool Lista_inserir(TLista *lista, Operation *data);
EXPORT void Lista_goFirst(TLista *lista);
EXPORT void Lista_goLast(TLista *lista);

// Código adaptado para facilitar a transição e integração com Python.

EXPORT bool realizar_deposito(TLista *lista, float valor, char *date);
EXPORT bool realizar_saque(TLista *lista, float valor, char *date);
EXPORT bool realizar_transferencia(TLista *lista, float valor, char *date, char *destino);
EXPORT Operation *get_currentOperation(TLista *lista);
EXPORT Operation *get_firstOperation(TLista *lista);
EXPORT Operation *get_lastOperation(TLista *lista);
EXPORT char *get_operations(TLista *lista);
EXPORT float get_saldo(TLista *lista);



EXPORT void Lista_cria(TLista *lista){
    lista->nElementos = 0;
    lista->sizeElemento = sizeof(Operation);
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
    
    novo->data = (Operation *) malloc(sizeof(Operation));
    
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

EXPORT bool Lista_next(TLista *lista){
    if (lista->current == NULL || lista->current->nextElemento == NULL) return false;
    lista->current = lista->current->nextElemento;
    return true;
}

EXPORT bool Lista_prev(TLista *lista){
    if (lista->current == NULL || lista->current->prevElemento == NULL) return false;
    lista->current = lista->current->prevElemento;
    return true;
}

EXPORT void Lista_goFirst(TLista *lista){
    if(lista->first != NULL){
        lista->current = lista->first;  
    }
}

EXPORT void Lista_goLast(TLista *lista){
  if(lista->last != NULL){
        lista->current = lista->last;  
  }
}

EXPORT int Lista_getSize(TLista *lista){
    return lista->nElementos;
}



// Código adaptado para facilitar a transição e integração com Python.


// Insere um depósito, retorna 0 sucesso, -1 erro (valor inválido)
EXPORT bool realizar_deposito(TLista *lista, float valor, char *date) {
    if (valor <= 0) return false;

    Operation op;
    op.id = lista->nElementos;
    op.value = valor;
    strcpy(op.type, "DEPOSITO");
    strcpy(op.date, date);
    strcpy(op.instituicao, "MyBank");
    strcpy(op.destino, "");

    lista->saldo += valor;

    if (!Lista_inserir(lista, &op)) {
        lista->saldo -= valor; // desfazer saldo
        return false;
    }

    lista->current = lista->last;

    return true;
}

// Insere um saque, valida saldo e retorna 0 sucesso, -1 erro
EXPORT bool realizar_saque(TLista *lista, float valor, char *date) {
    if (valor <= 0 || valor > lista->saldo) return false;

    Operation op;
    op.id = lista->nElementos;
    op.value = valor;
    strcpy(op.type, "SAQUE");
    strcpy(op.date, date);
    strcpy(op.instituicao, "MyBank");
    strcpy(op.destino, "");

    lista->saldo -= valor;

    if (!Lista_inserir(lista, &op)) {
        lista->saldo += valor;  // devolver saldo
        return false;
    }

    lista->current = lista->last;

    return true;
}

// Insere uma transferência, valida saldo e retorna 0 sucesso, -1 erro
EXPORT bool realizar_transferencia(TLista *lista, float valor, char *date, char *destino) {
    if (valor <= 0 || valor > lista->saldo) return false;

    Operation op;
    op.id = lista->nElementos;
    op.value = valor;
    strcpy(op.type, "TRANSFERENCIA");
    strcpy(op.date, date);
    strcpy(op.instituicao, "MyBank");
    strcpy(op.destino, destino);

    lista->saldo -= valor;

    if (!Lista_inserir(lista, &op)) {
        lista->saldo += valor;  // devolver saldo
        return false;
    }

    lista->current = lista->last;

    return true;
}

// Retorna ponteiro para operação atual ou NULL
EXPORT Operation *get_currentOperation(TLista *lista) {
    if (lista->current == NULL) return NULL;
    return lista->current->data;
}

// Retorna ponteiro para primeira operação ou NULL
EXPORT Operation *get_firstOperation(TLista *lista){
    if (lista->first == NULL) return NULL;
    return lista->first->data;
}

// Retorna ponteiro para ultima operação ou NULL
EXPORT Operation *get_lastOperation(TLista *lista){
    if (lista->last == NULL) return NULL;
    return lista->last->data;
}

// Preenche um array externo com até max operações, retorna quantas copiou
EXPORT char *get_operations(TLista *lista) {
    // Aloca um buffer grande (ajuste conforme necessário)
    char *json = malloc(4096);
    json[0] = '\0'; // inicializa como string vazia

    strcat(json, "[");

    Lista_goLast(lista);

    for (int i = 0; i < Lista_getSize(lista); i++) {
        char object[512];
        snprintf(object, sizeof(object),
                 "{\"id\": %d, \"value\": %.2f, \"type\": \"%s\", \"date\": \"%s\", \"instituicao\": \"MyBank\", \"destino\": \"%s\"}",
                 lista->current->data->id,
                 lista->current->data->value,
                 lista->current->data->type,
                 lista->current->data->date,
                 lista->current->data->destino);

        strcat(json, object);

        if (i != Lista_getSize(lista) - 1)
            strcat(json, ", ");

        if (!Lista_prev(lista))
            break;
    }

    strcat(json, "]");

    return json;
}

EXPORT float get_saldo(TLista *lista) {
    return lista->saldo;
}
