#pragma once
#include <vector>
#include <thread>
#include "miscellaneous.h"
#include "ObjEnvironment.h"

typedef unsigned short int type_unscaled_obj_coords;
typedef unsigned short int type_scaled_obj_coords;
typedef unsigned int type_timestamp;
typedef uint8_t type_objectclass;

//cout << sizeof(unsigned short int) * 8 << endl; // for relative coordinates
//cout << sizeof(unsigned int)*8 << endl; // for timestamp
//cout << sizeof(unsigned __int8) * 8 << endl; //for objectclass

/*! \file Sensors.h Contains only the parent sensor class and the child radar sensor class*/
/**
* Class sensors represent a polymorphic inheritance of the sensors. (Eevery sensor has a position, even thouhg it might be obsolete they have)
* Both the parent and the child classes are playing a fundemental role in this problem.
*/

using namespace std; 
class Sensors
{
protected:
	int id;
	bool on_off;
	string type; 
	vector<double> pos;
	Environment* env;
public:
	Sensors();
	Sensors(int _id, vector<double> _pos, string _envfile, bool initial_off = false, string _type = "None" );
	virtual bool get_status();
	virtual string get_type();
	virtual int get_id();
	virtual void print_this();
	virtual void SenseObjEnvironment(vector<double*> _position, double* _drivetime, double _duration) {};
	virtual type_timestamp Get_timestamp() { return 0; };
	virtual type_objectclass Get_objectClass() { return 0; };
	virtual vector<type_unscaled_obj_coords> Get_objectCoords() { vector<type_unscaled_obj_coords> dummy; return dummy; };
	bool operator <(const Sensors& rhs) const {return id < rhs.id;}
	virtual ~Sensors();
};

class RadarSensor : public Sensors {
private:
	vector <type_unscaled_obj_coords> obj_coords;
	type_timestamp timestamp;
	type_objectclass objectClass;
	vector <double> range;
	vector<double> r_pos;
public:
	RadarSensor(int _id,vector<double> _pos, vector<double> _range, string _envfile, bool _onoff = false, type_timestamp _timestamp=0, type_objectclass _objectClass=0);
	ofstream catchlog;
	virtual int get_id() { return id; }
	/**
	* The corresponding virtual twin in the parent class is obsolete. 
	+ This function connects the sensor via the environment class. The thread decides if the sensor can emit signals from the object or not. 
	*/
	virtual void SenseObjEnvironment(vector<double*> _position, double* _drivetime, double _duration);
	/**
	*The typedef timestamp (as required in the question) shall be delivered normally to the run time environment via ethernet, but get is used for this model. 
	*/
	virtual type_timestamp Get_timestamp() { return timestamp; };
	/**
	*The typedef objectClass (as required in the question) shall be delivered normally to the run time environment via ethernet, but get is used for this model.
	*/
	virtual type_objectclass Get_objectClass() { return objectClass; };
	/**
	*The typedef unscaled (as well as scaled) coordinates (as required in the question) shall be delivered normally to the run time environment via ethernet, but get is used for this model.
	*/
	virtual vector<type_unscaled_obj_coords> Get_objectCoords() { return obj_coords; };
	virtual void print_this();
};

