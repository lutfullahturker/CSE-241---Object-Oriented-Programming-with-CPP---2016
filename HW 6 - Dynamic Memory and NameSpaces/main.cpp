/* 
 * File:   CPUProgramDyn.h
 * Author: Lütfulah TÜRKER
 *
 * Created on 25 November 2016, 14:09
 */

/* 
 * File:   main.cpp
 * Author: Lütfullah TÜRKER
 *
 * Created on 25 November 2016, 14:02
 */

#include "requiredIncs.h"



int main(int argc, char** argv){
	//////////////////////////////////////////////////////////////////////////
	//command line parameters
	const char* filename = argv[1];
	int option = atoi(argv[2]);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//Testing class CPUProgramDyn
	CPUProgramDyn myProg(option);
        CPUProgramDyn myProg2(myProg);
        --myProg ;
        myProg.ReadFile(filename);
        myProg2.ReadFile("Square.txt");
        cout << (myProg + --myProg2)<<endl;
        myProg--;
        myProg+="testt";
        cout<<myProg[myProg.size()-1] << endl;
        if (myProg < myProg2){
            myProg2 = myProg;
        cout << myProg+myProg2<<endl;}
        if (myProg >myProg2){
            myProg=myProg2;
        cout << myProg+myProg2<< endl<<"(myProg > myProg2)"<<endl; }
        myProg += "eklendi !!!";
        cout<<myProg[myProg.size() -1]<<endl;
	//////////////////////////////////////////////////////////////////////////

	return 0;
}
