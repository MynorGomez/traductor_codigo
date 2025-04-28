#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <locale>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// Estructura para representar una palabra
struct Palabra {
    string palabra;
    string traduccion;
    string funcionalidad;
};

// Función para verificar si un archivo existe
bool archivo_existe(const string& archivo_nombre) {
    ifstream archivo(archivo_nombre);
    return archivo.is_open();
}

// Función para inicializar las palabras iniciales
vector<Palabra> palabras_iniciales() {
    return {
        {"asm", "ensamblador", "inserta código ensamblador en C++"},
        {"auto", "automático", "deduce automáticamente el tipo de una variable"},
        {"bool", "booleano", "tipo de dato verdadero/falso"},
        {"break", "romper", "termina un bucle o switch"},
        {"case", "caso", "define un caso en un switch"}
    };
}

// Función para eliminar espacios adicionales al principio y al final de una cadena
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Función para guardar las palabras en un archivo con formato de tabla
void guardar(const string& archivo_nombre, const vector<Palabra>& palabras) {
    ofstream archivo(archivo_nombre);
    if (!archivo) {
        cerr << "Error al abrir el archivo para guardar: " << archivo_nombre << endl;
        return;
    }

    // Escribir encabezados
    archivo << left << setw(20) << "Palabra" << " | "
            << setw(20) << "Traducción" << " | "
            << setw(40) << "Funcionalidad" << endl;
    archivo << string(85, '-') << endl;

    // Escribir palabras
    for (const auto& palabra : palabras) {
        archivo << left << setw(20) << palabra.palabra << " | "
                << setw(20) << palabra.traduccion << " | "
                << setw(40) << palabra.funcionalidad << endl;
    }

    archivo.close();
}

// Función para cargar las palabras desde un archivo con delimitadores "|"
vector<Palabra> cargar(const string& archivo_nombre) {
    vector<Palabra> palabras;
    ifstream archivo(archivo_nombre);
    if (!archivo) {
        cerr << "Error al abrir el archivo para cargar: " << archivo_nombre << endl;
        return palabras;
    }

    string linea;
    bool es_encabezado = true; // Ignorar la primera línea (encabezados)
    while (getline(archivo, linea)) {
        if (es_encabezado || linea.find('-') != string::npos) {
            es_encabezado = false;
            continue;
        }

        stringstream ss(linea);
        string palabra, traduccion, funcionalidad;

        getline(ss, palabra, '|');
        getline(ss, traduccion, '|');
        getline(ss, funcionalidad, '|');

        // Eliminar espacios adicionales alrededor de los campos
        palabra = trim(palabra);
        traduccion = trim(traduccion);
        funcionalidad = trim(funcionalidad);

        if (!palabra.empty() && !traduccion.empty() && !funcionalidad.empty()) {
            palabras.push_back({palabra, traduccion, funcionalidad});
        }
    }

    archivo.close();
    return palabras;
}

// Función para mostrar las palabras en formato de tabla
void mostrar(const vector<Palabra>& palabras) {
    cout << left << setw(20) << "Palabra" 
         << setw(20) << "Traducción" 
         << setw(40) << "Funcionalidad" << endl;
    cout << string(85, '-') << endl;

    for (const auto& palabra : palabras) {
        cout << left << setw(20) << palabra.palabra 
             << setw(20) << palabra.traduccion 
             << setw(40) << palabra.funcionalidad << endl;
    }
}

