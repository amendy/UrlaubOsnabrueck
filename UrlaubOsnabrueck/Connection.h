#pragma once
#include"Edge.h"
using namespace std;

extern double globalFaktor;

class Connection : public Edge
{
public:
	Connection(Node& rSrc, Node& rDes, double distance, int type) : Edge(rSrc, rDes),
		m_distance(distance), m_type(type)
	{
		if (type == 1)
		{
			m_typeName = "FussWeg";
			m_geschwindigkeit = 5;
			m_kost = 0;
		}
		else if (type == 2)
		{
			m_typeName = "Bus";
			m_geschwindigkeit = 15;
			m_kost = 3;
		}
		else if (type == 3)
		{
			m_typeName = "Taxi";
			m_geschwindigkeit = 45;
			m_kost = (2 * m_distance);
		}
		else if (type == 4)
		{
			m_typeName = "S-Bahn";
			m_geschwindigkeit = 30;
			m_kost = 3;
		}
		else
		{
			m_typeName = "Bergbahn";
			m_geschwindigkeit = 10;
			m_kost = 8;
		}
	}

	virtual double getWeight()
	{
		if (globalFaktor == 1)
		{
			return (m_distance / m_geschwindigkeit);
		}
		else if (globalFaktor == 2)
		{
			return  m_kost;
		}
		else
		{
			return 1;
		}
		return 0;
	}

	double getDistance()
	{ 
		return m_distance; 
	}
	int getType() 
	{ 
		return m_type; 
	}
	double getSpeed() 
	{ 
		return m_geschwindigkeit;
	}
	double getKost() 
	{ 
		return m_kost; 
	}
	string getTypeName() 
	{ 
		return m_typeName; 
	}

private:
	double m_kost;
	double m_distance;
	double m_geschwindigkeit;
	int m_type;
	string m_typeName;
};

