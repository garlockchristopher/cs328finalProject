# include <iostream>
using namespace std;

# include "ABuilder.h"
#include "BBuilder.h"
# include "Symmetric.h"
# include "Vector.h"


int main()
{
  //set up A
  ABuilder<double> myBuilder;
  Symmetric<double> pleaseWork = myBuilder ( 4 );
  //set up B
  BBuilder<double> myBBuilder;
  BotFunc<double> bFunc;
  LeftFunc<double> lFunc;
  RightFunc<double> rFunc;
  TopFunc<double> tFunc;
  Vector<double> pleaseAlsoWork = myBBuilder ( 4, tFunc, bFunc, lFunc, rFunc );
  cout << pleaseWork << endl;
  cout << pleaseAlsoWork << endl;
}