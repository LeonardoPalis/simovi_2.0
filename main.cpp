#include <iostream>
#include <stdio.h>
#include <string>
#include "config.h"
#include "SMV_lvl1.cpp"

using namespace std;

struct City{ int _id; string name;}city; // STRUCT OF THE CITIES

int main(void){
	
 	
	SMV_lvl1 *ba = new SMV_lvl1;
	ba->init();
	//cout << "THE CITY IS: "<< city._id;
	
	

	return 0;

}
