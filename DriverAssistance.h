#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Protocols.h"
#include "Sensors.h"
#include <Windows.h>
#include <thread>
#include <fstream>
#include <chrono>

using namespace std;

/*! \file DriverAssistance.h Contains only the DriverAssistance class and the real time environment variable of that type*/
/**
* Class Driverassistance is almost public. Only the time stamp is considered to be public. 
* The core component of the task, namely sensorprefusion is implemented in this content. 
*/
class DriverAssistance
{
private:
	double* timestamp;
public:
	/**
	*  The default constructer
	*/
	DriverAssistance();
	/**
	*A log file for the thread of the position and the driver time. The data types are precise. 
	*However the required datatypes for sensor are implemented in the corresponding places
	*/
	ofstream positionlog;
	/**
	*The prefusion log file for the sensors. Here, only the timestamp and the catches are printed
	*/
	ofstream sensorprefusionlog;
	/**
	*The launcher of the driving assistance is simply one of the core locations of the task. 
	*/
	void launch(vector<Sensors*> _AudiVehicleSensors,vector<double*> _position, double* _drivetime, double _duration);
	/**
	*A function which is used as thread to print and update global vehicle position and the real time. 
	*/
	void position_log_thread(vector<double*> _position, double* _drivetime, double _duration);
	/**
	*This function can be used to consider the time elapse for communication. 
	*/
	void clock_thread_function();
	/**
	*Sensor pre fusion listens all the individual threads of the sensors and determines catches based on the given criteria.
	*/
	int SensorPreFusion(vector<Sensors*> _AudiVehicleSensors, double* _drivetime, double _duration);
	virtual ~DriverAssistance();
};

