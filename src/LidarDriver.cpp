#include "LidarDriver.h"
#include <iostream>
#include <vector>

// Costruttore con inizialiazzione di default del vettore delle scansioni vuoto
LidarDriver::LidarDriver(double res) : resolution(res) {}

// Inserisce una nuova scansione in coda al vettore.
// In caso raggiunga la dimensione massima, viene eliminata la più vecchia, che si trova in testa,
// viene shiftato il vettore di una posizione e rimpiazzata la scansione in coda.
void LidarDriver::new_scan(const std::vector<double>& array)
{
    std::vector<double> checked_array = check_array(array);

    if (matrix.size() == BUFFER_DIM)
    {
        for (size_t i = 0; i < BUFFER_DIM - 1; i++)
        {
            matrix[i] = std::move(matrix[i + 1]);
        }
        matrix.pop_back();
    }
    matrix.push_back(checked_array);
}

// Esegue un controllo sul numero di letture che sono state fatte dal LidarDriver, ottenendo un vettore sempre con la stessa dimensione data dalla sensibilità
//  - Se il numero di letture è minore del previsto, il vettore viene completato con zeri.
//  - Se il numero di letture è maggiore, viene troncato fino ad ottenere la lunghezza corretta.
std::vector<double> LidarDriver::check_array(std::vector<double> array)
{
	if(array.size() > get_element_number())
	{
		std::vector<double> tmp(get_element_number());
		for(int i = 0; i < get_element_number(); i++)
		{
			tmp[i] = array[i];
		}
		return tmp;
	}
	else if(array.size() < get_element_number())
	{
		std::vector<double> tmp(get_element_number());
		for(int i = 0; i < array.size() ; i++){
			tmp[i] = array[i];
		}
		for(int j = array.size(); j < get_element_number(); j++)
		{
			tmp[j] = 0;
		}
		return tmp;
	}
	else
	{
		return array;
	}
}

// Restituisce il numero di letture per una scansione.
int LidarDriver::get_element_number() const
{
	return (DEGREES/resolution)+1;
}

// 
std::vector<double> LidarDriver::get_scan()
{
    if (matrix.empty())
    {
		std::cout << "Non sono presenti scansioni" << std::endl;
        return std::vector<double>();
    }

    std::vector<double> last_scan = std::move(matrix.front());
    // Rimuove la prima scansione e scala tutto
	matrix.erase(matrix.begin());

    return last_scan;
}

// Azzera il buffer del LidarDriver
void LidarDriver::clear_buffer()
{
	matrix.clear();
}

double LidarDriver::get_distance(double angle)
{
	if (matrix.size() == 0){
		std::cout << "Buffer vuoto";	//volendo si potrebbe gestire anche con un'eccezione
		return 0;
	}
	std::vector<double> tmp = matrix[matrix.size() - 1];
	int i = 0;
	//nel caso non sia presente l'angolo cercato prendo i due valori attorno al valore cercato
	int lsinistro=0;
	int ldestro=0;
	while(i*resolution <= angle || i < tmp.size()-1){
		lsinistro = i;
		ldestro = i + 1;
		i++;
	}	
	//se ldestro e lsinistro sono uguali(non dovrebbe succedere)
	if(abs(lsinistro - angle) <= abs(ldestro - angle)){ 
		return tmp[lsinistro];
	}
	else{
		return tmp[ldestro];
	}
}

std::ostream& operator<<(std::ostream& stream, const LidarDriver& ld)
{
	if (ld.matrix.empty())
    {
        return stream << "Non sono presenti scansioni salvate" << std::endl;
    }

    stream << "Ultima scansione:" << std::endl;
    for (double value : ld.matrix.back())
    {
        stream << value << " ";
    }
    stream << std::endl;

    return stream;
}