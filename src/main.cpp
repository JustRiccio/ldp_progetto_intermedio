#include "include/LidarDriver.h"
#include <iostream>
#include <vector>

int main()
{
    LidarDriver a;

    // Simula una lettura del Lidar
    std::vector<double> lettura;
    for (int i = 0; i < 10; i++) { // Simula 10 letture
        lettura.push_back(i * 1.5);
    }

    // Nuova scansione
    a.new_scan(lettura);

    // Ottiene la scansione più vecchia e la stampa
    std::vector<double> vecchia_scansione = a.get_scan();
    std::cout << "Scansione più vecchia:\n";
    for (double valore : vecchia_scansione) {
        std::cout << valore << " ";
    }
    std::cout << "\n";

    // Svuota il buffer
    a.clear_buffer();

    return 0;
}