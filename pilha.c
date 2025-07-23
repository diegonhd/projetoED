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
    float saldo;
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

// bool Lista_inserir(TLista *lista, byte *data){
//     TElementoLista *item;
//     if(data !=NULL){
//         // testa se é o primeiro elemento
//         if(lista->nElementos == 0){
//             // aloca area para o elemento da lista
//             if( (item = malloc(sizeof(TElementoLista)))!= NULL){
//                 // aloca area para o dado
//                 if((item->data = malloc(lista->sizeElemento))!=NULL){
//                     // copia o dado
//                     memcpy(item->data,data, lista->sizeElemento);
//                     // seta NULL para o proximo elemento pois a lista tem um so elemento no caso de lista simples
//                     // e o proprio elemento no caso de lista circular
//                     item->nextElemento = lista->isCircular ? item:NULL;
//                     if (lista->isDoubleChain){
//                         // seta NULL para o proximo elemento pois a lista tem um so elemento
//                         item->prevElemento = lista->isCircular ? item:NULL;
//                     }
//                     else{
//                         item->prevElemento = NULL;
//                     }
//                     // atualiza os ponteiros da lista
//                     lista->first = item;
//                     lista->current = item;
//                     lista->last = item;
//                     lista->nElementos++;
//                 }
//             }
//         }
//         else{
//             // aloca area para o elemento da lista
//             if( (item = malloc(sizeof(TElementoLista)))!= NULL){
//                 // atualiza o ponteiro do proximo elemento do ultimo anterior para ser novo elemento
//                 lista->last->nextElemento = item;
//                 if(lista->nElementos == 1){
//                     lista->first->nextElemento = item;
//                     if (lista->isDoubleChain == true){
//                         lista->first->prevElemento = lista->isCircular ? item:NULL;
//                     }
//                     else{
//                         lista->first->prevElemento = NULL;
//                     }
//                 }
//                 else {
//                     lista->current->nextElemento = item;
//                 }
//                 // aloca area para o dado
//                 if((item->data = malloc(lista->sizeElemento))!=NULL){
//                     // copia o dado
//                     memcpy(item->data,data, lista->sizeElemento);
//                     // seta NULL para o proximo elemento pois a lista tem um so elemento
//                     item->nextElemento = lista->isCircular ? lista->first:NULL;
//                     if (lista->isDoubleChain){
//                         // seta NULL para o elemento anterior pois a lista tem um so elemento
//                         item->prevElemento = lista->current;
//                         lista->first->prevElemento = lista->isCircular?item:NULL;
//                     }
//                     else{
//                         item->prevElemento = NULL;
//                     }
//                     // atualiza os ponteiros da lista
//                     lista->current = item;
//                     lista->last = item;
//                     lista->nElementos++;
//                 }
//             }
//         }
       
       
//     }
// }