// Función para agregar una nueva palabra
void agregar(const string& archivo_nombre, vector<Palabra>& palabras) {
    string palabra, traduccion, funcionalidad;
    cout << "Ingrese la palabra: ";
    cin >> palabra;
    palabra = trim(palabra); // Eliminar espacios adicionales

    // Verificar si la palabra ya existe
    auto it = find_if(palabras.begin(), palabras.end(), [&](const Palabra& p) {
        return p.palabra == palabra;
    });

    if (it != palabras.end()) {
        cout << "La palabra ya existe en el diccionario." << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "Ingrese la traducción: ";
    cin >> traduccion;
    traduccion = trim(traduccion); // Eliminar espacios adicionales
    cin.ignore();
    cout << "Ingrese la funcionalidad: ";
    getline(cin, funcionalidad);
    funcionalidad = trim(funcionalidad); // Eliminar espacios adicionales

    palabras.push_back({palabra, traduccion, funcionalidad});
    guardar(archivo_nombre, palabras);

    // Mostrar la palabra recién agregada en formato de tabla
    cout << "\nPalabra agregada correctamente:\n";
    cout << left << setw(20) << "Palabra"
         << setw(20) << "Traducción"
         << setw(40) << "Funcionalidad" << endl;
    cout << string(85, '-') << endl;
    cout << left << setw(20) << palabra
         << setw(20) << traduccion
         << setw(40) << funcionalidad << endl;

    system("pause");
    system("cls");
}

// Función para actualizar una palabra existente
void actualizar(const string& archivo_nombre, vector<Palabra>& palabras) {
    string palabra;
    cout << "Ingrese la palabra a actualizar: ";
    cin >> palabra;
    palabra = trim(palabra); // Eliminar espacios adicionales

    for (auto& p : palabras) {
        if (p.palabra == palabra) {
            cout << "Ingrese la nueva traducción: ";
            cin >> p.traduccion;
            p.traduccion = trim(p.traduccion); // Eliminar espacios adicionales
            cin.ignore();
            cout << "Ingrese la nueva funcionalidad: ";
            getline(cin, p.funcionalidad);
            p.funcionalidad = trim(p.funcionalidad); // Eliminar espacios adicionales

            guardar(archivo_nombre, palabras);
            cout << "Palabra actualizada correctamente." << endl;
            return;
        }
    }

    cout << "Palabra no encontrada." << endl;
}

// Función para eliminar una palabra
void eliminar(const string& archivo_nombre, vector<Palabra>& palabras) {
    string palabra;
    cout << "Ingrese la palabra a eliminar: ";
    cin >> palabra;
    palabra = trim(palabra); // Eliminar espacios adicionales

    auto it = remove_if(palabras.begin(), palabras.end(), [&](const Palabra& p) {
        return p.palabra == palabra;
    });

    if (it != palabras.end()) {
        palabras.erase(it, palabras.end());
        guardar(archivo_nombre, palabras);
        cout << "Palabra eliminada correctamente." << endl;
    } else {
        cout << "Palabra no encontrada." << endl;
    }
}

// Función principal
void diccionario() {
    system("cls"); // Limpiar la consola al iniciar
    // Configurar la consola para UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    locale::global(locale(""));

    string archivo_nombre = "palabras.txt";

    // Inicializar el archivo con palabras iniciales si no existe
    if (!archivo_existe(archivo_nombre)) {
        guardar(archivo_nombre, palabras_iniciales());
    }

    vector<Palabra> palabras = cargar(archivo_nombre);

    int opcion;
    do {
        cout << "\n--- CRUD de Palabras ---" << endl;
        cout << "1. Mostrar palabras" << endl;
        cout << "2. Agregar palabra" << endl;
        cout << "3. Actualizar palabra" << endl;
        cout << "4. Eliminar palabra" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";

        // Validar entrada no numérica
        if (!(cin >> opcion)) {
            cin.clear(); // Limpiar el estado de error
            cin.ignore(1000, '\n'); // Ignorar el resto de la línea
            cout << "Por favor, ingrese un número válido.\n";
            system("pause");
            system("cls");
            continue;
        }

        switch (opcion) {
            case 1:
                mostrar(palabras);
                break;
            case 2:
                agregar(archivo_nombre, palabras);
                break;
            case 3:
                actualizar(archivo_nombre, palabras);
                break;
            case 4:
                eliminar(archivo_nombre, palabras);
                break;
            case 5:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, seleccione una opción del menú.\n";
        }
    } while (opcion != 5);
    system("pause");
    system("cls");
}