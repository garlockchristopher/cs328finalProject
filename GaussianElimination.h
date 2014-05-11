#ifndef GAUSSIAN_ELIMINATION_H
#define GAUSSIAN_ELIMINATION_H

#include "Symmetric.h"
#include "SolvingMethod.h"
#include "Matrix.h"
#include "Vector.h"

template <class T>
class GaussianElimination: public virtual SolvingMethod<T>
{
  public:
    GaussianElimination(double error = -1): SolvingMethod<T>( error, "Gaussian Elimination" ){}
    virtual Vector<T> operator()(const MatrixBase<T>& A, const Vector<T>& B)
    {
      Matrix<T> myMatrix(A.size());
      Vector<T> b = B;
      for(unsigned int i=0;i<myMatrix.size(); i++)
        for(unsigned int j=0;j<myMatrix.size(); j++)
          myMatrix[i][j] = A(i,j);
      //Forward elimination with partial pivoting
      for(unsigned int i=0;i<myMatrix.size()-1;i++) // need to eliminate things down to last column
      {
        //PIVOT
        unsigned int rowWithMax;
        rowWithMax = myMatrix.findMaxRow(i); //find row # with maximum element in col xzcV
        myMatrix.swapRow(i,rowWithMax);
        b.swapRow(i,rowWithMax);
        //Eliminate all the values below swapped row
        T mult;  //used as the multiplier in the row operations
        for (unsigned int j=myMatrix.size()-1;j>i;j--)
        {
          if(myMatrix[j][i] != 0)
          {
            mult = -(myMatrix[j][i]/myMatrix[i][i]);
            myMatrix.rowOp(i,mult,j);
            b.rowOp(i,mult,j);
            myMatrix[j][i] = 0;
            SolvingMethod<T>:: iterations++;
          }
        }
      }
  
      //now solve the matrix using back substitution
      Vector<T> solution(myMatrix.size());
      //start at bottom row, work up.
      for(int i = myMatrix.size() - 1; i>=0; i--) 
      {
        T subtractMe = 0;
        //gives 0 iterations at bottom row and one more for each row up after that
        for(int j = myMatrix.size() - 1 - i; j>0 ; j--)
          subtractMe = subtractMe + myMatrix[i][myMatrix.size()-j] * solution[solution.size()-j];
        solution[i] = (b[i] - subtractMe)/myMatrix[i][i];    
      }

      return solution;
    }
};
#endif