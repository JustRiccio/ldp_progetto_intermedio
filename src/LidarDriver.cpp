#include "LidarDriver.h"
#include <iostream>
#include <vector>

LidarDriver::LidarDriver()
{
	std::vector<std::vector<double>> matrix = std::vector<std::vector<double>>(BUFFER_DIM);
}

void LidarDriver::new_scan(std::vector<double> array)
{
	array = check_array(array);
	
	if (matrix.size() == BUFFER_DIM)
	{
		for(int i = 0; i < BUFFER_DIM-1; i++)
		{
			matrix[i] = matrix[i+1];
		}
	}
	matrix.push_back(array);
}

std::vector<double> LidarDriver::check_array(std::vector<double> array)
{
	if(array.size() > get_element_number())
	{
		std::vector<double> tmp = std::vector<double>(get_element_number());
		for(int i = 0; i < get_element_number(); i++)
		{
			tmp[i] = array[i];
		}
		return tmp;
	}
	else if(array.size() < get_element_number())
	{
		std::vector<double> tmp = std::vector<double>(get_element_number());
		for(int i = 0; i < array.size() ; i++){
			tmp[i] = array[i];
		}
		for(int j = array.size() ; j < get_element_number(); j++)
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
	return (180/resolution)+1;
}

std::vector<double> LidarDriver::get_scan()
{
	//ritorna la scansione piu' vecchia e la rimuove dal buffer
	std::vector<std::vector<double>> tmp = std::vector<std::vector<double>>(BUFFER_DIM);
	std::vector<double> tmp = matrix[0];
	for(int i = 0; i < cont; i++)
	{
		tmp[i] = matrix[i];
	}
	for(int i = 0; i < cont-1; i++)
	{
		matrix[i] = tmp[i+1];
	}
}

void LidarDriver::clear_buffer()
{
	//elimina tutte le scansioni senza ritornarle
	//uguale al costruttore, forse da modificare il delete()
}

double LidarDriver::get_distance(double angle)
{
	if (cont == 0){
		std::cout<<"Buffer vuoto";	//volendo si potrebbe gestire anche con un'eccezzione
		return 0;
	}
	std::vector<double> tmp = matrix[cont];
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

/*friend std::ostream& operator<<(std::ostream& stream, const LidarDriver& ld)
{
	
}*/

