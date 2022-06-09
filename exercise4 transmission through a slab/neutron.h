#ifndef _neutron_h_KDH
#define _neutron_h_KDH

#include "rng.h"
#include "define.h"

extern rng RN;


class Cneutron{
private:

	double weight;

	double dtc;// distance to collision

	int iPass; // 통과 하냐 못하냐를 저장하는 1,0을 저장하지만 반환후 적산을 위해 int로 정의한다.
	//bool bCol; // 충돌여부를 나타내는 bool variable
	bool bRoop;	//while문 중단 여부를 확인 하는 bool variable

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