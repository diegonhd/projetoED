#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char byte;

typedef struct tagElementoLista {
    byte *data;// ponteiro para o dado a ser armazenado na lista
    void *nextElemento;// ponteiro para o proximo elemento da lista;
    void *prevElemento;// ponteiro para o elemento anterior da lista;
} TElementoLista;

typedef struct tagLista {
    bool isCircular;// indica se a lista e circular
    bool isDoubleChain;// indica se a lista é duplamente encadeada
    int nElementos; // numero de elementos da lista
    int sizeElemento;// tamanho do elemento da lista
    TElementoLista *first;// ponteiro para o primeiro elemento da lista
    TElementoLista *last;// ponteiro para ultimo elemento da lista
    TElementoLista *current;// ponteiro para ultimo elemento da lista
} TLista;

// metodos de acesso do objeto lista

void Lista_cria(TLista *lista,int sizeElemento,bool isCircular,bool isDoubleChain);
void Lista_destroi(TLista *lista);
byte *Lista_first(TLista *lista);
void Lista_next(TLista *lista);
void Lista_prev(TLista *lista);
byte *Lista_last(TLista *lista);
bool Lista_inserir(TLista *lista, byte *data);
bool Lista_removeCorrente(TLista *lista);
bool Lista_removeUltimo(TLista *lista);
void Lista_goFirst(TLista *lista);
void Lista_goLast(TLista *lista);

TElementoLista *List_getCurrentItem(TLista *lista);

void mostra_ElementosPrevLista(TLista *lista, int numero);
void mostra_ElementosLista(TLista *lista, int numero);



void Lista_cria(TLista *lista,int sizeElemento,bool isCircular, bool isDoubleChain){
    lista->isCircular = isCircular;
    lista->isDoubleChain = isDoubleChain;
    lista->nElementos = 0;
    lista->sizeElemento = sizeElemento;
    lista->first = NULL;// ponteiro para o primeiro elemento da lista
    lista->last  = NULL;// ponteiro para ultimo elemento da lista
    lista->current = NULL;
}
void Lista_destroi(TLista *lista){
    int i,n;
    if (lista->nElementos != 0){
        n = lista->nElementos;
        Lista_goLast(lista);
        for( i =0; i< n;i++){
            Lista_removeUltimo(lista);
        }
    }
    lista->nElementos = 0;
    lista->sizeElemento = 0;
    lista->first = NULL;// ponteiro para o primeiro elemento da lista
    lista->last  = NULL;// ponteiro para ultimo elemento da lista
    lista->current = NULL;
}

byte *Lista_first(TLista *lista){
    lista->current = lista->first;
    return lista->first->data;
}
void Lista_next(TLista *lista){
    if(lista->current->nextElemento != NULL){
        lista->current = lista->current->nextElemento;
    }
}
void Lista_prev(TLista *lista){
    if(lista->isDoubleChain){
        if(lista->current->prevElemento != NULL){
            lista->current = lista->current->prevElemento;
        }
    }
}
byte *Lista_last(TLista *lista){
    return lista->last->data;
}

