//#include "header.h"
#include "iif.h"

int f3(int* a) {
	int x = a[0];
	int y = a[1];
	int z = a[2];
	iif_assume(x + y + z >= 0);
	while (z> 0) {
		recordi(x, y, z);
		x++;
		y++;
		z -= 2;
	}

	recordi(x, y, z);
	iif_assert(x + y >= 0);
	return 0;
}


int main(int argc, char** argv)
{
	States global_states_sets[4];
	States* gsets = &global_states_sets[1];

	if (register_program(f3, "f3") == false) {
		return -1;
	} 

#ifdef linux
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		exit(-1);
	alarm(60);
#endif
	std::cout << "TRY SVM method ...\n";
	IIF_svm_learn isl(gsets, target_program);
	if (isl.learn() == 0) {  
		return 0;
	}

	std::cout << "TRY SVM-I method ...\n";
	IIF_svm_i_learn isil(gsets, target_program);
	if (isil.learn() == 0) {	
		return 0;
	}

	//std::cout << "TRY other method again...\n";
	return 0;
}
