#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include "config.h"

#define CLEAN_HASH for(int i = 0; i < _NUM_CITIES_; i++) for(int j = 0; j < _NUM_TYPES_; j++) OBJ_POS(0,0).listPlaces.clear()
#define int_vec std::vector<Places> 
#define OBJ_POS(c,t) cities[c].types[t]

using namespace std;

class SMV_lvl1{


	private:	
	
	struct Places{ int type; int _id; string name; string inf; string location; string id_maps; float smv_rate; float maps_rate;} ; //STRUCT OD PLACES
	struct Types{ std::list<Places> listPlaces;  int _id; bool empty;} ;	//STRUCT OF TYPES -> places 
	struct City{ Types types[_NUM_TYPES_]; int _id; string name; } ;//STRUCT OF CITIES
	struct City cities[_NUM_CITIES_];	//HASH OF CITIES
	struct vector_process{ Places vector_list; bool process; } ;	//STRUCT OF VECTOR BY REPLY 
		
	public:

 	void init() { startEngine(); }	

	private:  
	
 	/** 
	* THIS FUNCTION CREATE THE HASH OF CITIES AND THE HASH OF TYPES
	**/	
	void startEngine(){
		
		
		CLEAN_HASH;
		int command = 1;
		Places *p = new Places;
		do{
			readySQL(p);			
			OBJ_POS(0,p->type).listPlaces.insert(OBJ_POS(0,p->type).listPlaces.end(), *p);
			
			cout << "SAVED!" << endl;
			delete p;
			p = new Places;
			cout << "DO YOU WANNA MAKE ANOTHER INSERTION? ";
			cin >> command;
		
		}while(command != 0);
		
		int x = 1;
		
		for(std::list<Places>::iterator iter = OBJ_POS(0,0).listPlaces.begin(); 
		    iter != OBJ_POS(0,0).listPlaces.end(); iter++,x++)
		{
    			cout << x << ") Place:\n" 
					<< "Type: " << iter->type
					<< "Name: " << iter->name
					<< "Inf: " << iter->inf
					<< "Location: " << iter->location
					<< "Id Maps: " << iter->id_maps
					<< "SMV Rate: " << iter->smv_rate
					<< "Maps Rate: " << iter->maps_rate << endl << endl;
		}
		
		request_OP1(0,0,1);


	}

	/**
	* THIS FUCTION READY THE SQL AND RETURN A POINTER WITH THE ELEMENTS OF TYPE "PLACE"
	**/
	Places * readySQL(Places *pplace){
		cout << "1";

		cin >> pplace->type;
		cin >> pplace->name;
		cin >> pplace->inf;
		cin >> pplace->location;
		cin >> pplace->id_maps;
		cin >> pplace->smv_rate;
		cin >> pplace->maps_rate;
		return pplace;
	}
		
	/**
	* THIS FUNCTION PROCESS REQUESTS BY USERS AND CREATE VECTOR WHITH PLACES
	**/
	void request_OP1(int city, int type, int position){
		
			/** PUT MEMBERS OF LIST INSIDE OF VECTOR **/
		int length_list = OBJ_POS(city,type).listPlaces.size();
		
		struct vector_process vector_request[length_list];
		int i = 0; //LOOP
		for(std::list<Places>::iterator iter = OBJ_POS(0,0).listPlaces.begin(); 
		    iter != OBJ_POS(0,0).listPlaces.end(); iter++,i++)
		{
    			vector_request[i].vector_list = *iter;
			vector_request[i].process = true;
		
		}
		quickSort( vector_request, 0, length_list - 1); // SORT THE VECTOR
			/** RETURN "N" PLACES BY ORDER OF MAPS_RATE **/
		int loop = 0;
		if ( ( _PACKAGE_RESPONSE_ * position ) <= length_list ){
			for(int i = (length_list - 1)/position; loop < _PACKAGE_RESPONSE_; i--, loop++){
			
				cout << "VECTOR: " << vector_request[i].vector_list.maps_rate << endl;
			}

		}else if ( position < 2 ){	//CASES THAT THE VECTOR IS SMALLER THEN REQUEST 
			for(int i = (length_list - 1); i >= 0; i--){
			
				cout << "VECTOR 2: " << vector_request[i].vector_list.maps_rate << endl;
			}

		}
		
			
				
			/** VERIFY IF EXISTS A PLACES THAT THE USER DON'T WANT AND MAKE A LOGICAL EXCLUSION **/
		//for(int i = 0; i < nnon_places; i++) for(int j = 0; j < length_list; j++) if(non_places[i] == vector_list[j])
		cout << "\nLENGTH: " << length_list << endl;

	}

	/**
	* THIS FUNCTION SORT THE RESPONSE VECTOR BY MAPS_RATE
	**/
	void quickSort(vector_process *valor, int esquerda, int direita)
	{
	    int i, j;
	    float x;
	    vector_process *y = new vector_process;
	    i = esquerda;
	    j = direita;
	    x = valor[(esquerda + direita) / 2].vector_list.maps_rate;

	    while(i <= j)
	    {
		while(valor[i].vector_list.maps_rate < x && i < direita)
		{
		    i++;
		}
		while(valor[j].vector_list.maps_rate > x && j > esquerda)
		{
		    j--;
		}
		if(i <= j)
		{
		    *y = valor[i];
		    valor[i] = valor[j];
		    valor[j] = *y;
		    i++;
		    j--;
		    delete y;
		    y = new vector_process;
		}
	    }
	    if(j > esquerda)
	    {
		quickSort(valor, esquerda, j);
	    }
	    if(i < direita)
	    {
		quickSort(valor,  i, direita);
	    }
	}
	


};
