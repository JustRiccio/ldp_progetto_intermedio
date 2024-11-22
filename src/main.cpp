#include "LidarDriver.h";
#include <iostream>
#include <vector>

int main()
{
	LidarDriver::LidarDriver a = new LidarDriver::LidarDriver();
	
	std::vector<double> lettura = std::vector<double>();
	for(int i = 0; i < 3 ; i++)
	{
		
	}
	a.new_scan(lettura);
	
	return 0;
}