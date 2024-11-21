#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H 
#include <iostream>
#include <vector>

class LidarDriver
{
	private:
		std::vector<std::vector<double>> matrix;
		int cont;
		static constexpr int BUFFER_DIM = 10;
		int resolution;
		
	public:
		LidarDriver();
		LidarDriver(std::vector<std::vector<double>>);
		void new_scan(std::vector<double> array);
		std::vector<double> get_scan();
		void clear_buffer();
		double get_distance(double angle);
		friend std::ostream& operator<<(std::ostream& stream, const LidarDriver& ld);
};

#endif