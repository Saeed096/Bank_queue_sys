#pragma once

class Client
{
public:
	float arrival_time;           
	float service_duration;       
	float leave_time;              
	int waiting_time;
	int servingTellerId;
	bool isVip = false;
	string name;

	bool operator> (Client c1)
	{
		return this->arrival_time > c1.arrival_time;      
	}

	bool operator< (Client c1)
	{
		return this->arrival_time < c1.arrival_time;
	}

	bool operator== (Client c1)
	{
		return this->arrival_time == c1.arrival_time;
	}
};

