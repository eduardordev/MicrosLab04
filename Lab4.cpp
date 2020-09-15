/*
-------------------------------------------
Lab4.cpp
-------------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
PROGRAMACION DE MICROPROCESADORES
SECCION 20

AUTHORS:
Oscar De Leon - 19298
Eduardo Ramirez - 19946
Marco Ramirez - 19588

version 1.0
DATE: 15/09/2020

-------------------------------------------
Encryption and decryption of text documents
-------------------------------------------

*/
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

}

int main()
{
    int opc;
	int rc;
	int op;
	string txt;
	txt = readFile();
	bool st = true;

	pthread_t threadID;

    //Menu Principal
	cout<<"t\Welcome to EasyEncrypt"<<endl;
	cout<<"Available Options:"<<endl;
	cout<<"1. -> Encrypt File"<<endl;
	cout<<"2. -> Decrypt File"<<endl;
	cout<<"3. -> Exit"<<endl;
	cout<<"Desired Operation: ";
	cin>>opc;

	/*
	Sistema de ejecucion por opciones
	Switch como alternativa a operador logico if
	*/
	switch(opc){
        case 1:
            cout<<"t\ENCRYPT PROCESS STARTED"<<endl;

        case 2:
            cout<<"t\DECRYPT PROCESS STARTED"<<endl;

        case 3:
            break;

	}



	return 0;
}
