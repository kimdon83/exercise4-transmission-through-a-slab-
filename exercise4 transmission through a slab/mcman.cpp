#include "mcman.h"
#include "define.h"
#include "neutron.h"

rng RN;

Cmcmanager::Cmcmanager(){
	Num_history = 10000; set = 100;

	q = 0.;	qMean = 0.;	qVar = 0.;
	qSum = 0.; qSqu = 0.; 

}
Cmcmanager::~Cmcmanager(){


}

int Cmcmanager::readINPUT(void){

	//
	//cin >> Num_history;
	//Num_history = 10000;
	//cin >> set;
	//set = 100;
	return 0;
}
int Cmcmanager::mcrun(void){
	cout << "      input the number of history " << endl << Num_history<<endl;

	start = chrono::system_clock::now();

	cout << "1. Non-Baiased Sampling" << endl;

	for (i = 0; i < set; i++){
		q = 0;
		for (j = 0; j < Num_history; j++){
			//// simulation 시작
			Cneutron neutron;// 클래스 정의			
			q += neutron.SimulateTransmission();////뉴트론 하나 시뮬레이션 끝
		}
		qSum += q/Num_history; //Num_history 중 통과한 비율을 적산
		qSqu += (q / Num_history)*(q / Num_history);
	}
	qMean = qSum / set;
	qVar = (-qMean*qMean + (qSqu / set)    );
	// cout the result
	cout << "Mean : " << qMean << endl;
	cout << "Variance : " << qVar << endl;

	// cout the result
	cout << "Variance of mean : " << qVar / Num_history << endl;
	cout << endl;

	end = chrono::system_clock::now();
	time = end - start;
	cout << "------------------------------------------------------------------" << endl;
	cout << "      Time = " << time.count() << endl;
	cout << "------------------------------------------------------------------" << endl;

	return 0;
}
int Cmcmanager::mcrunBias(void){
	start = chrono::system_clock::now();

	cout << "2. Importance Sampling(survival biasing,RR)" << endl;

	for (i = 0; i < set; i++){
		q = 0;
		for (j = 0; j < Num_history; j++){
			//// simulation 시작
			Cneutron neutron;// 클래스 정의			
			q += neutron.SimulateTransmissionBias();////뉴트론 하나 시뮬레이션 끝
		}
		qSum += q / Num_history; //Num_history 중 통과한 비율을 적산
		qSqu += (q / Num_history)*(q / Num_history);
	}
	qMean = qSum / set;
	qVar = (-qMean*qMean + (qSqu / set));
	// cout the result
	cout << "Mean : " << qMean << endl;
	cout << "Variance : " << qVar << endl;

	// cout the result
	cout << "Variance of mean : " << qVar / Num_history << endl;
	cout << endl;

	end = chrono::system_clock::now();
	time = end - start;
	cout << "------------------------------------------------------------------" << endl;
	cout << "      Time = " << time.count() << endl;
	cout << "------------------------------------------------------------------" << endl;

	return 0;
}
int Cmcmanager::mcrunSplitting(void){
	start = chrono::system_clock::now();

	cout << "3. Importance Sampling(survival biasing,RR,Splittint)" << endl;

	for (i = 0; i < set; i++){
		q = 0;
		for (j = 0; j < Num_history; j++){
			//// simulation 시작
			Cneutron neutron;// 클래스 정의

			for (int i = 0; i < 3; i++){
				neutron.ome[i] = 0;
				neutron.loc[i] = 0;
			}
			neutron.num_spl = 0;

			q += neutron.SimulateTransmissionSplitting();////뉴트론 하나 시뮬레이션 끝
			Num_history += neutron.num_spl;

		}
		qSum += q / Num_history; //Num_history 중 통과한 비율을 적산
		qSqu += (q / Num_history)*(q / Num_history);
	}
	qMean = qSum / set;
	qVar = (-qMean*qMean + (qSqu / set));
	// cout the result
	cout << "Mean : " << qMean << endl;
	cout << "Variance : " << qVar << endl;

	// cout the result
	cout << "Variance of mean : " << qVar / Num_history << endl;
	cout << endl;

	end = chrono::system_clock::now();
	time = end - start;
	cout << "------------------------------------------------------------------" << endl;
	cout << "      Time = " << time.count() << endl;
	cout << "------------------------------------------------------------------" << endl;

	return 0;
}