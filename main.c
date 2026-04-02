#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
    Node *p = L->begin;
    printf("L -> ");
    // enquanto p n�o chegou ao fim da lista, isto �,
    // enquanto p estiver apontando para um n� da lista

    while (p != NULL) {
        printf("%d ->", p->val);
        p = p->next;
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



LinkedList *LinkedList_append(LinkedList *L1, LinkedList *L2)
{
    Node *p = L2->begin;


    while(p != NULL)
    {
        LinkedList_add_last(L1, p->val);
        p = p->next;
    }
    return L1;

}

//NÃO TERMINEI
//O COMMIT DEU CERTO

//LinkedList *LinkedList_concatena(LinkedList *L1, LinkedList *L2)
//{
//    Node *p = L2->begin;
//
//    LinkedList *L3 = LinkedList_create();
//    Linked_copia(L1, L3);
//    LinkedList_append
//}




int main (){

    LinkedList *La = LinkedList_create();
    LinkedList *Lb = LinkedList_create();
    LinkedList *Lc = LinkedList_create();

    LinkedList_add_first(La,5);
    LinkedList_add_first(La,4);
    LinkedList_add_first(La,2);
    LinkedList_add_first(La,10);
    LinkedList_add_first(La,20);

    LinkedList_add_last(La, 15);

    LinkedList_print(La);
    printf("elemento 1 = %d\n", LinkedList_PrintBegin(La));
    printf("elemento %d = %d\n", La->contador, LinkedList_PrintEnd(La));
    printf("END = %d\n", La->end->val);

    printf("\nNumeros de elementos: %d\n", LinkedList_numero_elem(La));
    LinkedList_print(La);

    LinkedList_rem(La, 20);
    printf("\nNumeros de elementos: %d\n", LinkedList_numero_elem(La));
    LinkedList_print(La);

    LinkedList_rem(La, 10);
    LinkedList_rem(La, 2);
    LinkedList_rem(La, 4);
    LinkedList_rem(La, 5);
    printf("\nNumeros de elementos: %d\n", LinkedList_numero_elem(La));
    LinkedList_print(La);



    LinkedList_add_first(La, 8);

    printf("\nNumeros de elementos: %d\n", LinkedList_numero_elem(La));
    LinkedList_print(La);


    LinkedList_add_last(Lb, 5);
    LinkedList_add_last(Lb, 15);
    LinkedList_add_last(Lb, 50);

    LinkedList_append(La, Lb);
    LinkedList_print(La);

    Linked_copia_inverte(La, Lc);
    LinkedList_print(Lc);


    LinkedList_print(La);
    LinkedList_print(Lb);
    //LinkedList_concatena(La,Lb);

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
