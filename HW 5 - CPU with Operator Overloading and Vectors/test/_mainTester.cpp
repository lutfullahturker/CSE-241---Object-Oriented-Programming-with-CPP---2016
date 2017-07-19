#include "requiredIncs.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
	//command line parameters
	const char* filename1 = "r1";
	const char* filename2 = "r2";
	int option = 0;

	int runOpt = atoi(argv[1]);

	CPUProgram myCPUProgram(option);
	myCPUProgram.ReadFile(filename1);
	
	CPUProgram myOtherCPUProgram(option);
	myOtherCPUProgram.ReadFile(filename2);


	switch(runOpt){
		case 0:
			cout << myCPUProgram << endl;
			break;

		case 1:
			//op []
			cout << myCPUProgram[0] << endl;
			cout << myCPUProgram[2] << endl;
			cout << myCPUProgram[4] << endl;
			break;


		case 2:
			//op +
			cout << (myCPUProgram + "MOV R1, 45")[5] << endl;
			cout << "-----------------------------------------------" <<endl;
			cout << myCPUProgram << endl;
			break;


		case 3:
			//op +=
			myCPUProgram += "MOV R1, 45";
			cout << myCPUProgram[5] << endl;
			cout << "-----------------------------------------------" <<endl;
			cout << myCPUProgram << endl;
			break;


		case 4:
			//op + <<
			cout << (myCPUProgram + myOtherCPUProgram) << endl;
			cout << "-----------------------------------------------" <<endl;
			cout << myCPUProgram << endl;
			break;


		case 5:
			//op COMP
			cout << (myCPUProgram == myCPUProgram ? "TRUE" : "FALSE") << endl;
			cout << (myCPUProgram <= myCPUProgram ? "TRUE" : "FALSE") << endl;
			cout << (myCPUProgram >= myCPUProgram ? "TRUE" : "FALSE") << endl;

			cout << (myCPUProgram != myOtherCPUProgram ? "TRUE" : "FALSE") << endl;
			cout << (myCPUProgram < myOtherCPUProgram ? "TRUE" : "FALSE") << endl;
			cout << (myOtherCPUProgram > myCPUProgram ? "TRUE" : "FALSE") << endl;
			break;


		case 6:
			cout << --myCPUProgram << endl;
			cout << "-----------------------------------------------" <<endl;
			cout << myCPUProgram << endl;
			cout << "-----------------------------------------------" <<endl;
			cout << myCPUProgram-- << endl;
			cout << "-----------------------------------------------" <<endl;
			cout << myCPUProgram << endl;
			break;


		case 7:
			//op ()
			cout << myOtherCPUProgram(5, 10) << endl;
			break;


		case 8:
			//error check
			cout << myCPUProgram[5] << endl;
			break;


		case 9:
			//error
			cout << myCPUProgram[8] << endl;

		break;


		case 10:
			cout << myCPUProgram(2,15) << endl;
		break;
	}




	return 0;
}
