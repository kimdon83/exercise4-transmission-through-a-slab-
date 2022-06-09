#include <cmath>

#include "neutron.h"
#include "rng.h"
#include "define.h"

extern rng RN;

Cneutron::Cneutron(){

	weight = 1;
	dtc = 0;
	iPass = 0;
	bRoop = true;
}

Cneutron::~Cneutron(){

}

void Cneutron::IsotropicScattering(){
	double temp;
	do{
		ome[0] = 2 * RN.gnRN() - 1;
		ome[1] = 2 * RN.gnRN() - 1;
		ome[2] = 2 * RN.gnRN() - 1;
		temp = ome[0] * ome[0] + ome[1] * ome[1] + ome[2] * ome[2];
	} while (temp >= 1.0);
	temp = sqrt(temp);
	ome[0] /= temp;
	ome[1] /= temp;
	ome[2] /= temp;
}
void Cneutron::RussianRoulette(){
	//Russian Roulette
	/*
	if (weight < wei_low){
	if (RN.gnRN() < pRR){
	iPass = 0;
	bRoop = false;
	}
	else{
	weight /= (1 - pRR);
	}
	}//Russian Ruoulette end
	*/
	if (weight < 0.1) {
		if (RN.gnRN() * 0.5 < weight) weight = 0.5;
		else{
			iPass = 0; bRoop = false;
		}
	}
}
void Cneutron::Splitting(){
	if (weight > wei_up){
		weight /= 2;
		double pre_loc, pre_weight;
		pre_loc = loc[0];
		pre_weight = weight;

		SimulateTransmissionSplitting();

		loc[0] = pre_loc;
		weight = pre_weight;
		num_spl += 1;
	}
}
int Cneutron::SimulateTransmission(){
	//bRoop = true;
	ome[0] = 1;
	loc[0] = 0;
	do
	{
		dtc = -log(RN.gnRN()) / sigma_t;

		loc[0] += dtc*ome[0];
		if (loc[0] >= length) { // ����ϸ� ������ �ϳ� �ø��� �ݺ����� ����������.
			iPass = 1;
			bRoop = false;
		}
		else if (loc[0] < 0){
			iPass = 0;
			bRoop = false;  // �ڷκ��������� ���
		}
		if (bRoop == false) break;

		if (RN.gnRN() < (sigma_a / sigma_t)){
			iPass = 0;
			bRoop = false;
		}
		IsotropicScattering();

	} while (bRoop);

	return iPass; //����ϸ� 1, ���ϸ� 0�� ��ȯ
}//��Ʈ�� �ϳ� �ùķ��̼� ��

double Cneutron::SimulateTransmissionBias(){
	//bRoop = true;
	ome[0] = 1;
	loc[0] = 0;
	do
	{
		dtc = -log(RN.gnRN()) / sigma_t;
		loc[0] += dtc*ome[0];
		if (loc[0] >= length) { // ����ϸ� ������ �ϳ� �ø��� �ݺ����� ����������.
			iPass = 1;
			bRoop = false;
		}
		else if (loc[0] < 0){// �ڷκ��������� ���
			iPass = 0;
			bRoop = false;
		}

		if (!bRoop) break;

		weight *= (1. - sigma_a / sigma_t);
		RussianRoulette();
		if (!bRoop) break;

		IsotropicScattering();
	} while (bRoop);

	return iPass*weight; 
}//��Ʈ�� �ϳ� �ùķ��̼� ��

double Cneutron::SimulateTransmissionSplitting(){
	//bRoop = true;
	ome[0] = 1;
	loc[0] = 0;
	do
	{
		dtc = -log(RN.gnRN()) / sigma_t;
		loc[0] += dtc*ome[0];
		if (loc[0] >= length) { // ����ϸ� ������ �ϳ� �ø��� �ݺ����� ����������.
			iPass = 1;
			bRoop = false;
		}
		else if (loc[0] < 0){// �ڷκ��������� ���
			iPass = 0;
			bRoop = false;
		}

		if (!bRoop) break;

		weight *= (1. - sigma_a / sigma_t);
		RussianRoulette();
		if (!bRoop) break;
		Splitting();
		IsotropicScattering();
	} while (bRoop);

	return iPass*weight; 
}