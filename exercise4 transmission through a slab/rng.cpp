#include <stdio.h>
#include <cmath>
#include "rng.h"

#define LOW16(p)    ( (unsigned long)(p) & 0x0000ffff )
#define UP16(p)     ( LOW16( (p)>>16 ) )

rng::rng(){
	l[3] = 0x2545;
	l[2] = 0xF491;
	l[1] = 0x4F6C;
	l[0] = 0xDD1D;
	xi[3] = 0x0000; xi[2] = 0x1234; xi[1] = 0xabcd; xi[0] = 0x330e;
	//xi[2] = 0x0000; xi[1] = 0x0000; xi[0] = 0x0005;
	two_m16 = 1.0 / pow(2.0, 16);

}
rng::~rng(){

}

double rng::gnRN(){

	unsigned short bl[12];
	unsigned short bu[8];

	bl[0] = LOW16(l[0] * xi[0]);
	bu[0] = UP16(l[0] * xi[0]);

	bl[1] = LOW16(l[1] * xi[0]);
	bu[1] = UP16(l[1] * xi[0]);

	bl[2] = LOW16(l[0] * xi[1]);
	bu[2] = UP16(l[0] * xi[1]);

	bl[3] = LOW16(l[2] * xi[0]);
	bu[3] = UP16(l[2] * xi[0]);

	bl[4] = LOW16(l[1] * xi[1]);
	bu[4] = UP16(l[1] * xi[1]);

	bl[5] = LOW16(l[0] * xi[2]);
	bu[5] = UP16(l[0] * xi[2]);

	bl[6] = LOW16(bu[0] + bl[1] + bl[2]);
	bu[6] = UP16(bu[0] + bl[1] + bl[2]);

	bl[7] = LOW16(bu[1] + bu[2] + bl[3] + bl[4] + bl[5]);
	bu[7] = UP16(bu[1] + bu[2] + bl[3] + bl[4] + bl[5]);

	bl[8] = LOW16(l[3] * xi[0]);
	bl[9] = LOW16(l[2] * xi[1]);
	bl[10] = LOW16(l[1] * xi[2]);
	bl[11] = LOW16(l[0] * xi[3]);


	xi[0] = bl[0];
	xi[1] = bl[6];
	xi[2] = bu[6] + bl[7];
	xi[3] = bu[7] + bu[3] + bu[4] + bu[5] + bl[8] + bl[9] + bl[10] + bl[11];

	return xi[0] * two_m16*two_m16*two_m16*two_m16 + xi[1] * two_m16*two_m16*two_m16 + xi[2] * two_m16*two_m16 + xi[3] * two_m16;

}