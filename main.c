//testing
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

typedef struct _node {
    int val;
    struct _node *next;
} Node;


typedef struct _linked_list {

    Node *begin;
    Node *end;
    int contador;

} LinkedList;



Node *Node_create(int val) {
    Node *node = (Node*) calloc(1, sizeof(Node));
    node->val = val;
    node->next = NULL;
    return node;
}



LinkedList *LinkedList_create() {

    LinkedList *L = (LinkedList *) calloc(1, sizeof(LinkedList));
    L->begin = NULL;
    L->end = NULL;
    L->contador = 0;
    return L;
}

void LinkedList_add_first(LinkedList *L, int val) {

    Node *p = Node_create(val);

    if (L->begin == NULL){   //se a lista est� vazia

        p->next = L->begin;
        L->begin = p;
        L->end = p;

    } else {
        p->next = L->begin;
        L->begin = p;
    }
    L->contador++;

}



void LinkedList_print(LinkedList *L) {
    printf("L -> ");
    // enquanto p n�o chegou ao fim da lista, isto �,
    // enquanto p estiver apontando para um n� da lista

    if(L != NULL)
    {
        Node *p = L->begin;
        while (p != NULL)
        {
            printf("%d -> ", p->val);
            p = p->next;
        }
    }


    printf(" NULL  \n");
}

int LinkedList_numero_elem(LinkedList *L) {
    return (L->contador);
}



void LinkedList_rem(LinkedList *L, int valor) {

    Node *pos=NULL;
    Node *prev=NULL;

    if (L->begin != NULL)       // A lista não está vazia
    {
       if (L->begin->val == valor) //achou no inicio
       {
            if(L->end == L->begin) // só tem um elemento
            {
                pos=L-> begin;

                free(pos);
                L->contador--;
                L->begin=NULL;
                L->end=NULL;
            }
            else  //remover o primeiro elmento
            {
                pos = L->begin;
                L->begin = pos->next;
                free(pos);
                L->contador--;

            }
       }
       else  //nao achou o primeiro elemento da lista
       {
            pos=L->begin;
            while ((pos!=NULL)&& (pos-> val!=valor))
            {
                prev=pos;
                pos=pos->next;
            } // chegou ao final ou encontrou

            if(pos!=NULL) //encontrou o elemento
            {
                prev->next = pos->next;
                free(pos);
                L->contador--;
                if(prev->next == NULL) //era o último elemento
                {
                    L->end = prev;
                }
            }
       }
    }

}

void LinkedList_add_last(LinkedList *L, int val) {

    Node *p = Node_create(val);

    if (L->end == NULL){   //se a lista est� vazia

        p->next = L->begin;
        L->begin = p;
    } else {
        L->end->next = p;
    }
    L->end = p;
    L->contador++;

}

int LinkedList_PrintBegin(LinkedList *La){
    if(La->contador == 0){
        return -1;
    }
    else{
        return La->begin->val;
    }

}

int LinkedList_PrintEnd(LinkedList *La){
    if(La->contador == 0){
        return -1;
    }
    else{
        return La->end->val;
    }
}

void LinkedList_remover(LinkedList *L, int valor){

    Node *pos;
    Node *prev;

    if(L->begin != NULL){ //caso a lista esteja vazia
        pos = L->begin;

        if(pos->val == valor){ //caso o primeiro elemento seja o valor a ser excluído
            if(pos->next != NULL){ //caso não seja o único elemento
                L->begin = pos->next;
                free(pos);
            }
            else{ //caso seja o único elemento
                L->begin = NULL;
                L->end = NULL;
                free(pos);
            }
        }
        else{ //caso não seja o primeiro elemento
            while(pos->val != valor && pos->next != NULL){
                prev = pos;
                pos = pos->next;
            }
            if(pos->val == valor){
                if(pos->next == NULL){ //caso for o último elemento
                    prev->next = NULL;
                    L->end = prev;
                    free(pos);
                }else{
                    prev->next = pos->next;
                    free(pos);
                }

            }

        }

    }
}

