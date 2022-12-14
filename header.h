// =================================================================
//
// File: header.h
// Author: Pedro Perez
// Description: This file contains the interface and implementation
//				of the Chronometer class, as well as the
//				implementation of some support functions. This class
//				is used to record the execution time of a program.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
// =================================================================

#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <sys/types.h>
#include <string>
#include <vector>

using namespace std;

vector<string> search(vector <string> datos1, string search1){

  vector<string> datosFiltrados;

  for(int i=0;i < datos1.size();i++){
    int found = datos1[i].find(search1);
    if(found!=datos1[i].npos){
      datosFiltrados.push_back(datos1[i]);
    }
  }
  return datosFiltrados;
}

vector<string> selectionSort(vector<int> &dayValue, vector <string> &datos1){

  vector <int> x = dayValue;
  vector <string> y = datos1;
  for (int i = 0; i < x.size()-1; i++) {
    for(int j = i + 1; j < x.size(); j++){
      if (x[j] < x[i]){
        swap(y[i],y[j]);
        swap(x[i],x[j]);
      }
    }
  }
  return y;
}

vector<int> date2dayvalue(vector<string> &dates){

  vector <int> dayValue;
  string tempDatum;
  int day,month;

  for(int i = 0; i<dates.size();i+=3){
    tempDatum = dates[i];
    stringstream cinDay(tempDatum);
    cinDay >> day;
    tempDatum = dates[i+1];
    stringstream cinMonth(tempDatum);
    cinMonth >> month;
    tempDatum = dates[i+2];
    int tempDayValue = ((month-1)*30)+day;
    dayValue.push_back(tempDayValue);
  }

  return dayValue;
}


vector<int> string2date(vector<string> &datePlusHour){

  //Obtiene el string de fecha y hora de la entrada de
  //datos

  vector<string> dates;
  string tempDatum;

    for(int i = 0;i<datePlusHour.size(); i+=4){
      //cout << datePlusHour[i] << "\t" <<datePlusHour[i+1] <<endl;
      tempDatum = datePlusHour[i];
      stringstream cinDate(tempDatum);
      while(getline(cinDate,tempDatum,'-')){
        dates.push_back(tempDatum);
      }
    }

    vector <int> dayValue = date2dayvalue(dates);
    return dayValue;
  }


  vector<int> hour2sec(vector<string> &hours){

    vector <int> secValue;
    string tempDatum;
    int hour,min;

    for(int i = 0; i<hours.size();i+=2){
      tempDatum = hours[i];
      stringstream cinHour(tempDatum);
      cinHour >> hour;
      tempDatum = hours[i+1];
      stringstream cinMin(tempDatum);
      cinMin >> min;
      int tempSecValue = (hour*3600)+min*60;
      secValue.push_back(tempSecValue);
    }

    return secValue;

  }


  vector<int> string2hour(vector<string> &datePlusHour){
    //Obtiene el string de fecha y hora de la entrada de
    //datos

    vector<string> hours;
    string tempDatum;

      for(int i = 1;i<datePlusHour.size(); i+=4){
        //cout << datePlusHour[i] << "\t" <<datePlusHour[i+1] <<endl;
        tempDatum = datePlusHour[i];
        stringstream cinHour(tempDatum);
        while(getline(cinHour,tempDatum,':')){
          hours.push_back(tempDatum);
        }
      }

      vector <int> secValue = hour2sec(hours);
      return secValue;
    }


  vector<int> date2secs(vector<string> &datePlusHour){
    vector <int> dayValue = string2date(datePlusHour);
    vector <int> secValue = string2hour(datePlusHour);
    vector <int> totalValue;
    for(int i = 0; i < dayValue.size(); i++){
      int secs = (dayValue[i]*3600*24) + (secValue[i]);
      totalValue.push_back(secs);
    }
    return totalValue;
  }


vector<int> line2string(vector<string> &data){

  //Desgloza la entrada de datos, asigna una posici??n
  //de un vector a cada string entre espacio y espacio

  vector<string> datePlusHour;

  for(int i=0; i<data.size(); i++){
    string tempLine = data[i];
    stringstream cinData(tempLine);
    while(getline(cinData,tempLine,' ')){
      datePlusHour.push_back(tempLine);
    }
  }

  vector <int> totalValue = date2secs(datePlusHour);
  return totalValue;

}

// =================================================================
// This class allows us to calculate the time that elapses between
// one execution line and another.
// =================================================================
class Chronometer {
private:
    timeval startTime;
    bool 	started;

public:
    Chronometer() :started(false) {}

    void start(){
    	started = true;
        gettimeofday(&startTime, NULL);
    }

    double stop(){
        timeval endTime;
        long seconds, useconds;
        double duration = -1;

        if (started) {
			gettimeofday(&endTime, NULL);

			seconds  = endTime.tv_sec  - startTime.tv_sec;
			useconds = endTime.tv_usec - startTime.tv_usec;

			duration = (seconds * 1000.0) + (useconds / 1000.0);
			started = false;
        }
		return duration;
    }
};

// =================================================================
// Swap the content of two localities (i, j) in array A.
//
// @param A, an array of T elements.
// @param i, an index in the array.
// @param j, an index in the array.
// =================================================================
template <class T>
void swap(T *A, int i, int j) {
	T aux = A[i];
	A[i] = A[j];
	A[j] = aux;
}

// =================================================================
// Swap the content of two localities (i, j) in vector v.
//
// @param v, a vector of T elements.
// @param i, an index in the vector.
// @param j, an index in the vector.
// =================================================================
template <class T>
void swap(vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

// =================================================================
// Converts the content of an array to a string.
//
// @param A, an array of T elements.
// @param size, the number of elements in the array.
// =================================================================
template <class T>
string arr2str(T *A, int size) {
	stringstream aux;

	aux << "[" << A[0];
	for (int i = 1; i < size; i++) {
		aux << ", " << A[i];
	}
	aux << "]";
	return aux.str();
}

// =================================================================
// Converts the content of a vector to a string.
//
// @param v, a vector of T elements.
// @param size, the number of elements in the array.
// =================================================================
template <class T>
string vec2str(const std::vector<T> &v) {
	stringstream aux;

	aux << "[" << v[0];
	for (int i = 1; i < v.size(); i++) {
		aux << ", " << v[i];
	}
	aux << "]";
	return aux.str();
}

#endif
