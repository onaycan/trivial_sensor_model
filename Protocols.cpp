#include "Protocols.h"
#include<iostream>

using namespace std;



Protocols::Protocols()
{
}

Protocols::Protocols(int _id, bool _on_off, string _type)
{
	id = _id;
	on_off = _on_off;
	type = _type;
}

bool Protocols::get_status()
{
	return on_off;
}

string Protocols::get_type()
{
	return type;
}

int Protocols::get_id() {
	return id;
}

void Protocols::print_this()
{
	cout << tabs(1) << " has a type of " << type << " protocoll"
		<< " and has a status of " << on_off << endl;
}

Protocols::~Protocols()
{
}

RadarEthernet::RadarEthernet(int _id, bool _onoff, int _bits_per_ms) : Protocols(_id, _onoff,"RadarEthernet"), bits_per_ms(_bits_per_ms){}

void RadarEthernet::print_this() {
	cout <<tabs(1)<<" has a type of " <<type<<" protocoll"
	<< " which has a rate of communication " << bits_per_ms
	<< " and has a status of " <<on_off<< endl;
};