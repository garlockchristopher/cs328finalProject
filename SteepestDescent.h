// Matt Garlock
// CS328 Final Project
// Header File for SteepestDescent

# include "Vector.h"
# include "MatrixBase.h"
# include "SolvingMethod.h"
# include <iostream>
using namespace std;

# include <stdexcept>
# ifndef STEEPESTDESCENT_H
# define STEEPESTDESCENT_H

template <typename T>
class SteepestDescent: public virtual SolvingMethod<T>
{
	public:
    SteepestDescent ( double error ): SolvingMethod<T> ( error, "Steepest Descent" ) {} 
    virtual Vector<T> operator()( const MatrixBase<T> & A, const Vector<T> & B )
    {
      if (A.size() != B.size())
        throw std:: length_error ( "Matrix and Vector must be the same size" );
      
      Vector<T> X ( B.size() );
      for ( unsigned int i = 0; i < B.size(); i++ )
        X[i] = 1;
      Vector<T> prevX ( B.size() );
      Vector<T> Diff ( B.size() );
      T alpha;
      SolvingMethod<T>:: iterations = 0;
      
      do
      {
        prevX = X;
        Diff = B - ( A * X );
        alpha = ( Diff * Diff ) / (( A * X ) * X );
        X = X + ( Diff * alpha );
        SolvingMethod<T>:: iterations++;
      } while ( (X - prevX ).norm() > SolvingMethod<T>:: errorTolerance );
      
      return X;
    }
};

# endif