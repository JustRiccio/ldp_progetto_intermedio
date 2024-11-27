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
	int element_number = get_element_number();
	if (array.size() > element_number)
	{
		std::vector<double> tmp(element_number);
		for (int i = 0; i < element_number; i++)
		{
			tmp[i] = array[i];
		}
		return tmp;
	}
	else if (array.size() < element_number)
	{
		std::vector<double> tmp(element_number);
		for (int i = 0; i < array.size(); i++)
		{
			tmp[i] = array[i];
		}
		for (int j = array.size(); j < element_number; j++)
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
	return (DEGREES / resolution) + 1;
}

// Ritorna l'ultima scansione effetuata e la rimuove dal buffer
std::vector<double> LidarDriver::get_scan()
{
    if (matrix.empty())
    {
		//Aggiungere eccezione
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

//Dato un angolo, restituisce la misura corrispondente a tale angolo nell'ultima scansione
//nel caso non sia presente l'angolo cercato, si prende il valore piu' vicino 
double LidarDriver::get_distance(double angle)
{
	if (matrix.size() == 0){
		//Aggiungere eccezione
		return 0;
	}
	std::vector<double> tmp = matrix[matrix.size() - 1];
	int i = 0;
	// nel caso non sia presente l'angolo cercato prendo i due valori attorno al valore cercato
	int left = 0;
	int right = 1;
	while (i * resolution <= angle && i < tmp.size() - 1)
	{
		left = i;
		right = i + 1;
		i++;
	}

	// se right e left sono uguali(non dovrebbe succedere)
	// if (abs(left*resolution - angle) <= abs(right*resolution - angle))
	// Ho dovuto rimuovere gli abs perche' troncavano tutto a int e 
	// quindi non funzionavano. Non dovrebbero esserci problemi di termini < 0
	// perche' left*resolution e' sempre <= angle, mentre right*resolution e' sempre >= angle
	// avendo angle appartenente a [0, 180]
	if (angle - left*resolution <= right*resolution - angle) 
	{
		return tmp[left];
	}
	else
	{
		return tmp[right];
	}
}

std::ostream &operator<<(std::ostream &stream, const LidarDriver &ld)
{
	if (ld.matrix.size() == 0)
	{
		stream << "There are no saved scans" << std::endl;
	}
	else
	{
		stream << "Last scan: ";
		for (double value : ld.matrix[ld.matrix.size() - 1])
		{
			stream << value << " ";
		}
		stream << std::endl;
	}
	return stream;
}