bool Lista_inserir(TLista *lista, byte *data){
    TElementoLista *item;
    if(data !=NULL){
        // testa se é o primeiro elemento
        if(lista->nElementos == 0){
            // aloca area para o elemento da lista
            if( (item = malloc(sizeof(TElementoLista)))!= NULL){
                // aloca area para o dado
                if((item->data = malloc(lista->sizeElemento))!=NULL){
                    // copia o dado
                    memcpy(item->data,data, lista->sizeElemento);
                    // seta NULL para o proximo elemento pois a lista tem um so elemento no caso de lista simples
                    // e o proprio elemento no caso de lista circular
                    item->nextElemento = lista->isCircular ? item:NULL;
                    if (lista->isDoubleChain){
                        // seta NULL para o proximo elemento pois a lista tem um so elemento
                        item->prevElemento = lista->isCircular ? item:NULL;
                    }
                    else{
                        item->prevElemento = NULL;
                    }
                    // atualiza os ponteiros da lista
                    lista->first = item;
                    lista->current = item;
                    lista->last = item;
                    lista->nElementos++;
                }
            }
        }
        else{
            // aloca area para o elemento da lista
            if( (item = malloc(sizeof(TElementoLista)))!= NULL){
                // atualiza o ponteiro do proximo elemento do ultimo anterior para ser novo elemento
                lista->last->nextElemento = item;
                if(lista->nElementos == 1){
                    lista->first->nextElemento = item;
                    if (lista->isDoubleChain == true){
                        lista->first->prevElemento = lista->isCircular ? item:NULL;
                    }
                    else{
                        lista->first->prevElemento = NULL;
                    }
                }
                else {
                    lista->current->nextElemento = item;
                }
                // aloca area para o dado
                if((item->data = malloc(lista->sizeElemento))!=NULL){
                    // copia o dado
                    memcpy(item->data,data, lista->sizeElemento);
                    // seta NULL para o proximo elemento pois a lista tem um so elemento
                    item->nextElemento = lista->isCircular ? lista->first:NULL;
                    if (lista->isDoubleChain){
                        // seta NULL para o elemento anterior pois a lista tem um so elemento
                        item->prevElemento = lista->current;
                        lista->first->prevElemento = lista->isCircular?item:NULL;
                    }
                    else{
                        item->prevElemento = NULL;
                    }
                    // atualiza os ponteiros da lista
                    lista->current = item;
                    lista->last = item;
                    lista->nElementos++;
                }
            }
        }
       
       
    }
}
void TElementoLista_dump(TElementoLista *element, int size){
    int i;
    byte *point;
    printf ("data = %x\n", element->data);
    printf ("next = %x\n",element->nextElemento);
    printf ("prev = %x\n",element->prevElemento);
    printf("Conteudo data\n");
    point = (byte*)(element->data);
    for (i = 0; i< size;i++){
        printf("%04x : %02x : %03d : %c \n",point, (*point), (*point), (*point));
        point++;
    }
}
void Lista_dumpParam(TLista *lista){
    TElementoLista *item;
    int i;
   
    printf("n.elementos      = %d\n",lista->nElementos); // numero de elementos da lista
    printf("Tamanho elem     = %d\n",lista->sizeElemento);// tamanho do elemento da lista
    printf("Ponteiro first   = %x\n", lista->first);// ponteiro para o primeiro elemento da lista
    printf("Ponteiro last    = %x\n",lista->last);// ponteiro para ultimo elemento da lista
    printf("Ponteiro current = %x\n",lista->current);// ponteiro para ultimo elemento da lista
    if(lista->first != NULL){
        item = lista->first;
        i = 0;
        do{
            TElementoLista_dump(item,lista->sizeElemento);
            item = item->nextElemento;
            i++;
        }
        while(i <lista->nElementos);
    }
    printf("-----------------------------------\n");
   
}

TElementoLista *Lista_getPenultimo(TLista *lista){
    TElementoLista *point;

    point = NULL;
    if(lista->nElementos > 0){  
        // atribuo ao primeiro elemento da lista
        point=lista->first;
        // Percorro a lista ate que seja o penultimo elemento, isto e,
        // o proximo e o ultimo elemento da lista
        while (point->nextElemento != lista->last){
            point = point->nextElemento;
        }
    }
    return point;
}

TElementoLista *Lista_getAnterior(TLista *lista){
    TElementoLista *point;

    point = NULL;
    if(lista->nElementos > 0){  
        // atribuo ao primeiro elemento da lista
        point=lista->first;
        // Percorro a lista ate que seja o penultimo elemento, isto e,
        // o proximo e o ultimo elemento da lista
        while (point->nextElemento != lista->current){
            point = point->nextElemento;
        }
    }
    return point;
}


