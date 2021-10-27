#pragma once
#include <vector>
#include "miscellaneous.h"
using namespace std;
/*! \file Protocols.h Contains only the parent protocol class and the child radar ethernet class*/
/**
* Class protocolls represent a polymorphic inheritance of the hardware protocolls. 
* Both the parent and the child classes are constructed but later on not really used. For an extension problem those classes might be usefull.
*/
class Protocols
{
protected:
	int id;
	bool on_off;
	string type;
public:
	Protocols();
	Protocols(int _id, bool _on_off = false, string _type="None");
	virtual bool get_status();
	virtual string get_type();
	virtual int get_id();
	virtual int get_bits_per_ms() { return 0; };
	virtual void print_this();
	virtual ~Protocols();
};

class RadarEthernet : public Protocols {
private:
	int bits_per_ms;
public:
	RadarEthernet(int _id, bool _onoff = false, int _bits_per_ms = 0);
	virtual int get_bits_per_ms() { return bits_per_ms; };
	virtual int get_id() { return id; };
	virtual void print_this();
};