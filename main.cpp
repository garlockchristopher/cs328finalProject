# include <iostream>
# include "ABuilder.h"
# include "BBuilder.h"
# include "Symmetric.h"
# include "SteepestDescent.h"
# include "GaussSiedel.h"
# include "Vector.h"
# include "GaussianElimination.h"

using namespace std;

template <class T>
Matrix<T> solutionMatrix(Vector<T> x, TopFunc<T> tFunc, BotFunc<T> bFunc, LeftFunc<T> lFunc, RightFunc<T> rFunc);

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
  Vector<double> b = myBBuilder ( 4, tFunc, bFunc, lFunc, rFunc );
  
  //Fill a Vector with solving methods
  
  SolvingMethod<double> * methods[2];
  methods[0] = new GaussianElimination<double>;
  methods[1] = new GaussSiedel<double>( .00001 );
  
  for ( unsigned int i = 0; i < 2; i++ )
  {
    Vector<double> x = methods[i] -> operator()(A, b);
    
    //print results  
    cout << "\nA: \n" << A << endl;
    cout << "\nb: \n" << b << endl;  
    cout << "\nx: \n" << x << endl;
    Matrix<double> solution = solutionMatrix(x, tFunc, bFunc, lFunc, rFunc);
    cout << "\n Solution Matrix for the Gaussian Elimination Method: \n" << solution << endl;
  }
}

template <class T>
Matrix<T> solutionMatrix(Vector<T> x, TopFunc<T> tFunc, BotFunc<T> bFunc, LeftFunc<T> lFunc, RightFunc<T> rFunc)
{
  unsigned int size = sqrt(x.size()) + 2;
  Matrix<T> solution(size);
  unsigned int iterator = 0;
  for (unsigned int i = size; i >= 1; i--) //start at bottom row and work up
  {
    for (unsigned int j = 0; j < size; j++) //start at left column and work right
	{
	  if(i - 1 == 0) // top Row
	    solution(i - 1, j) = tFunc(static_cast<T>(j)/static_cast<T>(size-1));
	  else if(i == size) //bottom Row
	    solution(i - 1, j) = bFunc(static_cast<T>(j)/static_cast<T>(size-1));
	  else if(j == size - 1) //right column
	    solution(i - 1, j) = rFunc(static_cast<T>(i - 1)/static_cast<T>(size-1));
	  else if(j == 0) //left column
	    solution(i - 1, j) = lFunc(static_cast<T>(i - 1)/static_cast<T>(size-1));
	  else //pull from x
	    solution(i - 1, j) = x[iterator++];
	}
  }
  return solution;
}