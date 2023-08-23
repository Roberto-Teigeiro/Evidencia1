#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;


void readfiles(vector<string>& data){
    string line;
    ifstream archivo;
    archivo.open("bitacora.txt");
    if (archivo.is_open()){
        while(getline(archivo, line)){
            data.push_back(line);
        }
    }

}

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
        if (leftArray[i].substr(0, 15) <= rightArray[j].substr(0, 15)) {
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

void ordenaMerge(vector<string>& array) {
    int n = array.size();
    ordenaMergeHelper(array, 0, n - 1);
}


void printarr(vector<string>& array){
     for (int i = 0; i < array.size(); i++) {
        cout << array[i]<< endl;
    }
    cout<<endl;
}

string GetCurrentTimestamp() {
    auto currentTime = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(currentTime);
    ostringstream oss;
    oss << put_time(localtime(&time), "%Y-%m-%d_%H-%M-%S");
    return oss.str();
}


int busqLineal(const vector<string>& array,string keylow,string keyhigh, ofstream& archivo){
    int contador=0;
    for (int i = 0; i < array.size(); i++) {
        if (array[i].substr(0,15) < keylow && array[i].substr(0,15) > keyhigh) { 
            archivo << array[i] << endl;
            contador++;
        }
    }
    return contador;
}

int buscarDatos(string keyhigh, string keylow, const vector<string>& array){
   ofstream archivo(GetCurrentTimestamp()+ "_Search.txt");
   int contador = busqLineal(array, keylow, keyhigh, archivo);
    archivo.close();
    return contador;
}
string monthToString(int month) {
    const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    if (month >= 1 && month <= 12) {
        return months[month - 1];
    } else {
        return "Mes Invalido"; 
    }
}

int main(){
    string diai, diaf;
    int mesi, mesf;
    vector<string> datos;
    readfiles(datos);
    ordenaMerge(datos);
    cout<<"Dame el dia inicial (1-31)";
    cin>>diai;
    cout<<"Dame el mes (1-12)";
    cin>>mesi;
    cout<<"Dame el dia final (1-31)";
    cin>>diaf;
    cout<<"Dame el mes final(1-12)";
    cin>>mesf;
    int contador=buscarDatos(monthToString(mesi) + " " + diai, monthToString(mesf) + " " + diaf, datos);
    cout<<"se retornaron: "<<contador<< " lineas"<<endl<<"Presiona Enter para salir.";
    cin.get();

} 