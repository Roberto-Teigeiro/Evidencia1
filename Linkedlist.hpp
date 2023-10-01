#include <iostream>

using namespace std;
class Node {
    public:
    std::string data;
    Node* next;
    Node* prev;
    Node()
    {
        data = "0";
        next = NULL;
        prev = NULL;
        
    }
    
    Node(std::string data)
    {
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }};
class LinkedList{
    private:
    Node* Front;
    Node* Rear;
    public:
    LinkedList(){Front=NULL; Rear=NULL;}
    void insertion(std::string val);
    void mindeQueue();
    void maxdeQueue();
    bool isEmpty(); 
    bool isFull();
    int peek();
    void printQueue();
  };
