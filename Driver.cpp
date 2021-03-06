// test1.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <iostream>

#include <thread>
#include "Header.h"

using namespace std;

/*! \file Driver.cpp Contains only the main function */
/**
*
*/
int main() 
{
	

	cout << "Selecting the Car" << endl;
	AudiVehicle HisVehicle("ExampleConfigCar");
	vector<double> direction(3); 
	direction[0] = 0.0;
	direction[1] = 1.0;
	direction[2] = 0.0;
	double velocity = 0.00972222; /// in m/ms
	double duration(2500.0);

	HisVehicle.StartEngine(direction,velocity,duration);
	
	return 0;
}

