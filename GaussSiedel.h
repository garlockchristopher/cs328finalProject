#ifndef GAUSS_SIEDEL
#define GAUSS_SIEDEL

# include "Vector.h"
# include "MatrixBase.h"
# include "SolvingMethod.h"
# include <iostream>
template <class T>
class GaussSiedel: public virtual SolvingMethod<T>
{
  public:
    GaussSiedel(double error): SolvingMethod<T>( error, "Gauss Siedel" ){}
    
    virtual Vector<T> operator()(const MatrixBase<T>& A, const Vector<T>& b)
    {
      //reset iterations
      SolvingMethod<T>::iterations = 0;
      
      Vector<T> current(b.size());
      Vector<T> last(b.size());
      
      
      //build initial guess
      for (unsigned int i = 0; i < current.size(); i++)
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
        
        SolvingMethod<T>::iterations++;
      } while ((current - last).norm() > SolvingMethod<T>::errorTolerance);
      return current;
    }
};

#endif