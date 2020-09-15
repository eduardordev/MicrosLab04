#include <iostream>
#include <stdio.h>		
#include <fstream> 		
#include <stdlib.h>		
#include <string>
#include <cstdlib>		
#include <cmath>
#include <sstream>		
#include <vector>		
#include <unistd.h>		
#include <bitset>			
#include <ctime>		
#include <pthread.h>			
	
using namespace std;

int const bufferL = 8;
int const threadCount = 4;

string const filetxt = "datos.txt";
string cifrado = "";

string readFile(){
	ifstream fileStream(filetxt, ios::in);

	if(!fileStream){

		cerr<<"ERROR AT READING FILE"<<filetxt<<endl;
		exit(EXIT_FAILURE);

	}

	string result;

	if(fileStream){
		
		ostringstream receiver;
		receiver<<fileStream.rdbuf();
		result = receiver.str();

	}

	return result;
}

void *cifrarTxt(void *arg){
	// que pedo
}

int main()
{
	int rc;
	int op;
	string txt;
	txt = readFile();
	bool st = true;

	pthread_t threadID;

	return 0;
}