bool Lista_inserir(TLista *lista, byte *data) {
    // Cria novo elemento
    TElementoLista *novo = malloc(sizeof(TElementoLista));
    if (!novo) return false;

    novo->data = malloc(lista->sizeElemento);
    if (!novo->data) {
        free(novo);
        return false;
    }

    memcpy(novo->data, data, lista->sizeElemento);
    novo->nextElemento = NULL;
    novo->prevElemento = NULL;

    // Inserção na lista
    if (lista->nElementos == 0) {
        lista->first = novo;
        lista->last = novo;
        lista->current = novo;
    } else {
        lista->last->nextElemento = novo;
        if (lista->isDoubleChain)
            novo->prevElemento = lista->last;
        lista->last = novo;

        if (lista->isCircular)
            lista->last->nextElemento = lista->first;
    }

    lista->nElementos++;
    return true;
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




// Código adaptado para facilitar a transição e integração com Python.

typedef struct {
    float valor;
    char tipo[10];
} Operacao;
typedef unsigned char byte;

int realizar_deposito(TLista *lista, float valor);
int realizar_saque(TLista *lista, float valor);
float get_saldo();
Operacao* get_operacao_atual(TLista *lista);
int navegar_proximo(TLista *lista); // retorna 0 sucesso, -1 se não avançar
int navegar_anterior(TLista *lista);
int get_operacoes(TLista *lista, Operacao* buffer, int max);

// Insere um depósito, retorna 0 sucesso, -1 erro (valor inválido)
int realizar_deposito(TLista *lista, float valor) {
    if (valor <= 0) return -1;

    Operacao op;
    op.valor = valor;
    strcpy(op.tipo, "DEPOSITO");

    lista->saldo += valor;

    if (!Lista_inserir(lista, (byte*)&op)) {
        lista->saldo -= valor; // desfazer saldo
        return -1;
    }

    lista->current = lista->last;

    return 0;
}

// Insere um saque, valida saldo e retorna 0 sucesso, -1 erro
int realizar_saque(TLista *lista, float valor) {
    if (valor <= 0 || valor > lista->saldo) return -1;

    Operacao op;
    op.valor = valor;
    strcpy(op.tipo, "SAQUE");

    lista->saldo -= valor;

    if (!Lista_inserir(lista, (byte*)&op)) {
        lista->saldo += valor;
        return -1;
    }

    lista->current = lista->last;

    return 0;
}

float get_saldo(TLista *lista) {
    return lista->saldo;
}

// Retorna ponteiro para operação atual ou NULL
Operacao* get_operacao_atual(TLista *lista) {
    if (lista->current == NULL) return NULL;
    return (Operacao*)lista->current->data;
}

// Avança a posição atual, retorna 0 sucesso, -1 se já no fim
int navegar_proximo(TLista *lista) {
    if (lista->current == NULL || lista->current->nextElemento == NULL) return -1;
    lista->current = lista->current->nextElemento;
    return 0;
}

// Volta a posição atual, retorna 0 sucesso, -1 se já no início
int navegar_anterior(TLista *lista) {
    if (!lista->isDoubleChain) return -1; // não dá para voltar
    if (lista->current == NULL || lista->current->prevElemento == NULL) return -1;
    lista->current = lista->current->prevElemento;
    return 0;
}

// Preenche um array externo com até max operações, retorna quantas copiou
int get_operacoes(TLista *lista, Operacao* buffer, int max) {
    if (lista->nElementos == 0) return 0;

    int count = 0;
    TElementoLista *item = lista->first;
    while (item != NULL && count < max) {
        memcpy(&buffer[count], item->data, sizeof(Operacao));
        count++;
        item = item->nextElemento;
        if (item == lista->first) break; // se circular
    }
    return count;
}



//APAGAR PRA VERSÃO FINAL
//Funções pra testar o codigo em c

// void teste_deposito(TLista *lista, float valor) {
//     int res = realizar_deposito(lista, valor);
//     if (res == 0) {
//         printf("Depósito de R$ %.2f realizado com sucesso. Saldo atual: R$ %.2f\n", valor, get_saldo(lista));
//     } else {
//         printf("Falha ao realizar depósito de R$ %.2f\n", valor);
//     }
// }

// void teste_saque(TLista *lista, float valor) {
//     int res = realizar_saque(lista, valor);
//     if (res == 0) {
//         printf("Saque de R$ %.2f realizado com sucesso. Saldo atual: R$ %.2f\n", valor, get_saldo(lista));
//     } else {
//         printf("Falha ao realizar saque de R$ %.2f. Saldo atual: R$ %.2f\n", valor, get_saldo(lista));
//     }
// }

// void mostrar_operacao(Operacao *op, int indice) {
//     if (op != NULL) {
//         printf("Operação %d: Tipo: %s, Valor: R$ %.2f\n", indice, op->tipo, op->valor);
//     } else {
//         printf("Operação %d: Nenhuma operação.\n", indice);
//     }
// }

// void teste_navegacao(TLista *lista) {
//     printf("Navegando pelas operações:\n");
//     if (lista->nElementos == 0) {
//         printf("Lista vazia.\n");
//         return;
//     }
//     // Vai para o primeiro
//     Lista_goFirst(lista);
//     int idx = 1;
//     do {
//         Operacao *op = get_operacao_atual(lista);
//         mostrar_operacao(op, idx++);
//     } while(navegar_proximo(lista) == 0);
// }

// void teste_listar_todas_operacoes(TLista *lista) {
//     Operacao buffer[100];
//     int n = get_operacoes(lista, buffer, 100);
//     printf("Total de operações: %d\n", n);
//     for (int i = 0; i < n; i++) {
//         printf("Operação %d: Tipo: %s, Valor: R$ %.2f\n", i + 1, buffer[i].tipo, buffer[i].valor);
//     }
// }

// void menu() {
//     printf("\n==== MENU BANCO ====\n");
//     printf("1 - Realizar Depósito\n");
//     printf("2 - Realizar Saque\n");
//     printf("3 - Ver Saldo\n");
//     printf("4 - Ver Operação Atual\n");
//     printf("5 - Avançar Operação\n");
//     printf("6 - Voltar Operação\n");
//     printf("7 - Listar Todas Operações\n");
//     printf("0 - Sair\n");
//     printf("Escolha uma opção: ");
// }

// void interativo() {
//     TLista lista;
//     Lista_cria(&lista, sizeof(Operacao), false, true);
//     lista.saldo = 0.0f;

//     int opcao;
//     float valor;
//     Operacao buffer[100];

//     do {
//         menu();
//         scanf("%d", &opcao);
//         getchar(); // Limpar \n do buffer

//         switch (opcao) {
//             case 1:
//                 printf("Valor do depósito: R$ ");
//                 scanf("%f", &valor);
//                 if (realizar_deposito(&lista, valor) == 0)
//                     printf("Depósito realizado com sucesso!\n");
//                 else
//                     printf("Erro no depósito. Valor inválido!\n");
//                 break;

//             case 2:
//                 printf("Valor do saque: R$ ");
//                 scanf("%f", &valor);
//                 if (realizar_saque(&lista, valor) == 0)
//                     printf("Saque realizado com sucesso!\n");
//                 else
//                     printf("Erro no saque. Verifique o saldo ou valor!\n");
//                 break;

//             case 3:
//                 printf("Saldo atual: R$ %.2f\n", get_saldo(&lista));
//                 break;

//             case 4: {
//                 Operacao *op = get_operacao_atual(&lista);
//                 if (op)
//                     printf("Operação atual: %s de R$ %.2f\n", op->tipo, op->valor);
//                 else
//                     printf("Nenhuma operação atual.\n");
//                 break;
//             }

//             case 5:
//                 if (navegar_proximo(&lista) == 0)
//                     printf("Avançou para a próxima operação\n");
//                 else
//                     printf("Não é possível avançar.\n");
//                 break;

//             case 6:
//                 if (navegar_anterior(&lista) == 0)
//                     printf("Voltou para a operação anterior.\n");
//                 else
//                     printf("Não é possível voltar.\n");
//                 break;

//             case 7: {
//                 int n = get_operacoes(&lista, buffer, 100);
//                 printf("Total de operações: %d\n", n);
//                 for (int i = 0; i < n; i++) {
//                     printf("Operação %d: %s - R$ %.2f\n", i + 1, buffer[i].tipo, buffer[i].valor);
//                 }
//                 break;
//             }

//             case 0:
//                 printf("Saindo...\n");
//                 break;

//             default:

//                 printf("Opção inválida. Tente novamente.\n");
//         }

//     } while (opcao != 0);

//     Lista_destroi(&lista);
// }


int main() {
    //APAGAR PRA VERSÃO FINAL
    //interativo();
    return 0;
}




    





    


