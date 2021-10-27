#include "DriverAssistance.h"
#include <iostream>
#include"miscellaneous.h"
using namespace std;


DriverAssistance::DriverAssistance()
{
	
}

void DriverAssistance::position_log_thread(vector<double*> _position, double* _drivetime, double _duration) {
	
	while (*_drivetime<_duration) {
		this->positionlog << *_drivetime <<" "<<*_position[0] <<" "<< *_position[1] <<" "<< *_position[2]  <<endl;
	}
	}

void DriverAssistance::clock_thread_function() {
	auto tstart = chrono::high_resolution_clock::now();
	while (true) {
		auto tend = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> time_elapsed = tend - tstart;
		*(this->timestamp) = time_elapsed.count();
	}
}

int DriverAssistance::SensorPreFusion(vector<Sensors*> _AudiVehicleSensors, double* _drivetime, double _duration) {
	unsigned short int catches = 0;
	vector<unsigned short int> catchers;
	while (*_drivetime < _duration) {
		type_objectclass catched = 0;
		for (unsigned int i = 0; i < _AudiVehicleSensors.size(); i++)
		{	
			if (Ltwnorm(_AudiVehicleSensors[i]->Get_objectCoords())!=0)
			for (unsigned int j = i+1; j < _AudiVehicleSensors.size(); j++)
			{
				if (_AudiVehicleSensors[i]->Get_objectClass() == _AudiVehicleSensors[j]->Get_objectClass())
				{
					if (Ltwnorm(_AudiVehicleSensors[i]->Get_objectCoords()) != 0)
						if(_AudiVehicleSensors[i]->Get_objectCoords()[0]== _AudiVehicleSensors[j]->Get_objectCoords()[0])
							if (_AudiVehicleSensors[i]->Get_objectCoords()[1] == _AudiVehicleSensors[j]->Get_objectCoords()[1])
								if (_AudiVehicleSensors[i]->Get_objectCoords()[2] == _AudiVehicleSensors[j]->Get_objectCoords()[2])
								{
									catched = _AudiVehicleSensors[j]->Get_objectClass();
									catchers.push_back(i);
									catchers.push_back(j);
									catches++;
									goto there;
								}
				}
			}
		}
		there:
		{
			if (catches == 2)
			{
				catches--;
				cout <<"At real time: "<<*_drivetime<<" the objectclass "<<unsigned(catched)
					 <<" is detected at least by sensors "<<to_string(catchers[0])<<" and "<< to_string(catchers[1]) <<endl;
				

			}
		}
		sensorprefusionlog << *_drivetime << " " << unsigned(catched) << endl;

		Sleep(10);
	}
	return 0;
}

void DriverAssistance::launch(vector<Sensors*> _AudiVehicleSensors, vector<double*> _position, double* _drivetime, double _duration){
	
	vector<thread> SensorRecieverThreads;
	timestamp = new double(0.0);
	
	positionlog.open("Threadlog_Wheel_and_GPS_position.log", ofstream::out);
	thread position_log_thread(&DriverAssistance::position_log_thread,this,_position,_drivetime, _duration);
	
	for (unsigned int i = 0; i < _AudiVehicleSensors.size(); i++)
	{
		thread SenseObjEnvThread(&Sensors::SenseObjEnvironment, _AudiVehicleSensors[i], _position, _drivetime, _duration);
		SensorRecieverThreads.push_back(move(SenseObjEnvThread));
	}

	sensorprefusionlog.open("SensorPreFusion.log", ofstream::out);
	thread sensorprefusionthread(&DriverAssistance::SensorPreFusion, this, _AudiVehicleSensors, _drivetime, _duration);


	if (position_log_thread.joinable())
	{
		cout << "Joining Position log Thread " << std::endl;
		position_log_thread.join();
	}
	for (unsigned int i = 0; i < SensorRecieverThreads.size(); i++)
	if (SensorRecieverThreads[i].joinable())
	{
		cout << "Joining sense environment Thread " <<to_string(_AudiVehicleSensors[i]->get_id())<< std::endl;
		SensorRecieverThreads[i].join();
	}

	if (sensorprefusionthread.joinable())
	{
		cout << "Joining Sensor Pre Fusion Thread " << std::endl;
		sensorprefusionthread.join();
	}
	
	//cout << SensorPreFusion() << endl;

	
}


DriverAssistance::~DriverAssistance()
{
}
