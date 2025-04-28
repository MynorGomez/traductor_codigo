#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <locale>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// Función para cargar el diccionario desde el archivo
unordered_map<string, string> cargar_diccionario(const string& archivo_nombre) {
    unordered_map<string, string> diccionario;
    ifstream archivo(archivo_nombre);
    if (!archivo) {
        cerr << "Error al abrir el archivo para cargar el diccionario: " << archivo_nombre << endl;
        return diccionario;
    }

    string linea;
    bool es_encabezado = true; // Ignorar encabezados
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

        // Eliminar espacios adicionales
        palabra = palabra.substr(0, palabra.find_last_not_of(" ") + 1);
        traduccion = traduccion.substr(0, traduccion.find_last_not_of(" ") + 1);

        diccionario[palabra] = traduccion;
    }

    archivo.close();
    return diccionario;
}

// Función para traducir el texto multilínea
void traducir_codigo(const unordered_map<string, string>& diccionario) {
    cout << "Ingrese el código C++ a traducir (finalice con una línea vacía):" << endl;

    string linea;
    vector<string> codigo_original;

    // Ignorar el primer salto de línea
    cin.ignore();

    while (getline(cin, linea) && !linea.empty()) {
        codigo_original.push_back(linea);
    }

    cout << "\nCódigo traducido:\n" << endl;

    bool es_funcion = false; // Bandera para identificar si estamos dentro de una función

    for (const auto& linea : codigo_original) {
        stringstream ss(linea);
        string palabra;

        while (ss >> palabra) {
            // Detectar funciones (si hay paréntesis al final)
            if (palabra.find("()") != string::npos) {
                es_funcion = true;
            }

            // Traducir palabras clave
            if (diccionario.find(palabra) != diccionario.end()) {
                cout << diccionario.at(palabra) << " ";
            } else if (palabra == "{") {
                if (es_funcion) {
                    cout << "{ ";
                } else {
                    cout << "inicio ";
                }
            } else if (palabra == "}") {
                if (es_funcion) {
                    cout << "} ";
                    es_funcion = false; // Salimos de la función
                } else {
                    cout << "fin ";
                }
            } else {
                cout << palabra << " ";
            }
        }
        cout << endl;
    }
}

// Función principal
void traductor() {
    system("cls"); // Limpiar la consola al iniciar
    // Configurar la consola para UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    locale::global(locale(""));

    string archivo_nombre = "palabras.txt";

    // Cargar el diccionario desde el archivo
    unordered_map<string, string> diccionario = cargar_diccionario(archivo_nombre);

    if (diccionario.empty()) {
        cerr << "El diccionario está vacío. Verifique el archivo." << endl;
        return;
    }

    char opcion;
    do {
        // Traducir el código ingresado por el usuario
        traducir_codigo(diccionario);

        cout << "\n¿Desea traducir otro código? (s/n): ";
        cin >> opcion;
        opcion = tolower(opcion); // Convertir a minúscula para evitar problemas con mayúsculas
        cin.ignore(); // Ignorar el salto de línea después de la entrada
    } while (opcion == 's');

    cout << "Saliendo del traductor...\n";
}