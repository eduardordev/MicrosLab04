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
string const clave = "P0L1N0M14L";
int counter = 0;
pthread_cond_t fullstack, emptystack;
pthread_mutex_t mutexf;
sem_t count_sem, barrier_sem, done_sem;

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

	string &aStr = *(static_cast<string*>(arg));
	string str1 = "";
	string str2 = "";

	pthread_mutex_lock(&mutexf);
	counter++;

	if(counter == threadCount){
		counter = 0;

		pthread_cond_broadcast(&emptystack);
		pthread_cond_wait(&fullstack, &mutexf);
		
	}
	else
	{
		counter++;
	
	}

	

	//ejecucion de cifrado
	
	int a=0;
	//For que incluye los ultimos cuatro caracteres del string (Ronda 1)
	for(int i=bufferLength-4;i<bufferL;i++){
		str1 += (aStr[i]^clave[a]);
		a++;
	}
	for(int j=0;j<bufferL-4;j++){
		str1 += aStr[j];
	}
	//Ronda 2
	aStr="";
	a=0;
	for(int i=bufferLength-4;i<bufferL;i++){
		aStr += (str1[i]^clave[a]);
	}
	for(int j=0;j<bufferL-4;j++){
		aStr += str1[j];
	}
	//Ronda 3
	str1="";
	a=0;
	for(int i=bufferLength-4;i<bufferL;i++){
		str1 += (aStr[i]^clave[a]);
	}
	for(int j=0;j<bufferL-4;j++){
		str1 += aStr[j];
	}
	//Ronda 4
	aStr="";
	a=0;
	for(int i=bufferLength-4;i<bufferL;i++){
		aStr += (str1[i]^clave[a]);
	}
	for(int j=0;j<bufferL-4;j++){
		aStr += str1[j];
	}
	
	//Se añade el string cifrado al texto global cifrado
	cifrado += aStr;

	//Se finaliza el thread
	pthread_mutex_unlock(&mutexf);
	pthread_exit(NULL);

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
	pthread_cond_init(&fullstack, NULL); 
	pthread_cond_init(&emptystack, NULL);
	pthread_mutex_init(&mutexf, NULL);
	

    //Menu Principal
	cout<<"Welcome to EasyEncrypt"<<endl;
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
            cout<<"ENCRYPT PROCESS STARTED"<<endl;

            if(txt==""){
				cout<<"The file"<<filetxt<<" is empty."<<endl;
			}
			else{

				string temp = "";
				int letras;
				int cnt = 0; //contador de letras
				int rp;
				
				//Se determina cuantos grupos de caracteres se crearan a partir del tamaño del buffer definido
				if(((txt.length())%bufferL)>0){
					letras = (int)(txt.length()/bufferL)+1;
				}
				else{
					letras = (int)(txt.length()/bufferL);
				}
				
				string clct [letras];
				
				//Se recorre el texto y se separa en sus respectivos grupos, los cuales se almacenan en collection
				for(int i=0;i<letras;i++){
					rp = 0;
					
					if((a+bufferL-1)>(txt.length()-1)){
						while(rp < bufferL && (a+rp)<(txt.length()-1)){
							temp += txt[a+rp];
							rp++;
						}
					}
					else{
						while(rp < bufferL){
							temp += txt[a+rp];
							rp++;
						}
					}
					
					clct[i] = temp;
					a+=bufferL;
					temp = "";
				}
				
				vector<string> stack;
				for(int i=0;i<letras;i++){
					stack.push_back(clct[i]);
				}
				
				while(stack.size()>0){
					for(int j=0;j<threadCount && stack.size()>0;j++){
						
						temp = stack.back();
						stack.pop_back();

						
						rc = pthread_create(&threadID,NULL,cifrarTxt,static_cast<void*>(&temp));
						usleep(1000);
						

						if(rc){
							printf("ERROR; return code from pthread_create() is %d\n", rc);
							exit(-1);
						}

						rc = pthread_join(threadID, NULL);
						

						if(rc){
							printf("ERROR; return code from pthread_join() is %d\n", rc);
							exit(-1);
						}
					}
				}

				ofstream outFile("out.bin",ios::binary);
				if(!outFile)
				{
					cerr<<"Error making out.bin"<<endl;
					exit(EXIT_FAILURE);
				}
				outFile<<cifrado;

			}
	
			cout<<"El texto cifrado se ha escrito exitosamente."<<endl;

        case 2:
            cout<<"DECRYPT PROCESS STARTED"<<endl;

        case 3:
            break;

	}

	return 0;
}
