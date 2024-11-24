#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H 
#include <iostream>
#include <vector>

class LidarDriver
{
	private:
		std::vector<std::vector<double> > matrix;
		int cont;	//indice dell'ultima scansione(vettore di misure)
		static constexpr int BUFFER_DIM = 10;
		const double resolution; // const perche' le specifiche richiedono che la risoluzione sia fissa per tutta la durata
		// di vita dell'istanza di oggetto
		
	public:
		LidarDriver(double);
		LidarDriver(std::vector<std::vector<double> >);
		void new_scan(std::vector<double> array);
		std::vector<double> check_array(std::vector<double> array);
		int get_element_number();
		std::vector<double> get_scan();
		void clear_buffer();
		double get_distance(double angle);
		friend std::ostream& operator<<(std::ostream& stream, const LidarDriver& ld);
};

#endif