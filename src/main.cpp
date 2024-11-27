#include "LidarDriver.h"
#include <iostream>
#include <vector>

// funzione da eliminare, serve solo a generare numeri random per simulare delle letture
/*
#include <random>
std::vector<double> test(int size){
    std::vector<double> output;


    // codice preso da stackoverflow 
    // https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c risposta migliore

    double lower_bound = 0;
    double upper_bound = 10;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;


    for (int i=0; i<size; i++){
        double random_n = unif(re);
        output.push_back(random_n);
    }

    return output;
}
*/

int main()
{
    LidarDriver a = LidarDriver(1);

    // Simula una lettura del Lidar
    //std::vector<double> lettura = test(a.get_element_number());
    std::vector<double> lettura;
    for (int i = 0; i < 11; i++) { // Simula lettura 10 gradi 
        lettura.push_back(i * 1.5);
    }

    // test del print << di un Lidar vuoto
    std::cout << a;

    // Nuova scansione
    a.new_scan(lettura);

    lettura.clear();
    for (int i = 0; i < 6; i++) { // Simula lettura 10 gradi 
        lettura.push_back(i * 1.3);
    }
    a.new_scan(lettura);

    lettura.clear();
    for (int i = 0; i < 15; i++) { // Simula lettura 10 gradi 
        lettura.push_back(i * 1.7);
    }
    a.new_scan(lettura);

    // test del print << di un Lidar
    std::cout << a;

    // Ottiene la scansione più vecchia e la stampa
    std::vector<double> vecchia_scansione = a.get_scan();
    std::cout << "Scansione piu' vecchia:\n";
    for (double valore : vecchia_scansione) {
        std::cout << valore << "  ";
    }
    std::cout << std::endl;

    // Svuota il buffer
    a.clear_buffer();

    std::vector<double> b = a.get_scan();
    std::cout << "Scansione piu' vecchia:\n";
    for (double valore : b) {
        std::cout << valore << "  ";
    }
    std::cout << std::endl;

    // test del print << di un Lidar vuoto dopo un buffer clear
    std::cout << a;

    return 0;
}