#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
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
int ipto_int(string ip){
    unsigned int total;
    string part;
    vector<int> ipv;
    stringstream ips(ip);
     while (getline(ips, part, '.')) {
        ipv.push_back(stoi(part));
    }
    total= ipv[3] | (ipv[2] << 8) | (ipv[1] << 16) | (ipv[0] << 24);
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
        timeStruct.tm_year = /* You'll need the year here */ 122; // e.g., 120 represents the year 2020
        timeStruct.tm_hour = std::stoi(hora.substr(0, 2));
        timeStruct.tm_min = std::stoi(hora.substr(3, 2));
        timeStruct.tm_sec = std::stoi(hora.substr(6, 2));

        return mktime(&timeStruct);
    }
int busqLineal(LinkedList* lista, time_t keylow, time_t keyhigh, ofstream& archivo, int iplow, int iphigh, int portlow, int porthigh){ // Las variables low/high son utilizadas para comparar y escribir en el archivo
    int contador=0;
     Node* temp = lista->Front;
     while(temp!=NULL){
        if(temp->data->toUnixTimestamp() < keylow && temp->data->toUnixTimestamp() > keyhigh || (ipto_int(temp->data->ip) < iplow && ipto_int(temp->data->ip) > iplow ) || (stoi(temp->data->puerto) < portlow && stoi(temp->data->puerto) > portlow)) {
            archivo << "Mes: " << temp->data->mes << ", Dia: " << temp->data->dia << ", Hora: " << temp->data->hora << ", IP: " << temp->data->ip << ", Puerto: " << temp->data->puerto << ", Status: " << temp->data->status << endl;
            contador++;
        }
        temp = temp->next;
     }
    return contador;
}
// Función para buscar datos en un rango específico y guardar los resultados en un archivo
int buscarDatos(time_t keyhigh, time_t keylow, const LinkedList* lista, int tipobusqueda,int iplow, int iphigh, int portlow, int porthigh){
    ofstream archivo(GetCurrentTimestamp() + "_Search.txt");
    int contador = (tipobusqueda==1) ? (lista, keylow,keyhigh,archivo,NULL,NULL,NULL,NULL) : 
                    (tipobusqueda==2) ? (lista, NULL, NULL,archivo,iplow,iphigh,NULL,NULL):
                    (tipobusqueda==3) ?(lista, NULL, NULL,archivo,NULL,NULL,portlow,porthigh) :
                    0;
    archivo.close();
    return contador;
}
void buscar_mes(LinkedList* lista){
    string diai, mesi, diaf, mesf;
    cout << "Dame el dia inicial (1-31): "<<endl;
    cin >> diai;
    cout << "Dame el mes (1-12): "<<endl;
    cin >> mesi;
    cout << "Dame el dia final (1-31): "<<endl;
    cin >> diaf;
    cout << "Dame el mes final (1-12): "<<endl;
    cin >> mesf;

if (diai == "1" || diai == "2" || diai == "3") {
    diai = "0" + diai;
}

if (diaf == "1" || diaf == "2" || diaf == "3") {
    diaf = "0" + diaf;
}

    int contador = buscarDatos(toUnixTimestamp(diai,mesi,"00:00:00"),toUnixTimestamp(diaf,mesf,"00:00:00"), lista ,1,NULL,NULL,NULL,NULL);
    cout << "Se retornaron: " << contador << " lineas" << endl; 
}
void buscar_ip(LinkedList* lista){
    string ipi, ipf;
    cout<<"Dame el rango de ip inical"<<endl;
    cin>>ipi;
    cout<<"Dame el rango de ip final"<<endl;
    cin>>ipf;
    buscarDatos(NULL,NULL,lista,2,ipto_int(ipi),ipto_int(ipf),NULL,NULL);
}
void buscar_puerto(LinkedList* lista){
    int puertoi,puertof;
    cout<<"Dame el rango de puertos incial"<<endl;
    cin>>puertoi;
    cout<<"Dame el rango de puertos final"<<endl;
    buscarDatos(NULL,NULL,lista,3,NULL,NULL,puertoi,puertof);
}
int main(){
LinkedList lista;
readfiles(lista);
lista.performMergeSort();
cout<<"\nHola, que deseas hacer?"<<endl<<"Buscar en el archivo por\n1.Fechas\n 2.Ips\n 3.Puertos de IP\n4.Salir\n";
int seleccion;
cin>>seleccion;
switch(seleccion){
    while(seleccion!=4){
        case(1):
            buscar_mes(&lista);
            break;
        case(2):
            buscar_ip(&lista);
            break; 
        case(3):
            buscar_puerto(&lista);
            break;


    }
}
    

}