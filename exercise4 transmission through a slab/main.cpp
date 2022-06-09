#include "define.h"

int main(void){
	cout << "------------------------------------------------------------------" << endl;
	cout << "|       Exercise #4. Transmission through a slab                 |" << endl;
	cout << "------------------------------------------------------------------" << endl;

	Cmcmanager mcman;
	mcman.readINPUT();
	mcman.mcrun();
	
	Cmcmanager mcman1;
	//mcman1.readINPUT();
	mcman1.mcrunBias();

	Cmcmanager mcman2;
	//mcman2.readINPUT();
	mcman2.mcrunSplitting();

	system("pause");
}