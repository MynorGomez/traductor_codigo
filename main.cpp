/*	
*	Tarea grupal del curso Programación I
*	
*	Universidad Mariano Gálvez de Guatemala
*	Facultad de Ingeniería en Sistemas
*	
*	Autores:
*	Josseline Adriana Catalán Juárez
*	José David Mazariegos Ortega
*	Mynor Alexander Gómez Pedro
*	Erick Manuel Fuentes Miranda
*	Francisco Antonio De León Natareno
*/
#include "traductor.cpp"
#include "diccionario.cpp"
#include <iostream>
#include <locale>
#ifdef _WIN32
#include <windows.h> // Para configurar la consola en Windows
#endif
using namespace std;

int main() {
    system("color 0A"); // Cambiar el color de la consola
    // Configurar la consola para UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Configurar salida en UTF-8
    SetConsoleCP(CP_UTF8);       // Configurar entrada en UTF-8
#endif
    locale::global(locale("")); // Configurar localización global

    int opcion;

    do {
        // Menú principal
        cout << "==========================================\n";
        cout << "|           --- MENU PRINCIPAL ---       |\n";
        cout << "==========================================\n";
        cout << "1 - Gestionar Diccionario (CRUD)\n";
        cout << "2 - Traducir Código C++\n";
        cout << "3 - Salir\n";
        cout << "==========================================\n";
        cout << "Selecciona una opción: ";
        cin >> opcion;

        // Validar entrada no numérica
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Por favor, ingresa un número válido.\n";
            system("pause");
            system("cls");   
        
            continue;
        }

        // Switch para manejar las opciones
        switch (opcion) {
            case 1:
                cout << "\n=== GESTIONAR DICCIONARIO ===\n";
                // Llamar a la función que encapsula el diccionario
                diccionario();
                break;

            case 2:
                cout << "\n=== TRADUCIR CÓDIGO C++ ===\n";
                // Llamar a la función que encapsula el traductor
                traductor();
                system("cls");
                break;

            case 3:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción no válida. Por favor, selecciona una opción del menú.\n";
                break;
        }
        system("cls"); // Limpiar la consola después de cada opción
        cout << endl;
    } while (opcion != 3);

    return 0;
}