#include "StrList.h"
#include <string.h>
#include <stdio.h>
// Node & List Data Structures
typedef struct Node {
    char* data;
    struct Node* next;
} Node;

 typedef struct _StrList{
  Node* head;
  size_t size;
}StrList;


//------------------------------------------------
// Node implementation
//------------------------------------------------

// allocate memory for a new node and returns it.
Node* Node_alloc(char* data , Node* next){
    Node* p= (Node*) malloc(sizeof(Node));
    if(p==NULL){
        return NULL;
    }
    p->data=data;
    p->next=next;
    return p;
}

void Node_free(Node* node){
    if (node == NULL) {
        return;
    }
    free(node->data);
    free(node);
}
//------------------------------------------------
// List implementation
//------------------------------------------------

//allocate memory for a new list, return the list
StrList* StrList_alloc(){
    StrList* p= (StrList*)malloc(sizeof(StrList));
    if(p==NULL){
       return NULL;
    }
    p->head=NULL;
    p->size=0;
    return p;
}

void StrList_free(StrList* StrList){
    if(StrList==NULL){return;}
    Node* p1=StrList->head;
    Node* p2;
    while(p1 !=NULL){
        p2=p1;
        p1=p1->next;
        Node_free(p2);
    }
    free(StrList);
}

size_t StrList_size(const StrList* StrList){
    return StrList->size;
}

// return the node in the index
Node* getNodeAt(int index, const StrList* StrList) {
    if (StrList == NULL || index < 0) {
        return NULL;
    }
    int i = 0;
    Node* p = StrList->head;
    while (i < index && p != NULL) {
        p = p->next;
        i++;
    }
    return p;
}

void StrList_insertLast(StrList* StrList, const char* data){
    Node* new_node = Node_alloc(strdup(data), NULL);
    if(!new_node){ return;}
    Node* last= getNodeAt((int)StrList->size-1,StrList);
    if (last == NULL) {
        StrList->head = new_node;
    }
    else {
       last->next=new_node;
    }
    StrList->size++;
}

void StrList_insertAt(StrList* StrList,const char* data,int index){
    char* new_data= strdup(data);
    if(index==0) {
        Node* new_head= Node_alloc(new_data,StrList->head);
        if(!new_head){return;}
        Node* previous_head= StrList->head;
        StrList->head=new_head;
        StrList->head->next=previous_head;
    }
    else {
        Node* current = getNodeAt(index, StrList);
        Node* previous= getNodeAt(index-1,StrList);
        if (current == NULL) {
            free(new_data);  // Free the memory allocated for new_data
            return;
        } else {
            if(previous) {
                Node *new_node = Node_alloc(new_data, current);
                if(!new_node){return;}
                previous->next = new_node;
            }
        }
    }
    StrList->size++;
}
char* StrList_firstData(const StrList* StrList){
    Node* head= getNodeAt(0,StrList);
    if(head) {
        return head->data;
    }
    return NULL;
}

void StrList_print(const StrList* StrList) {
    Node* p = StrList->head;
    
    while (p != NULL) {
        printf("%s", p->data);
        // Print space only if the current node is not the last node
        if (p->next != NULL) {
            printf(" ");
        }
        p = p->next;
    }
    printf("\n");
}
void StrList_printAt(const StrList* Strlist,int index){
    Node* p= getNodeAt(index,Strlist);
    if(p){
        printf("%s\n",p->data);
    }
}
int StrList_printLen(const StrList* Strlist){
    if(!Strlist){
        return -1;
    }
    size_t ans=0;
    Node* current=Strlist->head;
    while(current){
        ans+= strlen(current->data);
        current=current->next;
    }
    return (int) ans;
}
int StrList_count(StrList* StrList, const char* data){
    if(!StrList || !data){
        return -1;
    }
    int ans=0;
    Node* current=StrList->head;
    while(current){
        if(strcmp(current->data,data)==0) {
            ans++;
        }
      current=current->next;

    }
    return  ans;
}

void StrList_removeAt(StrList* StrList, int index){
    if(index==0){
        Node* delete= StrList->head;
        StrList->head=delete->next;
        Node_free(delete);
        StrList->size--;
        return;
    }
    Node* previous= getNodeAt(index-1,StrList);
    Node* delete= getNodeAt(index,StrList);
    if (previous  && delete) {
        previous->next = delete->next;
        Node_free(delete);
        StrList->size--;
    }
}
void StrList_remove(StrList* StrList, const char* data){
    if(!StrList || !data){
        return;
    }
    int i=0;
    Node* current=StrList->head;
    while(current){
        int cmp= strcmp(data,current->data);
        if(cmp==0){
            Node* next=current->next;
            StrList_removeAt(StrList,i);
            current=next;
        }
        else {
            current=current->next;
             i++;
        }
    }
}

StrList* StrList_clone(const StrList* StrList) {
    if(!StrList || !StrList->head){
        return NULL;
    }
   struct StrList* clone_list = (struct StrList*) StrList_alloc();
   Node* original=StrList->head;

   while(original){
       char* clone_data= strdup(original->data);
       StrList_insertLast((struct _StrList *) clone_list, clone_data);
       original=original->next;
   }
   return (struct _StrList *) clone_list;
}

void StrList_sort( StrList* StrList){
    if (StrList == NULL || StrList->size <= 1) {
        // Nothing to sort or already sorted
        return;
    }
    Node* current_outside = StrList->head;
    while (current_outside) {
        Node* current_inside = StrList->head;
        while (current_inside->next) {
            int cmp = strcmp(current_inside->data, current_inside->next->data);
            if (cmp > 0) {
                // Swap the nodes
                char* tmp = current_inside->data;
                current_inside->data = current_inside->next->data;
                current_inside->next->data = tmp;
            }
            current_inside = current_inside->next;
        }
        current_outside = current_outside->next;
    }
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
        if(!StrList1 && !StrList2) {
            return 1;
        }
         if ((StrList1 && !StrList2) || (!StrList1 && StrList2) || (StrList1->size != StrList2->size)) {
            return 0;
        }
            Node *current_1 = StrList1->head;
            Node *current_2 = StrList2->head;
            while (current_1 && current_2) {
                int cmp = strcmp(current_2->data, current_1->data);
                if (cmp != 0) {
                    return 0;
                }
                current_1 = current_1->next;
                current_2 = current_2->next;
            }

            return 1;
        }

int StrList_isSorted( StrList* list) {

    if (StrList_size(list) <= 1) {
        return 1; // An empty list or a single element list is considered sorted
    }

    Node *current = list->head;
    while (current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0) {
            return 0; // List is not sorted
        }
        current = current->next;
    }

    return 1; // List is sorted
}

void StrList_reverse( StrList* StrList){
    if(StrList==NULL || StrList->head==NULL){
        return;
    }
    Node* prev=NULL;
    Node* current=StrList->head;
    Node* next=NULL;
    while(current){
        next=current->next;
        current->next=prev;
        prev=current;
        current=next;
    }
    StrList->head=prev;
}







