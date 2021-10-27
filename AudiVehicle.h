#pragma once
#include "ECU.h"
#include "miscellaneous.h"

/*! \file AudiVehicle.h Contains only the Vehicle Class.*/
/**
* Class AudiVehicle contains a single generic vehicle where the actors, sensors, agents protocolls and controll units to be attached. 
* Mechanics and dimensions as well as the kinematics of the vehicle is filled by means of the constructers and other public functions
*/
class AudiVehicle
{
private:
	/**
	* The type is defining the type of the vehicle as string. 
	* The configuration can be extended by means of the eneumerator. 
	*/
	string type; 
	/**
	* The physical duimensions of the vehicle. Those are used to place the sensors. 
	*/
	double length;
	double width; 
	/**
	*The position pointer vector as well as the direction. Especially the position will be threaded in this code. 
	*/
	vector<double*> position;
	vector<double> direction;
	/**
	*The driver time is representing the real time. 
	*/
	double* drivetime;
	/**
	*The velocity is considered to be an input to the vehicle class. 
	*/
	double velocity;
	/**
	*The vehicle can contain more then one ECU. The relationships in between protocolls and sensors are contained in this vector of pointers. 
	*/
	vector<ECU*> ecus;
	/**
	*The vehicle can again contain many sensors. 
	*/
	vector<Sensors*> sensors;
	/**
	*Many protocols, for example CAN bus and other fast ethernets can be implemented in this model.
	*/
	vector<Protocols*> protocols;


public:
	/**
	* The default constructer of this principally doing nothing but providing new assignment which is used in this context. 
	*/
	AudiVehicle(); 
	/**
	* This constructer prepares the vehicle before the run. Based on a car pool (enumurator), the constructer sets the relatinships 
	* in between sensors and protocols. ECU's and more are also declared in this content.
	*/
	AudiVehicle(string _type);
	/**
	* This function does not necessarily defines the idle condition. It is the enterance to the real time environment, thus the kinematics (velcity)
	* is in this case quite crucial to determine the behavior of the threads. 
	*/
	void StartEngine(vector<double> direction, double _velocity, double _duration); 
	/**
	* A function which is threaded. This function can be considered as a wheel or GPS sensor. Better would be to inherit another sensor from the parent and 
	* read those variables accordingly. But since any actor, including the valves, brakes and especiall engine is missing in this context, a simple thread is replaced this purpose. 
	*/
	void ClockTime_and_UpdatePosition(double _duration);
	vector<Protocols*> get_protocols() { return protocols;  };
	virtual ~AudiVehicle();
};

