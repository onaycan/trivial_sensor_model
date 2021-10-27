#include "ECU.h"



ECU::ECU()
{
	//sense2recieve2this.insert(make_pair(0, 1));
}

void ECU::run(vector<double*> _position,double* _drivetime, double _duration)
{
	RunTimeEnvironment.launch(AudiVehicleSensors, _position,_drivetime, _duration);
}

void ECU::SetPhysicalConnections(int _protocolid, int _sensorid) {
	sense2recieve2this.insert(make_pair(_protocolid, _sensorid));
}

ECU::~ECU()
{
}
