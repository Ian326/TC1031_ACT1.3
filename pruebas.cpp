#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

vector<string> selectionSort(vector <int> &dayValue, vector <string> &datos1){

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
      cout << hours[i] << endl;
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

  //Desgloza la entrada de datos, asigna una posición
  //de un vector a cada string entre espacio y espacio

  vector<string> datePlusHour;

  for(int i=1; i<data.size(); i++){
    string tempLine = data[i];
    stringstream cinData(tempLine);
    while(getline(cinData,tempLine,' ')){
      datePlusHour.push_back(tempLine);
    }
  }

  vector <int> totalValue = date2secs(datePlusHour);
  return totalValue;

}

int main(){
  vector<string> data;
  string a = "13-09-20 06:41 M 2ARR0";
  string b = "30-05-20 16:11 R 1FJQ6";
  string c = "27-11-20 09:00 M 2FRN7";
  string d = "31-12-20 09:00 M 2FRN7";
  data.push_back(a);
  data.push_back(b);
  data.push_back(c);
  data.push_back(d);

  line2string(data);
  vector <int> dayValue = line2string(data);
  for(int i = 0; i<dayValue.size(); i++){
    cout << dayValue[i] << endl;
  }

}
