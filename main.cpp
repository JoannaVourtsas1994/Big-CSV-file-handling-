#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <omp.h>
using namespace std;
float ConvertToCelsius(float);
float ConvertToKelvin(float);

int main ()
{

ifstream MainFile; //Open csv file 
MainFile.open("Bigfile.csv"); //Main File 
if(!MainFile.is_open()) 
	cout << "Error on opening file"<<endl;

//the 2 conversion files 
fstream CelFile("Celcius.csv",ios::in| ios::out | ios::app);
if(!CelFile.is_open()) 
	cout << "Error on opening file"<<endl;

fstream KelFile("Kelvin.csv",ios::in| ios::out | ios::app);
if(!KelFile.is_open()) 
	cout << "Error on opening file"<<endl;




//omp_set_num_threads(2);
#pragma omp parallel sections num_threads(2)
{

#pragma omp section 
  {  string tempt;
	//ifstream MainFile2; //Open csv file 
	//MainFile2.open("Bigfile2.csv"); //Main File 
	//if(!MainFile2.is_open()) 
	//cout << "Error on opening file"<<endl;

	while(!MainFile.eof()){
	getline(MainFile,tempt);
	istringstream ss(tempt);

	while (getline (ss,tempt,','))//ignore , 
	{
	int n= stoi(tempt);

	float result = ConvertToKelvin(n);

	KelFile << result<<",";//insert , to go to next tab 
	}
	KelFile <<endl;
	}	
  
  }


#pragma omp section
  { string tempts;
	ifstream MainFile; //Open csv file 
	MainFile.open("Bigfile.csv"); //Main File 
	if(!MainFile.is_open()) 
	cout << "Error on opening file"<<endl;

	while(!MainFile.eof()){
	getline(MainFile,tempts);
	istringstream ss(tempts);

	while (getline (ss,tempts,','))//ignore , 
	{
	int n= stoi(tempts);

	float results = ConvertToCelsius(n);

	CelFile << results<<",";//insert , to go to next tab 
	}
	CelFile <<endl;
	}	

  }



}
return 0;
}


float ConvertToCelsius( float input)
{

float val;
val= (input-32)*(5.0/9);

return val;
}

float ConvertToKelvin( float input)
{

float val;
val= (input-32)*(5.0/9)+273.15;

return val;
}

