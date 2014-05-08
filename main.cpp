# include <iostream>
using namespace std;

# include "ABuilder.h"
# include "Symmetric.h"
# include "Vector.h"

int main()
{
  ABuilder<double> myBuilder;
  Symmetric<double> pleaseWork = myBuilder ( 4 );
  BBuilder<double> myBBuilder;
  Vector<double> pleaseAlsoWork = myBBuilder ( 4 );
  cout << pleaseWork << endl;
  cout << pleaseAlsoWork << endl;
}