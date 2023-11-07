#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <ctime>
#include <map>



using namespace std;
string GetCurrentTimestamp() {
    auto currentTime = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(currentTime);
    ostringstream oss;
    oss << put_time(localtime(&time), "%Y-%m-%d_%H-%M-%S");
    return oss.str();
}
struct datos {
    std::string mes;
    std::string dia;
    std::string hora;
    std::string ip;
    std::string puerto;
    std::string status;
    datos() {}
    datos(std::string m, std::string d, std::string h, std::string i, std::string p, std::string s)
        : mes(m), dia(d), hora(h), ip(i), puerto(p), status(s) 
    {}

    time_t toUnixTimestamp() {
        std::map<std::string, int> monthMap = {{"Jan", 0}, {"Feb", 1}, {"Mar", 2}, {"Apr", 3},
                                               {"May", 4}, {"Jun", 5}, {"Jul", 6}, {"Aug", 7},
                                               {"Sep", 8}, {"Oct", 9}, {"Nov", 10}, {"Dec", 11}};

        struct tm timeStruct = {};
        timeStruct.tm_mday = std::stoi(dia);
        timeStruct.tm_mon = monthMap[mes];
        timeStruct.tm_year = /* You'll need the year here */ 122; // e.g., 120 represents the year 2020
        timeStruct.tm_hour = std::stoi(hora.substr(0, 2));
        timeStruct.tm_min = std::stoi(hora.substr(3, 2));
        timeStruct.tm_sec = std::stoi(hora.substr(6, 2));

        return mktime(&timeStruct);
    }
     void mdatos(){
        cout << "Mes: " << mes << ", Dia: " << dia << ", Hora: " << hora << ", IP: " << ip << ", Puerto: " << puerto << ", Status: " << status << endl;

    }
};
class Node {
    public:
    datos* data;
    Node* next;
    Node* prev;
    Node()
    {
        data = new datos();
        next = NULL;
        prev = NULL;
        
    }
    
    Node(string mes, string dia, string hora, string ip,string puerto, string status)
    {
        this->data= new datos(mes,dia,hora,ip,puerto,status);
        this->next = NULL;
        this->prev = NULL;
    }};
class LinkedList{
    
    public:
    Node* Front;
    Node* Rear;

    LinkedList(){Front=NULL; Rear=NULL;}
    void insertion(string mes, string dia, string hora, string ip, string puerto, string status);
    void mindeQueue();
    void maxdeQueue();
    bool isEmpty(); 
    bool isFull();
    Node* merge(Node* left, Node* right);
    Node* mergeSort(Node* head);
    int peek();
        void performMergeSort() {Front = this->mergeSort(Front);}
    Node* getFront(){
        return Front;
    }
    void printList();
  };