bool Lista_removeCorrente(TLista *lista){
    TElementoLista *item,*anterior, *proximo;
   
    if(lista->nElementos == 0){
        return false;
    }
    else{
        if (lista->nElementos == 1){
            item = lista->first;
            // liberei area e memoria alocada para os dados
            free(item->data);
            // atribui NULL o ponteiro do proximo, mas nao seria necessário
            item->nextElemento = NULL;

            // atribui ao ponteiro do prev o valor nulo
            if(lista->isDoubleChain==true){
                item->prevElemento = NULL;
            }
            // liberei a area do item de lista                
            free(item);
            lista->first   = NULL;
            lista->last    = NULL;
            lista->current = NULL;
            lista->nElementos--;
        }
        else{
            // caso n > 1;
            // libera a area de dados do ultimo elemento
            free(lista->current->data);
            if(lista->isDoubleChain==true){
                anterior = lista->current->prevElemento;
            }
            else{
                anterior = Lista_getAnterior(lista);
            }
            proximo = lista->current->nextElemento;
            // atribui ao elemento next do anterior apontar para o elemento proximo
            // caso que corrente e o ultimo
            if(lista->current == lista->last){
                anterior->nextElemento = lista->isCircular ? proximo: NULL;
                lista->last = anterior;
            }
            // caso que o corrente e  primeiro
            if(lista->current == lista->first){
                if ( anterior != NULL){
                    anterior->nextElemento = lista->isCircular ? proximo: NULL;
                }
                else{
                    if (proximo != NULL){
                        proximo->prevElemento = NULL;
                    }
                }
                lista->first = proximo;
            }
            else{
                // caso geral
                anterior->nextElemento = proximo;
            }
            // libera a area do ultimo item
            if(lista->isDoubleChain){
                proximo->prevElemento = anterior;
            }
           
            free(lista->current);
            // faz o ultimo e o corrente serem o penultimo
            lista->current = anterior;
            // decrementa o numero de elementos da lista
            lista->nElementos--;
        }
    }
    return true;
   
}

