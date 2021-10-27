#include "AudiVehicle.h"


enum CarPool {
	ExampleConfigCar,
	AnotherTestCar,
	SomeExpensiveCar,
	InvalidOption
};

CarPool CarofConcern(string _type) {
	map<string, CarPool> type2enum;
	type2enum["ExampleConfigCar"] = ExampleConfigCar;
	type2enum["AnotherTestCar"] = AnotherTestCar;
	type2enum["SomeExpensiveCar"] = SomeExpensiveCar;
	map<string, CarPool>::iterator it;
	it = type2enum.find(_type);
	if (it != type2enum.end())
		return it->second;
	return InvalidOption;

}

AudiVehicle::AudiVehicle()
{
}

AudiVehicle::AudiVehicle(string _type) {
	
	switch (CarofConcern(_type)) {
		case ExampleConfigCar: {
			cout <<"You have selected the car type from the car pool: "<<_type << endl;
			type = _type;
			length = 5.172;
			width = 1.945;
			velocity = 0.0;
			for (int i = 0; i < 3; i++)
			{
				double* zero = new double(0.0);
				position.push_back(zero);
				direction.push_back(0.0);
			}
			
			//Begin: Decleration of ECU's
			ECU* ecuofthis = new ECU();
			ecus.push_back(ecuofthis);
			//End: Decleration of ECU's


			//Begin: Decleration and definition of Sensors
			for (int s = 0; s < 4; s++)
			{
				vector<double> current_pos;
				vector<double> range;
				range.push_back(3.0);
				range.push_back(3.0);
				current_pos.push_back(s / 2 - width / 2.0);
				current_pos.push_back(s % 2 - length / 2.0);
				current_pos.push_back(0.3);

				RadarSensor* sensorofthis = new RadarSensor(s,current_pos,range,"Environment.env",false, 0);
				sensors.push_back(sensorofthis);
				for (unsigned int e = 0; e < ecus.size(); e++)
					ecus[e]->AudiVehicleSensors.push_back(sensorofthis);
			}
			for (unsigned int i = 0; i < sensors.size(); i++)
				sensors[i]->print_this();
			//End: Decleration and definition of Sensors

			//Begin: Decleration and definition of Hardware Protocols
			RadarEthernet* ethernetofthis = new RadarEthernet(0,false,1000);
			protocols.push_back(ethernetofthis);
			for (unsigned int e = 0; e < ecus.size(); e++)
				ecus[e]->AudiVehicleProtocols.push_back(ethernetofthis);
			for (unsigned int i = 0; i < protocols.size(); i++)
				protocols[i]->print_this();

			//End: Decleration and definition of Hardware Protocols
			
			//Begin: Definition of the ECU Physical Protocol hashtags 
			for (unsigned int e = 0; e < ecus.size(); e++)
				for (unsigned int i = 0; i < sensors.size(); i++)
					ecus[e]->SetPhysicalConnections(protocols[0]->get_id(), sensors[i]->get_id());
			//End: Definition of the ECU Physical Protocol hashtags 
			break;
		}
		case AnotherTestCar: {cout << "Not implemented Yet" << endl; break; }
		case SomeExpensiveCar: {cout << "Not implemented Yet" << endl; break; }
		case InvalidOption: {cout << "The car string you have entered could not be mapped to the enumerator" << endl; break; }
		default: {cout<<"one should never see this command output"<<endl; }
		
	}
}

void AudiVehicle::StartEngine(vector<double> _direction, double _velocity, double _duration)
{
	cout << "The Engine has started with initial velocity and position. Launching the ECU's." << endl;
	direction = _direction;
	velocity = _velocity;
	
	thread position_thread(&AudiVehicle::ClockTime_and_UpdatePosition,this, _duration);

	
	for (unsigned int e = 0; e < ecus.size(); e++)
		ecus[e]->run(position,drivetime,_duration);
	
	if (position_thread.joinable())
	{
		cout << "Joining Position Thread " << std::endl;
		position_thread.join();
	}
	
}

void AudiVehicle::ClockTime_and_UpdatePosition(double _duration)
{
	drivetime = new double(0.0);
	while (*(this->drivetime) < _duration) {
		auto t1 = chrono::high_resolution_clock::now();
		//sleeping 1 milliseconds
		Sleep(1);
		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> time_elapsed = t2 - t1;
		*(this->drivetime) = *(this->drivetime) + time_elapsed.count();
		for (int i = 0; i < 3; i++)
			*(this->position[i]) = *(this->position[i]) + velocity * direction[i] * time_elapsed.count();
	}
}

AudiVehicle::~AudiVehicle()
{

}