void LinkedList::insertion(string mes, string dia, string hora, string ip, string puerto, string status){
    Node* nuevonodo= new Node(mes,dia,hora,ip,puerto,status);
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
Node* LinkedList::merge(Node* left, Node* right) {
    Node dummy;
    Node* tail = &dummy;

    while (left && right) {
        if (left->data->toUnixTimestamp() < right->data->toUnixTimestamp()) {
            tail->next = left;
            left->prev = tail;
            left = left->next;
        } else {
            tail->next = right;
            right->prev = tail;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = left ? left : right;

    while (tail->next) {
        tail->next->prev = tail;
        tail = tail->next;
    }

    return dummy.next;
}
Node* LinkedList::mergeSort(Node* head) {
    if (!head || !head->next) return head;

    Node* mid = head;
    Node* fast = head;

    while (fast->next && fast->next->next) {
        mid = mid->next;
        fast = fast->next->next;
    }

    Node* right = mid->next;
    mid->next = NULL;
    right->prev = NULL;

    Node* left = mergeSort(head);
    right = mergeSort(right);

    return merge(left, right);
}
int ipto_int(const string& ip) {
    unsigned int total = 0;
    string part;
    vector<int> ipv;
    stringstream ips(ip);

    while (getline(ips, part, '.')) {
        if (part.empty()) continue; // Skip empty parts caused by trailing dots

        try {
            int octet = stoi(part);
            if (octet < 0 || octet > 255) {
                cerr << "Invalid octet in IP: " << ip << ". Each octet should be between 0 and 255 inclusive." << endl;
                return -1; // or some other sentinel value indicating error
            }
            ipv.push_back(octet);
        } catch (const invalid_argument& ia) {
            cerr << "Invalid IP: " << ip << ". Each octet should be a valid integer." << endl;
            return -1;
        } catch (const out_of_range& oor) {
            cerr << "Invalid IP: " << ip << ". Each octet should be between 0 and 255 inclusive." << endl;
            return -1;
        }
    }

    if (ipv.size() != 4) {
        cerr << "Invalid IP: " << ip << ". Not enough valid octets." << endl;
        return -1;
    }

    total = ipv[3] | (ipv[2] << 8) | (ipv[1] << 16) | (ipv[0] << 24);
    return total;
}


void readfiles(LinkedList& lista){
    string mes, dia, hora, ip, puerto, status, line;
    ifstream archivo;
    archivo.open("bitacora.txt");
    if (archivo.is_open()){
        while(getline(archivo, line)){
        istringstream iss(line);
        if (line[5]==' ') {
            line.insert(4, "0");
            
        }
        iss>>mes>>dia>>hora>>ip;
        int puertopos=ip.find(":");
        puerto=ip.substr(puertopos+1);
        ip=ip.substr(0,puertopos);
        getline(iss,status);
            lista.insertion(mes,dia,hora,ip,puerto,status);
        }
    }
    archivo.close();
}
void LinkedList::printList(){
    Node* temp = Front;
    if (Front == NULL) {
        cout << "List empty" << endl;
        return;
    }
    cout<<"La cola es: "<<endl;
    while (temp != NULL) {
        temp->data->mdatos();
        cout<<endl;
        temp = temp->next;
    }
    cout<<endl;
}
time_t toUnixTimestamp(string dia, string mes, string hora) {
    std::map<std::string, int> monthMap = {{"Jan", 0}, {"Feb", 1}, {"Mar", 2}, {"Apr", 3},
                                           {"May", 4}, {"Jun", 5}, {"Jul", 6}, {"Aug", 7},
                                           {"Sep", 8}, {"Oct", 9}, {"Nov", 10}, {"Dec", 11}};

    struct tm timeStruct = {};
    timeStruct.tm_mday = std::stoi(dia);
    timeStruct.tm_mon = monthMap[mes];
    timeStruct.tm_year = 122; // For the year 2022
    timeStruct.tm_hour = std::stoi(hora.substr(0, 2));
    timeStruct.tm_min = std::stoi(hora.substr(3, 2));
    timeStruct.tm_sec = std::stoi(hora.substr(6, 2));

    return mktime(&timeStruct);
}

int searchByTimestamp(const LinkedList* lista, time_t keylow, time_t keyhigh, ofstream& archivo) {
    int contador = 0;
    Node* temp = lista->Front;
    while(temp != NULL) {
        time_t unix= toUnixTimestamp(temp->data->dia,temp->data->mes,temp->data->hora);
        if(unix >= keylow && unix <= keyhigh) {
            archivo << "Mes: " << temp->data->mes << ", Dia: " << temp->data->dia << ", Hora: " << temp->data->hora << ", IP: " << temp->data->ip << ", Puerto: " << temp->data->puerto << ", Status: " << temp->data->status << endl;
           
        }
        temp = temp->next;
    }
    return contador;
}

int searchByIp(LinkedList* lista, string iplow, string iphigh, ofstream& archivo) {
    int contador = 0;
    Node* temp = lista->Front;
    while(temp != NULL) {
        int ip_int = ipto_int(temp->data->ip);
        if(ip_int >= ipto_int(iplow) && ip_int <= ipto_int(iphigh)) {
            archivo << "Mes: " << temp->data->mes << ", Dia: " << temp->data->dia << ", Hora: " << temp->data->hora << ", IP: " << temp->data->ip << ", Puerto: " << temp->data->puerto << ", Status: " << temp->data->status << endl;
           
        }
        temp = temp->next;
    }
    return contador;
}
int searchByPort(LinkedList* lista, int portlow, int porthigh, ofstream& archivo) {
    int contador = 0;
    Node* temp = lista->Front;
    cout<<temp->data->puerto;
    while(temp != NULL) {
        int port_int = stoi(temp->data->puerto);
        if(port_int >= portlow && port_int <= porthigh) {
            archivo << "Mes: " << temp->data->mes << ", Dia: " << temp->data->dia << ", Hora: " << temp->data->hora << ", IP: " << temp->data->ip << ", Puerto: " << temp->data->puerto << ", Status: " << temp->data->status << endl;
            contador++;
        }
        temp = temp->next;
    }
    return contador;
}
void buscar(LinkedList* lista, int tipobusqueda) {
    time_t keylow = 0, keyhigh = 0;
    string iplow, iphigh;
    int portlow = 0, porthigh = 0;
    
    ofstream archivo(GetCurrentTimestamp() + "_Search.txt");
    
    switch(tipobusqueda) {
        case 1: { // Search by date
            // Create a map to convert numeric month to string representation.
            std::map<int, std::string> monthMapStr = {
                {1, "Jan"}, {2, "Feb"}, {3, "Mar"}, {4, "Apr"},
                {5, "May"}, {6, "Jun"}, {7, "Jul"}, {8, "Aug"},
                {9, "Sep"}, {10, "Oct"}, {11, "Nov"}, {12, "Dec"}
            };

            int mesiNum, mesfNum;
            std::string diai, diaf, mesi, mesf;

            cout << "Dame el dia inicial (1-31): ";
            cin >> diai;

            cout << "Dame el mes inicial (1-12): ";
            cin >> mesiNum;
            mesi = monthMapStr[mesiNum]; // Convert to string representation.

            cout << "Dame el dia final (1-31): ";
            cin >> diaf;

            cout << "Dame el mes final (1-12): ";
            cin >> mesfNum;
            mesf = monthMapStr[mesfNum]; // Convert to string representation.

            keylow = toUnixTimestamp(diai, mesi, "00:00:00");
            keyhigh = toUnixTimestamp(diaf, mesf, "00:00:00");
            int contador = searchByTimestamp(lista, keylow, keyhigh, archivo);
            cout << "Se retornaron: " << contador << " lineas" << endl;
            break;
        }
        case 2: { // Search by IP
            cout << "Dame el rango de ip inicial" << endl;
            cin >> iplow;
            cout << "Dame el rango de ip final" << endl;
            cin >> iphigh;
            int contador = searchByIp(lista, iplow, iphigh, archivo);
            cout << "Se retornaron: " << contador << " lineas" << endl;
            break;
        }
        case 3: { // Search by port
            cout << "Dame el rango de puertos inicial" << endl;
            cin >> portlow;
            cout << "Dame el rango de puertos final" << endl;
            cin >> porthigh;
            int contador = searchByPort(lista, portlow, porthigh, archivo);
            cout << "Se retornaron: " << contador << " lineas" << endl;
            break;
        }
        default: {
            cout << "Invalido!" << endl;
            return;
        }
    }
    
    archivo.close();
}

class NodeBST{
    public:
    NodeBST* left;
    NodeBST* right;
    int data;
    string port;
    NodeBST* prev;

    NodeBST(){}
    NodeBST(string port,int data,NodeBST* prev){this->left=NULL; this->right=NULL; this->data=data; this->prev=prev; this->port=port;}
};


class BinarySearchTree{

    NodeBST* root;
    public:
    BinarySearchTree(){this->root=nullptr;};
    void PreOrder(NodeBST* root);
    void InOrder();
    void InOrder(NodeBST* root);
    void PostOrder(NodeBST* root);
    void PostOrder();
    void Insertion(string puerto, int concurrences);
    int height(NodeBST* node);
    NodeBST* getroot(){return this->root;};
    void ancestors(int key);
    int WhatLevelAmI(NodeBST* node, int key,int count);
    void PreOrder();
    int height();
    NodeBST* BinarySearch(NodeBST* node, int key);
    int WhatLevelAmI(int key);
    NodeBST* Insertion(NodeBST* root, string puerto, int concurrences);
};

NodeBST* BinarySearchTree::Insertion(NodeBST* root, string puerto, int concurrences){
    if (root == nullptr) {
        root = new NodeBST(puerto,concurrences,nullptr);
        return root;
    }
    if(concurrences <= root->data){
        root->left = (root->left==nullptr) ? new NodeBST(puerto,concurrences,root) : Insertion(root->left, puerto, concurrences);
        cout<<"insertado";
    }
    else{
        root->right = (root->right==nullptr) ? new NodeBST(puerto,concurrences,root) : Insertion(root->right, puerto, concurrences);
         cout<<"insertado";
    }
    return root;
}

void BinarySearchTree::Insertion(string puerto, int concurrences){
    Insertion(this->root,puerto,concurrences);
}

void ConcurredPorts(LinkedList &lista) {
    BinarySearchTree bst;
    unordered_map<string, int> concurrences;
    Node* temp = lista.Front;
    while (temp != NULL) {
        if (concurrences.count(temp->data->puerto) == 1) {
            concurrences[temp->data->puerto] += 1;
        } else {
            concurrences[temp->data->puerto] = 1;
        }
        temp = temp->next;
    }
    for (const auto i : concurrences) {
        cout << "Puerto: " << i.first << " Numero de veces visto: " << i.second << endl;
        bst.Insertion(i.first,i.second);
    }
    bst.PreOrder(bst.getroot());

}
void BinarySearchTree::PreOrder(NodeBST* root){
    if (root==NULL){
        return;
    }
    cout<<root->port<<" ";
    PreOrder(root->left);
    PreOrder(root->right);

}
void BinarySearchTree::PreOrder(){
    PreOrder(this->root);
}



int main(){ 
LinkedList lista;
readfiles(lista);
lista.performMergeSort();
ConcurredPorts(lista);
cout<<"\nHola, que deseas hacer?"<<endl<<"Buscar en el archivo por\n1.Fechas\n2.Ips\n3.Puertos de IP\n4.Mostrar los 5 puertos mas concurridos\n5.Salir\n";
int seleccion;
cin>>seleccion;
switch(seleccion){
    while(seleccion!=4){
        case(1):
            buscar(&lista, 1);
            break;
        case(2):
            buscar(&lista, 2);
            break; 
        case(3):
            buscar(&lista, 3);
            break;
    }
}
    

}