bool Lista_removeUltimo(TLista *lista){
    TElementoLista *item,*penultimo;
   
    if(lista->nElementos == 0){
        return false;
    }
    else{
        if (lista->nElementos == 1){
            item = lista->first;
            // liberei area e memoria alocada para os dados
            free(item->data);
            // atribui NULL o ponteiro do proximo, mas nao seria necessário
            item->nextElemento = NULL;

            // atribui ao ponteiro do prev o valor nulo
            if(lista->isDoubleChain==true){
                item->prevElemento = NULL;
            }
            // liberei a area do item de lista                
            free(item);
            lista->first   = NULL;
            lista->last    = NULL;
            lista->current = NULL;
            lista->nElementos--;
        }
        else{
            // caso n > 1;
            // libera a area de dados do ultimo elemento
            free(lista->last->data);
            if(lista->isDoubleChain==true){
                penultimo = lista->last->prevElemento;
            }
            else{
                penultimo = Lista_getPenultimo(lista);
            }
            // coloca o elemento como ultimo, isto é, o proximo é nulo
            penultimo->nextElemento = lista->isCircular ? lista->first: NULL;
            // libera a area do ultimo item
            if(lista->isDoubleChain){
                lista->first->prevElemento = penultimo;
            }
            free(lista->last);
            // faz o ultimo e o corrente serem o penultimo
            lista->last = penultimo;
            lista->current = penultimo;
            // decrementa o numero de elementos da lista
            lista->nElementos--;
        }
    }
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


TElementoLista *List_getCurrentItem(TLista *lista){
    return lista->current;
}

void mostra_ElementosLista(TLista *lista, int numero){
    int i, elemento;
    TElementoLista *item;
    if(lista->nElementos > 0){
        // Vou para o primeiro elemento
        Lista_goFirst(lista);
        // Vou executar numero de next na lista
        for(i=0; i< numero; i++){
            // pega o elemento corrente
            item = List_getCurrentItem(lista);
            // copiando o conteudo de dado do item para  variavel elemento
            if (item != NULL){
                memcpy(&elemento,item->data, sizeof(int));
            }
            printf("lista[%d] = %d\n",i,elemento);
            Lista_next(lista);
        }
    }
    else{
        printf("Lista vazia!\n");
    }
}
void mostra_ElementosPrevLista(TLista *lista, int numero){
    int i, elemento;
    TElementoLista *item;
    if((lista->nElementos > 0)&&(lista->isDoubleChain ==true)){
        // Vou para o ultimo elemento
        Lista_goLast(lista);
        // Vou executar numero de next na lista
        for(i=0; i< numero; i++){
            // pega o elemento corrente
            item = List_getCurrentItem(lista);
            // copiando o conteudo de dado do item para  variavel elemento
            if (item != NULL){
                memcpy(&elemento,item->data, sizeof(int));
            }
            printf("lista[%d] = %d\n",i,elemento);
            Lista_prev(lista);
        }
    }
    else{
        printf("Lista vazia ou lista nao é circular!\n");
    }
}


//testando


typedef struct{
    char descricao[50];
    float valor;
    char tipo[10];
}Operacao;


void mostrar_operacao_atual(TLista *lista) {
    Operacao op;
    if (lista->current != NULL) {
        memcpy(&op, lista->current->data, sizeof(Operacao));
        printf("Operaçao atual:\n");
        printf("Tipo: %c\n", op.tipo);
        printf("Valor: %.2f\n", op.valor);
        printf("Descricao da operacao: %s\n", op.descricao);
    } else {
        printf("Nenhuma operacao registrada.\n");
    }
}

void mostra_OperacoesLista(TLista *lista) {
    int i = 0;
    TElementoLista *item;
    Operacao op;

    if(lista->nElementos > 0){
        Lista_goFirst(lista);

        do {
            item = List_getCurrentItem(lista);
            if (item != NULL) {
                memcpy(&op, item->data, sizeof(Operacao));
                printf("Operacao %d:\n", i + 1);
                printf("  Tipo      : %s\n", op.tipo);
                printf("  Valor     : %.2f\n", op.valor);
                printf("  Descricao : %s\n", op.descricao);
                printf("--------------------------\n");
            }
            Lista_next(lista);
            i++;
        } while(i < lista->nElementos);
    } else {
        printf("Lista vazia!\n");
    }
}


float saldo = 0.0;

void realizar_deposito(TLista *lista) {
    Operacao op;
    printf("Digite a descricao do deposito: ");
    fgets(op.descricao, sizeof(op.descricao), stdin);
    op.descricao[strcspn(op.descricao, "\n")] = '\0';
    
    printf("Digite o valor a depositar: ");
    scanf("%f", &op.valor);
    getchar(); // limpar buffer

    if (op.valor <= 0) {
        printf("Valor invalido.\n");
        return;
    }

    saldo += op.valor;
    strcpy(op.tipo, "DEPOSITO");
    Lista_inserir(lista, (byte *)&op);
    printf("Deposito realizado com sucesso. Saldo atual: R$ %.2f\n", saldo);
}


void realizar_saque(TLista *lista) {
    Operacao op;
    printf("Digite a descricao do saque: ");
    fgets(op.descricao, sizeof(op.descricao), stdin);
    op.descricao[strcspn(op.descricao, "\n")] = '\0';

    printf("Digite o valor a sacar: ");
    scanf("%f", &op.valor);
    getchar(); // limpar buffer

    if (op.valor <= 0 || op.valor > saldo) {
        printf("Saque invalido. Saldo atual: R$ %.2f\n", saldo);
        return;
    }

    saldo -= op.valor;
    strcpy(op.tipo, "SAQUE");
    Lista_inserir(lista, (byte *)&op);
    printf("Saque realizado com sucesso. Saldo atual: R$ %.2f\n", saldo);
}

void mostrar_saldo() {
    printf("Saldo atual: R$ %.2f\n", saldo);
}



int main() {
    TLista lista;
    Lista_cria(&lista, sizeof(Operacao), false, true);
    
    int opcao;
    do {
        printf("\n---- Menu Conta Corrente ----\n");
        printf("1 - Depositar\n");
        printf("2 - Sacar\n");
        printf("3 - Mostrar saldo");
        printf("4 - Avancar (proxima)\n");
        printf("5 - Voltar (anterior)\n");
        printf("6 - Mostrar operacao atual\n");
        printf("7 - Mostrar histórico completo\n");
        printf("8 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar o buffer
        
        
        switch(opcao){
            case 1:
                realizar_deposito(&lista);
                break;
            case 2:
                realizar_saque(&lista);
                break;
            case 3:
                mostrar_saldo();
                break;
            case 4:
                Lista_next(&lista);
                mostrar_operacao_atual(&lista);
                break;
            case 5:
                (&lista);
                mostrar_operacao_atual(&lista);
                break;
            case 6:
                mostrar_operacao_atual(&lista);
                break;
            case 7:
                mostra_OperacoesLista(&lista);
                break;
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
       } while (opcao != 8);
        

    Lista_destroi(&lista);
    return 0;
}
    



    


