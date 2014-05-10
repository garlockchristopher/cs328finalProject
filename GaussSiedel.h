#ifndef GAUSS_SIEDEL
#define GAUSS_SIEDEL

#include "Vector.h"
#include "Symmetric.h"
#include 

template <class T>
class GaussSiedel: public virtual SolvingMethod
{
  public:
    GaussSiedel(double error): SolvingMethod( error ){}
    
    virtual Vector<T> operator()(const MatrixBase<T> A, const Vector<T> b)
    {
      if(!A.diagonallyDominant())
        throw "Matrix must be diagonallyDominant to use the GaussSiedel Method.";
      
      //reset iterations
      SolvingMethod::iterations = 0;
      
      Vector<T> current(b.size());
      Vector<T> last(b.size());
      
      //build initial guess
      for (int i = 0; i < current.size(); i++)
        current[i] = 0;
      
      do
      {
        last = current;
        for (unsigned int i = 0; i < current.size(); ++i)
        {
          T subtractMe = 0;
          for (unsigned int j = 0; j < current.size(); ++j)
          {
            if (j != i) //not on diagonal
              subtractMe += A(i,j) * current[j];
          }
          current[i] = (1.0/A(i,i)) * (b[i] - subtractMe);
        }
        
        SolvingMethod::iterations++;
      } while ((current - last).norm() > SolvingMethod<T>::errorTolerance);
      return current;
    }
}

#endif