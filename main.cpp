/*
main.cpp
used to test all of the classes included below
Matthew and Christopher Garlock
*/
# include <iostream>
# include "ABuilder.h"
# include "BBuilder.h"
# include "Symmetric.h"
# include "SteepestDescent.h"
# include "GaussSiedel.h"
# include "Vector.h"
# include "GaussianElimination.h"

using namespace std;

//purpose: given the vector x from the equation Ax=b, this function will return a matrix filled with
//         the solution at every calculated point.          
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
  SolvingMethod<double> * methods[3];
  GaussianElimination<double> gElim;
  GaussSiedel<double> gSied(.0001);
  SteepestDescent<double> sDescent(.0001);
  methods[0] = &gElim;
  methods[1] = &gSied;
  methods[2] = &sDescent;
  
  cout << "=====================================================================" << endl;
  cout << "=======================Begin tests for n = 4=========================" << endl;
  cout << "=====================================================================" << endl;
  cout << "A: \n" << A << endl;
  cout << "b: \n" << b << endl; 
  
  cout << "\n********************************************************************************" <<endl;
  cout << "*********Printing Results for calculations with error tolerance = .0001*********" << endl;
  cout << "********************************************************************************"<<endl;
  for ( unsigned int i = 0; i <= 2; i++ )
  {
    methods[i] -> setTolerance(.0001);
    Vector<double> x = methods[i] -> operator()(A, b);
    Matrix<double> solution = solutionMatrix(x, tFunc, bFunc, lFunc, rFunc);
    cout << "\n Solution Matrix for the " << methods[i] -> getName() << " Method: \n" << solution << endl;
    cout << "Number of iterations: " << methods[i] -> getIterations() << endl;
  }
  
  cout << "\n*********************************************************************************" <<endl;
  cout << "*********Printing Results for calculations with error tolerance = .00001*********" << endl;
  cout << "*********************************************************************************" <<endl;
  for ( unsigned int i = 0; i <= 2; i++ )
  {
    methods[i] -> setTolerance(.00001);
    Vector<double> x = methods[i] -> operator()(A, b);
    Matrix<double> solution = solutionMatrix(x, tFunc, bFunc, lFunc, rFunc);
    cout << "\n Solution Matrix for the " << methods[i] -> getName() << " Method: \n" << solution << endl;
    cout << "Number of iterations: " << methods[i] -> getIterations() << endl;
  }
  
  cout << "\n**********************************************************************************" <<endl;
  cout << "*********Printing Results for calculations with error tolerance = .000001*********" << endl;
  cout << "**********************************************************************************" <<endl;
  for ( unsigned int i = 0; i <= 2; i++ )
  {
    methods[i] -> setTolerance(.000001);
    Vector<double> x = methods[i] -> operator()(A, b);
    Matrix<double> solution = solutionMatrix(x, tFunc, bFunc, lFunc, rFunc);
    cout << "\n Solution Matrix for the " << methods[i] -> getName() << " Method: \n" << solution << endl;
    cout << "Number of iterations: " << methods[i] -> getIterations() << endl;
  }
  
  cout << "=====================================================================" << endl;
  cout << "=======================Begin tests for n = 6=========================" << endl;
  cout << "=====================================================================" << endl;
  
  b = myBBuilder ( 6, tFunc, bFunc, lFunc, rFunc );
  Symmetric<double> A2 = myBuilder (6);
  
  cout << "\n********************************************************************************" <<endl;
  cout << "*********Printing Results for calculations with error tolerance = .0001*********" << endl;
  cout << "********************************************************************************" <<endl;
  for ( unsigned int i = 0; i <= 2; i++ )
  {
    methods[i] -> setTolerance(.0001);
    Vector<double> x = methods[i] -> operator()(A2, b);
    Matrix<double> solution = solutionMatrix(x, tFunc, bFunc, lFunc, rFunc);
    cout << "\n Solution Matrix for the " << methods[i] -> getName() << " Method: \n" << solution << endl;
    cout << "Number of iterations: " << methods[i] -> getIterations() << endl;
  }
  
  cout << "\n*********************************************************************************" <<endl;
  cout << "*********Printing Results for calculations with error tolerance = .00001*********" << endl;
  cout << "*********************************************************************************" <<endl;
  for ( unsigned int i = 0; i <= 2; i++ )
  {
    methods[i] -> setTolerance(.00001);
    Vector<double> x = methods[i] -> operator()(A2, b);
    Matrix<double> solution = solutionMatrix(x, tFunc, bFunc, lFunc, rFunc);
    cout << "\n Solution Matrix for the " << methods[i] -> getName() << " Method: \n" << solution << endl;
    cout << "Number of iterations: " << methods[i] -> getIterations() << endl;
  }
  
  cout << "\n**********************************************************************************" <<endl;
  cout << "*********Printing Results for calculations with error tolerance = .000001*********" << endl;
  cout << "**********************************************************************************" <<endl;
  for ( unsigned int i = 0; i <= 2; i++ )
  {
    methods[i] -> setTolerance(.000001);
    Vector<double> x = methods[i] -> operator()(A2, b);
    Matrix<double> solution = solutionMatrix(x, tFunc, bFunc, lFunc, rFunc);
    cout << "\n Solution Matrix for the " << methods[i] -> getName() << " Method: \n" << solution << endl;
    cout << "Number of iterations: " << methods[i] -> getIterations() << endl;
  }
  
  cout << "=====================================================================" << endl;
  cout << "=======================Begin tests for n = 8=========================" << endl;
  cout << "=====================================================================" << endl;
  b = myBBuilder ( 8, tFunc, bFunc, lFunc, rFunc );
  Symmetric<double> A3 = myBuilder (8);
  
  cout << "\n********************************************************************************" <<endl;
  cout << "*********Printing Results for calculations with error tolerance = .0001*********" << endl;
  cout << "********************************************************************************" <<endl;
  for ( unsigned int i = 0; i <= 2; i++ )
  {
    methods[i] -> setTolerance(.0001);
    Vector<double> x = methods[i] -> operator()(A3, b);
    Matrix<double> solution = solutionMatrix(x, tFunc, bFunc, lFunc, rFunc);
    cout << "\n Solution Matrix for the " << methods[i] -> getName() << " Method: \n" << solution << endl;
    cout << "Number of iterations: " << methods[i] -> getIterations() << endl;
  }
  
  cout << "\n*********************************************************************************" <<endl;
  cout << "*********Printing Results for calculations with error tolerance = .00001*********" << endl;
  cout << "*********************************************************************************" <<endl;
  for ( unsigned int i = 0; i <= 2; i++ )
  {
    methods[i] -> setTolerance(.00001);
    Vector<double> x = methods[i] -> operator()(A3, b);
    Matrix<double> solution = solutionMatrix(x, tFunc, bFunc, lFunc, rFunc);
    cout << "\n Solution Matrix for the " << methods[i] -> getName() << " Method: \n" << solution << endl;
    cout << "Number of iterations: " << methods[i] -> getIterations() << endl;
  }
  
  cout << "\n**********************************************************************************" <<endl;
  cout << "*********Printing Results for calculations with error tolerance = .000001*********" << endl;
  cout << "**********************************************************************************" <<endl;
  for ( unsigned int i = 0; i <= 2; i++ )
  {
    methods[i] -> setTolerance(.000001);
    Vector<double> x = methods[i] -> operator()(A3, b);
    Matrix<double> solution = solutionMatrix(x, tFunc, bFunc, lFunc, rFunc);
    cout << "\n Solution Matrix for the " << methods[i] -> getName() << " Method: \n" << solution << endl;
    cout << "Number of iterations: " << methods[i] -> getIterations() << endl;
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