#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

// Función para leer los datos del archivo y almacenarlos en un vector
void readfiles(vector<string>& data){
    string line;
    ifstream archivo;
    archivo.open("bitacora.txt");
    if (archivo.is_open()){
        while(getline(archivo, line)){
        if (line[5]==' ') {
            line.insert(4, "0");
            
        } 
            data.push_back(line);
        
        }
    }
    archivo.close(); // Cierra el archivo después de leerlo
}

// Algoritmo de ordenamiento por inserción
void insertionSort(vector<string>& array) {
    for (int j = 1; j < array.size(); j++) {
        string key = array[j];
        int i = j - 1;

        while (i >= 0 && array[i].substr(0, 15) > key.substr(0, 15)) {
            array[i + 1] = array[i];
            i = i - 1;
        }

        array[i + 1] = key;
    }
}

// Función para combinar dos subarrays ordenados en el algoritmo de ordenamiento merge sort
void merge(vector<string>& array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<string> leftArray(n1);
    vector<string> rightArray(n2);

    // Copia elementos a subarrays temporales
    for (int i = 0; i < n1; i++) {
        leftArray[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = array[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].substr(0, 15) < rightArray[j].substr(0, 15)) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copia los elementos restantes si es necesario
    while (i < n1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < n2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }
}

// Función auxiliar para ordenar un rango del vector en el algoritmo de ordenamiento merge sort
void ordenaMergeHelper(vector<string>& array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordena recursivamente las mitades izquierda y derecha
        ordenaMergeHelper(array, left, mid);
        ordenaMergeHelper(array, mid + 1, right);

        // Combina las mitades ordenadas
        merge(array, left, mid, right);
    }
}

// Función principal de ordenamiento merge sort
void ordenaMerge(vector<string>& array) {
    int n = array.size();
    ordenaMergeHelper(array, 0, n - 1);
}

// Función para imprimir el contenido del vector
void printarr(vector<string>& array){
    for (int i = 0; i < array.size(); i++) {
        cout << array[i] << endl;
    }
    cout << endl;
}

// Función para obtener la marca de tiempo actual en formato de cadena
string GetCurrentTimestamp() {
    auto currentTime = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(currentTime);
    ostringstream oss;
    oss << put_time(localtime(&time), "%Y-%m-%d_%H-%M-%S");
    return oss.str();
}

// Función para realizar una búsqueda lineal en el vector y escribir los resultados en un archivo
int busqLineal(const vector<string>& array, string keylow, string keyhigh, ofstream& archivo){
    int contador = 0;
    for (int i = 0; i < array.size(); i++) {
        if (array[i].substr(0,15) < keylow && array[i].substr(0,15) > keyhigh) {
            archivo << array[i] << endl;
            contador++;
        }
    }
    return contador;
}

// Función para buscar datos en un rango específico y guardar los resultados en un archivo
int buscarDatos(string keyhigh, string keylow, const vector<string>& array){
    ofstream archivo(GetCurrentTimestamp() + "_Search.txt");
    int contador = busqLineal(array, keylow, keyhigh, archivo);
    archivo.close();
    return contador;
}

// Función para convertir un número de mes a su representación en cadena
string monthToString(int month) {
    const char* months[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};

    if (month >= 1 && month <= 12) {
        return months[month - 1];
    } else {
        return "Mes Inválido";
    }
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

void buscar_mes(){
    string diai, diaf;
    int mesi, mesf;
    vector<string> datos;
    readfiles(datos);
    ordenaMerge(datos);
    cout << "Dame el dia inicial (1-31): ";
    cin >> diai;
    cout << "Dame el mes (1-12): ";
    cin >> mesi;
    cout << "Dame el dia final (1-31): ";
    cin >> diaf;
    cout << "Dame el mes final (1-12): ";
    cin >> mesf;

if (diai == "1" || diai == "2" || diai == "3") {
    diai = "0" + diai;
}

if (diaf == "1" || diaf == "2" || diaf == "3") {
    diaf = "0" + diaf;
}

    int contador = buscarDatos(monthToString(mesi) + " " + diai, monthToString(mesf) + " " + diaf, datos);
    cout << "Se retornaron: " << contador << " lineas" << endl;
    cout << "Presiona Enter para salir.";
    cin.ignore(); // Ignora cualquier carácter de nueva línea previo
    cin.get();    // Espera la pulsación de la tecla Enter
}

void buscar_IP(){
    string ipinicial, ipfinal;
    vector<string> datos;
    readfiles(datos);
}

int main(){
cout<<"Hola, que deseas hacer?"<<endl<<"Buscar en el archivo por\n1.Fechas\n 2.Ips\n 3.Puertos de IP\n4.Salir";
int seleccion;
cin>>seleccion;
switch(seleccion){
    while(seleccion!=4){
        case(1):
            buscar_mes();
            break;
        case(2):

    }
}
    
    return 0; // Salida exitosa
}