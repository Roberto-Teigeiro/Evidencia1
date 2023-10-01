#include "Linkedlist.hpp"


void LinkedList::insertion(std::string val){
    Node* nuevonodo= new Node(val);
    if(Front==NULL){
        Front=nuevonodo;
        Rear=nuevonodo;
        return;
    };
        Node* temp=Front;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=nuevonodo;
        nuevonodo->prev=temp;
        Rear=nuevonodo;
    };