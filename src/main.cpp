#include "LidarDriver.h"
#include <iostream>
#include <vector>
#include <random>

std::vector<double> get_random_scan(int);
int get_choice();
void test();

int main()
{
    test();
    return 0;
}

// genera numeri random per simulare delle letture.
// codice preso da stackoverflow
// https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c top answer
// + chatGPT per generare il seed dato che quella parte di codice non funzionava
std::vector<double> get_random_scan(int size)
{
    std::random_device rd; // Use hardware entropy if available
    std::mt19937 gen(rd());
    std::vector<double> output;
    double lower_bound = 0;
    double upper_bound = 10;

    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);

    for (int i = 0; i < size; i++)
    {
        double random_n = unif(gen);
        output.push_back(random_n);
    }
    return output;
}

int get_choice()
{
    std::cout << "\n1-Instantiate a new Driver";
    std::cout << "\n2-Manual new scan";
    std::cout << "\n3-Automatic new scan";
    std::cout << "\n4-Get scan";
    std::cout << "\n5-Clear buffer";
    std::cout << "\n6-Get distance";
    std::cout << "\n7-Print last scan";
    std::cout << "\n0-Exit";
    std::cout << "\nWaiting for input";
    std::cout << std::endl;
    int choice;
    std::cin >> choice;
    return choice;
}

void test()
{
    LidarDriver ld = LidarDriver(1);
    int choice = -1;

    while (choice != 0)
    {
        choice = get_choice();
        switch (choice)
        {
        case 0:
        {
            std::cout << "Bye!" << std::endl;
            break;
        }
        case 1:
        {
            double resolution = 0;
            while (resolution <= 0 or resolution > 1)
            {
                std::cout << "Resolution? (real number in ]0, 1])" << std::endl;
                std::cin >> resolution;
            }

            // per il momento non funziona.
            // o si sistemano i costruttori o l'operatore =
            // oppure si impone la scelta della resolution all'inizio
            // e se uno vuole cambiare resolution deve riavviare il programma
            // ld = LidarDriver(resolution);
            break;
        }
        case 2:
        {
            std::vector<double> scan;
            std::cout << "Type values (type 0 to stop)" << std::endl;
            double value = 1;
            std::cin >> value;
            // siccome i valori sono inseriti da utente non c'e' bisogno di implementare
            // l'uguaglianza tra double come abs(a-b) <= epsilon
            while (int(value) != 0)
            {
                scan.push_back(value);
                std::cin >> value;
            }

            ld.new_scan(scan);
            break;
        }
        case 3:
        {
            ld.new_scan(get_random_scan(ld.get_element_number()));
            break;
        }
        case 4:
        {
            std::vector<double> scan = ld.get_scan();

            if (scan.size() == 0)
            {
                std::cout << "There are no saved scans" << std::endl;
            }
            else
            {
                for (double val : scan)
                {
                    std::cout << val << " ";
                }
                std::cout << std::endl;
            }
            break;
        }
        case 5:
        {
            ld.clear_buffer();
            break;
        }
        case 6:
        {
            double angle = -1;
            while (angle < 0 or angle > 180)
            {
                std::cout << "Angle? (real number in [0, 180])" << std::endl;
                std::cin >> angle;
            }
            double output = ld.get_distance(angle);
            if (output == 0){
                // sarebbe da effettuare un catch di un'eccezione qui
                std::cout << "There is no measure for that angle" << std::endl;
            }
            else{
                std::cout << "Distance measured: " << output << std::endl;
            }
            break;
        }
        case 7:
        {
            std::cout << ld;
            break;
        }

        default:
        {
            std::cout << "Invalid input" << std::endl;
            break;
        }
        }
    }
}

