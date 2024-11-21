#include "LidarDriver.h"
#include <iostream>
#include <vector>

LidarDriver::LidarDriver()
{
	std::vector<std::vector<double>> matrix = std::vector<std::vector<double>>(BUFFER_DIM);
}

void new_scan(std::vector<double> array)
{
	array = check_array(array);
	
	if (matrix.size() == LidarDriver::BUFFER_DIM)
	{
		for(int i = 0; i < BUFFER_DIM-1; i++)
		{
			matrix[i] = matrix[i+1];
		}
	}
	matrix.push_back(array);
}

std::vector<double> check_array(std::vector<double> array)
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
		
	}
	else
	{
		return array;
	}
}

int get_element_number()
{
	return (180/resolution)+1;
}

std::vector<double> get_scan()
{
	
}
