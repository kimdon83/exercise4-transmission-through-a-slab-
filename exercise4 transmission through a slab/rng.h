#ifndef _rng_h_
#define _rng_h_
#include <math.h>

class rng{
public:
	double two_m16;

	unsigned short l[4];// 2685 8216 5773 6338 717 2685821657736338717 2545 F491 4F6C DD1D
	unsigned short xi[4];

	rng();
	~rng();

	double gnRN(void);

};
#endif
