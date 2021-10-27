#pragma once
#include<vector>
#include<map>
#include "Protocols.h"
#include "Sensors.h"
#include "DriverAssistance.h"
#include <iostream>
#include <string>
#include <chrono>
#include <windows.h>
#include <thread>

using namespace std;
typedef unsigned int uint32;

/*! \file ECU.h Contains only the ECU class*/
/**
* Class ECU contains mainly two privat members. The first one defined the hashtag from sensors to protocolls, but this is not used in this content. 
* The idea was to simulate the time gap based on the communication elapse. For this problem the ethernet listener and emitter is assummed to be fast enough. 
* The second private member is the runtimeenvironment as a driver assistance system which does not activate any actors and does not take action but listens carefully. 
*/
class ECU
{
private:
	map <int, int> sense2recieve2this;
	DriverAssistance RunTimeEnvironment; 
public:
	/**
	* The constructer
	*/
	ECU();
	/**
	* The vehicle sensors are considered to be public members of ECU, since they do not really belong to ECU but to the vehicle. ECU is suppossed to communicate with those. 
	*/
	vector<Sensors*> AudiVehicleSensors;
	/**
	* The vehicle hardware busses are considered to be public members of ECU, since they do not really belong to ECU but to the vehicle. ECU is suppossed to communicate with those.
	*/
	vector<Protocols*> AudiVehicleProtocols;
	/**
	*This function inserts members to the hashtag (private map)
	*/
	void SetPhysicalConnections(int _protocolid, int _sensorid);
	/**
	* The run calls the runtime environment. A gateway to the core of the problem. 
	*/
	void run(vector<double*> _position,double* _drivetime, double _duration);
	virtual ~ECU();
};

