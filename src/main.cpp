#include <iostream>
#include "LidarDriver.h"

int main() {
    // Inizializza il driver con una risoluzione di 1 grado
    LidarDriver driver(1.0);

    // Crea alcune scansioni di prova utilizzando il costruttore del vettore
    std::vector<double> scan1;
    scan1.push_back(1.0);
    scan1.push_back(2.0);
    scan1.push_back(3.0);
    scan1.push_back(4.0);
    scan1.push_back(5.0);

    std::vector<double> scan2;
    scan2.push_back(6.0);
    scan2.push_back(7.0);
    scan2.push_back(8.0);
    scan2.push_back(9.0);
    scan2.push_back(10.0);

    std::vector<double> scan3;
    scan3.push_back(11.0);
    scan3.push_back(12.0);
    scan3.push_back(13.0);
    scan3.push_back(14.0);
    scan3.push_back(15.0);

    // Aggiungi le scansioni al buffer
    driver.new_scan(scan1);
    driver.new_scan(scan2);
    driver.new_scan(scan3);

    // Stampa lo stato attuale del buffer
    std::cout << driver;

    // Test della funzione get_distance con un angolo specifico
    double angle = 2.0; // Angolo in gradi
    double distance = driver.get_distance(angle);
    std::cout << "Distanza all'angolo " << angle << ": " << distance << std::endl;

    // Ottieni e stampa la scansione più vecchia
    std::vector<double> oldest_scan = driver.get_scan();
    std::cout << "Scansione più vecchia rimossa dal buffer: ";
    for (double d : oldest_scan) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    // Pulisce il buffer e verifica
    driver.clear_buffer();
    std::cout << "Buffer dopo la pulizia: " << driver;

    return 0;
}