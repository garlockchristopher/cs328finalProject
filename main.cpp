# include <iostream>
using namespace std;

# include "ABuilder.h"
#include "BBuilder.h"
# include "Symmetric.h"
# include "Vector.h"
# include "GaussianElimination.h"

template <class T>
Matrix<T> solutionMatrix(Vector<T> x, TopFunc tFunc, BotFunc bFunc, LeftFunc lFunc, RightFunc, rFunc);

int main()
{
  //set up A
  ABuilder<double> myBuilder;
  Symmetric<double> A = myBuilder ( 4 );
  
  //set up B
  BBuilder<double> myBBuilder;
  BotFunc<double> bFunc;
  LeftFunc<double> lFunc;
  RightFunc<double> rFunc;
  TopFunc<double> tFunc;
  
  //solve Ax=b for x
  Vector<double> b = myBBuilder ( 4, tFunc, bFunc, lFunc, rFunc );
  GaussianElimination<double> GEsolver;
  Vector<double> x = GEsolver(A, b);
  
  //print results  
  cout << "\nA: \n" << A << endl;
  cout << "\nb: \n" << b << endl;  
  cout<< "\nx: \n" << x << endl;
}

template <class T>
Matrix<T> solutionMatrix(Vector<T> x, TopFunc tFunc, BotFunc bFunc, LeftFunc lFunc, RightFunc, rFunc)
{
  unsigned int size = sqrt(x.size()) + 2;
  Matrix<T> solution(size);
  for (unsinged int i = 0; i < size; i++)
  {
    for (unsinged int j = 0; j < size; j++)
	{
	  if(i == size - 1) // top Row
	    solution(i, j) = TopFunc(static_cast<T>(j)/static_cast<T>(size));
	  else if(i == 0) //bottom Row
	    solution(i, j) = botFunc(static_cast<T>(j)/static_cast<T>(size));
	}
  }  
}