#ifndef _MCMAN_H_KDH_
#define _MCMAN_H_KDH_

#include "define.h"


class Cmcmanager{
private:
	int i,j,k;
	rng RN;

	double theta;
	double pdf;

	int Num_history,Num;
	int set;

	//double loc; // x coordinate
	//double delta_loc; // º¯À§
	double qSum, qSqu;
	double q, qMean, qVar;

	chrono::system_clock::time_point start;
	chrono::system_clock::time_point end;
	chrono::duration<double> time;


public:

	Cmcmanager();
	~Cmcmanager();

	int readINPUT(void);
	int mcrun(void);
	int mcrunBias(void);
	int mcrunSplitting(void);


};
#endif