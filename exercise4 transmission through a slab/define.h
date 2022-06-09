#include <iostream>
#include <iomanip>
#include <stdlib.h> // srand, rand
#include <chrono>
#include <iostream>

#include "mcman.h"
#include "rng.h"

using namespace std;

#define _pi 3.14159265358979

//Cross Section
#define sigma_t 0.1
//#define sigma_s 0.08
#define sigma_a 0.03


#define length 50

//Russian Roulette
#define wei_low 0.25	//weight lower limit
#define wei_up  1.5	//weight upper limit
#define pRR     0.25	//probability of Russian Roulette