void Linked_copia(LinkedList *L1, LinkedList *L2)
{
    Node *p = L1->begin;

    while(p != NULL)
    {
        LinkedList_add_last(L2, p->val);
        p = p->next;
    }

}

//aula (27/03)
void Linked_copia_inverte(LinkedList *L1, LinkedList *L2)
{
    Node *p = L1->begin;

    while(p != NULL)
    {
        LinkedList_add_first(L2, p->val);
        p = p->next;
    }

}



void LinkedList_append(LinkedList *L1, LinkedList *L2)
{
    Node *p = L2->begin;


    while(p != NULL)
    {
        LinkedList_add_last(L1, p->val);
        p = p->next;
    }

}



void LinkedList_concatena(LinkedList *L1, LinkedList *L2, LinkedList *L3)
{
    Linked_copia(L1, L3);
    LinkedList_append(L3, L2);
}

void LinkedList_transforma(LinkedList *L1, LinkedList *L2, LinkedList *L3)
{
    if(L1->begin == NULL)
    {
        L3->begin = L2->begin;
        L3->end = L2->end;
        L3->end->next = NULL;
        L3->contador = L2->contador;
    }
    else if(L2->begin == NULL)
    {
        L3->begin = L1->begin;
        L3->end = L1->end;
        L3->end->next = NULL;
        L3->contador = L2->contador;
    }
    else
    {
        L3->begin = L1->begin;
        L1->end->next = L2->begin;
        L3->end = L2->end;
        L3->end->next = NULL;
        L3->contador = L1->contador + L2->contador;
    }
    free(L1);
    free(L2);

}

void LinkedList_merge(LinkedList *L1, LinkedList *L2, LinkedList *L3)
{
    Node *p1 = L1->begin;
    Node *p2 = L2->begin;
    bool flag = true;

    while(p1 != NULL && p2 != NULL){
        if (flag){
            LinkedList_add_last(L3, p1->val);
            p1 = p1->next;
        } else{
            LinkedList_add_last(L3, p2->val);
            p2 = p2->next;
        }
        flag = !flag;
    }

    while(p1 != NULL){
        LinkedList_add_last(L3, p1->val);
        p1 = p1->next;
    }

    while(p2 != NULL){
        LinkedList_add_last(L3, p2->val);
        p2 = p2->next;
    }
}


