#ifndef _neutron_h_KDH
#define _neutron_h_KDH

#include "rng.h"
#include "define.h"

extern rng RN;


class Cneutron{
private:

	double weight;

	double dtc;// distance to collision

	int iPass; // ��� �ϳ� ���ϳĸ� �����ϴ� 1,0�� ���������� ��ȯ�� ������ ���� int�� �����Ѵ�.
	//bool bCol; // �浹���θ� ��Ÿ���� bool variable
	bool bRoop;	//while�� �ߴ� ���θ� Ȯ�� �ϴ� bool variable

private:
	void IsotropicScattering();
	void RussianRoulette();
	void Splitting();

public:
	double ome[3], loc[3];
	int num_spl;

	Cneutron();
	~Cneutron();
	
	int SimulateTransmission();
	double SimulateTransmissionBias();
	double SimulateTransmissionSplitting();
	
};
#endif