#include "LidarDriver.h"
#include <iostream>
#include <vector>

LidarDriver::LidarDriver(double res) : resolution(res)
{
	matrix = std::vector<std::vector<double>>();
}

void LidarDriver::new_scan(std::vector<double> array)
{
	array = check_array(array);
	if (matrix.size() == BUFFER_DIM)
	{
		for (int i = 0; i < BUFFER_DIM - 1; i++)
		{
			matrix[i] = matrix[i + 1];
		}
		matrix[matrix.size() - 1] = array;
	}
	else
	{
		matrix.push_back(array);
	}
}

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

int LidarDriver::get_element_number()
{
	return (DEGREES / resolution) + 1;
}

std::vector<double> LidarDriver::get_scan()
{
	if (matrix.size() == 0)
	{
		// soluzione migliore sarebbe un'eccezione
		return std::vector<double>();
	}

	std::vector<double> last_scan = matrix[0];
	for (int i = 0; i < matrix.size() - 1; ++i)
	{
		matrix[i] = matrix[i + 1];
	}
	matrix.pop_back();

	return last_scan;
}

void LidarDriver::clear_buffer()
{
	matrix = std::vector<std::vector<double>>();
}

double LidarDriver::get_distance(double angle)
{
	if (matrix.size() == 0)
	{
		// soluzione migliore sarebbe un'eccezione
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
	if (angle - left*resolution <= right*resolution - angle) 
	// ho dovuto rimuovere gli abs perche' troncavano tutto a int e 
	// quindi non funzionavano. Non dovrebbero esserci problemi
	// perche' left*resolution e' sempre <= angle, mentre right*resolution e' sempre >= angle
	// sapendo che angle appartiene a [0, 180]
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