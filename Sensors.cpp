#include "Sensors.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <Windows.h>
#include "ObjEnvironment.h"

using namespace std;



Sensors::Sensors()
{
}

Sensors::Sensors(int _id, vector<double> _pos, string _envfile, bool initial_off, string _type)
{
	env=new Environment(_envfile);


	id = _id;
	for (int i = 0; i < 3; i++)
		pos.push_back(_pos[i]);
	on_off = initial_off;
	type = _type;
}

bool Sensors::get_status()
{
	return on_off;
}

string Sensors::get_type()
{
	return type;
}

int Sensors::get_id()
{
	return id;
}


void Sensors::print_this()
{
	cout << tabs(1) << " has a type of " << type << " sensor"
	<< " and has a status of " << on_off << endl;
}

Sensors::~Sensors()
{
}

RadarSensor::RadarSensor(int _id, vector<double> _pos, vector<double> _range, string _envfile,
						 bool _onoff, type_timestamp _timestamp,  type_objectclass _objectClass)
	: Sensors(_id, _pos, _envfile, _onoff, "RadarSensor"), timestamp(_timestamp) , objectClass(_objectClass)
{
	for(unsigned int i=0;i<_range.size();i++)
	range.push_back(_range[i]); 
	r_pos.resize(3);
	obj_coords.resize(3);
	for (int i = 0; i < 3; i++)
	{
		r_pos[i] = 0;
		obj_coords[i] = 0;
	}
}

void RadarSensor::print_this() { 
	cout << tabs(1) << " has a type of " << Sensors::type<<" sensor"
	<< " which has a timestamp of " << timestamp
	<< " position of [X:"<<pos[0]<<" Y:"<<pos[1]<<" Z:"<<pos[2]<<"]"
	<< " has range of "<<range[0]<<" l-r "<<range[1]<<" f-a"
	<< " and has a status of " << Sensors::on_off<< endl;
	};

void RadarSensor::SenseObjEnvironment(vector<double*> _position, double* _drivetime, double _duration) {
	catchlog.open("Threadlog_catches_of_RadarSensor_"+to_string(id)+".log", ofstream::out);
	while (*_drivetime<_duration) {
		Sleep(1);
		for (int i = 0; i < 3; i++)
			r_pos[i] = pos[i] + *_position[i];
		timestamp = type_timestamp(*_drivetime);
		for (unsigned int j = 0; j < env->real_object_coordinates[0].size(); j++)
		{
			double difx = env->real_object_coordinates[0][0] - r_pos[0];
			double dify = env->real_object_coordinates[0][1] - r_pos[1];
			if (difx < range[0] && difx > -range[0] && dify < range[1] && dify > -range[1])
			{
				
				objectClass = type_objectclass(env->real_object_type[0]);
				for (int i = 0; i < 3; i++)
				{
					obj_coords[i] = type_unscaled_obj_coords(env->real_object_coordinates[0][i] - *_position[i]);
					obj_coords[i] = obj_coords[i] << 1000; /// SCALING!
				}
				//some charachters are unvisible therefore further standard unsigned shall be used here
				//catchlog << timestamp << " " << unsigned(objectClass) << endl;
				catchlog << *_drivetime << " " << env->real_object_type[0] << endl;
			}
			else
			{
				objectClass = type_objectclass(0);
				for (int i = 0; i < 3; i++)
					obj_coords[i] = type_unscaled_obj_coords(0);
				
				catchlog << *_drivetime << " " << 0 << endl;
			}
		}
		
	}
	catchlog.close();

}