int main (){

    setlocale(LC_ALL, "Portuguese");

    //criação das listas
    LinkedList *La = LinkedList_create();  //lista(A)
    LinkedList *Lb = LinkedList_create();  //lista02
    LinkedList *Lc = LinkedList_create();  //lista03

    //adicionando elementos na primeira posição da lista(A)
    LinkedList_add_first(La,5);
    LinkedList_add_first(La,4);
    LinkedList_add_first(La,2);
    LinkedList_add_first(La,10);
    LinkedList_add_first(La,20);

    //adicionando um elemento no final da lista(A)
    LinkedList_add_last(La, 15);

    //imprimindo a lista(A) na tela
    printf("Lista A: \n");
    LinkedList_print(La);
    printf("elemento 1 = %d\n", LinkedList_PrintBegin(La));
    printf("elemento %d = %d\n", La->contador, LinkedList_PrintEnd(La));
    printf("END = %d\n", La->end->val);

    printf("Numeros de elementos: %d\n\n", LinkedList_numero_elem(La));

    //Removendo um elemento da lista(A)
    printf("Removendo um elemento da Lista A:\n");
    LinkedList_rem(La, 20);
    printf("Numeros de elementos: %d\n", LinkedList_numero_elem(La));
    LinkedList_print(La);

      //Removendo 4 elementos da lista(A)
//    printf("\nRemovendo 4 elementos da Lista A:\n");
//    LinkedList_rem(La, 10);
//    LinkedList_rem(La, 2);
//    LinkedList_rem(La, 4);
//    LinkedList_rem(La, 5);
//    LinkedList_print(La);
//    printf("Numeros de elementos: %d\n\n", LinkedList_numero_elem(La));



    //adicionando um elemento no começo da lista(A)
    printf("Adicionando um elemento no comeco da Lista A:\n");
    LinkedList_add_first(La, 8);
    LinkedList_print(La);
    printf("Numeros de elementos: %d\n\n", LinkedList_numero_elem(La));


    printf("Lista A: ");
    LinkedList_print(La);
    //adicionando elementos no final da lista(B)
    printf("Lista B: ");
    LinkedList_add_last(Lb, 5);
    LinkedList_add_last(Lb, 15);
    LinkedList_add_last(Lb, 50);
    LinkedList_print(Lb);
    printf("Lista C: ");
    LinkedList_print(Lc);

        //adicionando a lista(B) no final da lista(A)
//    printf("\nLinkedList_append(La, Lb):\n");
//    LinkedList_append(La, Lb);
//    LinkedList_print(La);
//
//    printf("\nLinked_copia_inverte(La, Lc);\n");
//    Linked_copia_inverte(La, Lc);
//    LinkedList_print(Lc);
//
//
        //imprime as Lista A e a Lista B na tela
//    printf("\nLista A: ");
//    LinkedList_print(La);
//    printf("Lista B: ");
//    LinkedList_print(Lb);
//    printf("Lista C: ");
//    LinkedList_print(Lc);
//
        //trasforma a Lista A e Lista B em uma Lista C mantendo os endereços de memória originais
//    LinkedList_transforma(La, Lb, Lc);
//    La = NULL;
//    Lb = NULL;
//
        //imprime as 3 listas
//    printf("\nLista C: ");
//    LinkedList_print(Lc);
//    printf("\nLista A: ");
//    LinkedList_print(La);
//    printf("Lista B: ");
//    LinkedList_print(Lb);
//    Lc = NULL;
//    printf("a");


//    printf("\n\n\nLinkedList_concatena(La,Lb);\nLista C: ");
//    LinkedList_concatena(La, Lb, Lc);
//    LinkedList_print(Lc);


        //imprime as Lista A e a Lista B na tela
//    printf("\nLista A: ");
//    LinkedList_print(La);
//    printf("Lista B: ");
//    LinkedList_print(Lb);


    LinkedList_merge(La, Lb, Lc);
    printf("Lista C: ");
    LinkedList_print(Lc);



//    printf("elemento 1 = %d\n", LinkedList_PrintBegin(La));
//    printf("elemento %d = %d\n", La->contador, LinkedList_PrintEnd(La));
//
//    LinkedList_rem(La, 8);
//    LinkedList_rem(La, 15);
////    printf("elemento 1 = %d\n", LinkedList_PrintBegin(La));
////    printf("elemento %d = %d\n\n\n", La->contador, LinkedList_PrintEnd(La));
//

//    LinkedList_add_last(Lb,5);
//    LinkedList_add_last(Lb,4);
//    LinkedList_add_last(Lb,2);
//    LinkedList_add_last(Lb,20);
//    LinkedList_add_last(Lb,10);
//    LinkedList_print(Lb);
//
//    LinkedList_remover(Lb, 20);
//    LinkedList_print(Lb);
//    LinkedList_remover(Lb, 4);
//    LinkedList_print(Lb);
//    LinkedList_remover(Lb, 28);
//    LinkedList_print(Lb);
//    LinkedList_remover(Lb, 5);
//    LinkedList_print(Lb);
//    LinkedList_remover(Lb, 10);
//    LinkedList_print(Lb);
//    LinkedList_remover(Lb, 5);
//    LinkedList_print(Lb);
//    LinkedList_remover(Lb, 2);
//    LinkedList_print(Lb);


return (0);
}
