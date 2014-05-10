#ifndef GAUSS_SIEDEL
#define GAUSS_SIEDEL

#include "Vector.h"
#include "Symmetric.h"
#include 

template <class T>
class GaussSiedel
{
  public:
    GaussSiedel(double error): SolvingMethod( error ){}
    
    virtual Vector<T> operator()(const MatrixBase<T> A, const Vector<T> b)
    {
      if (mat.getSize() != vec.getSize())
        throw_SizeMismatchException(mat.getSize(), vec.getSize());
      
      if (!(mat.isDiagonallyDominant()))
        throw_NonDiagonallyDominantException();
      
      const int SIZE = vec.getSize();
      
      Vector<T> curr_X(SIZE), prev_X;
      
      for (int i = 0; i < SIZE; ++i)
        curr_X[i] = i;
      
      int iters = 0;
      
      do
      {
        prev_X = curr_X;
        
        for (int i = 0; i < SIZE; ++i)
        {
          T subt = 0;
          
          for (int j = 0; j < SIZE; ++j)
          {
            if (j != i)
              subt += mat[i][j]*curr_X[j];
          }
          
          curr_X[i] = (1.0/mat[i][i]) * (vec[i] - subt);
        }
        
        ++iters;
      } while ((curr_X - prev_X)%2 > ERROR_TOLERANCE && iters < MAX_ITERATIONS);
      std::cout << iters << " iterations" << std::endl;
      return curr_X;
    }
}

#endif