// Matt Garlock
// CS328 Final Project
// Header File for SteepestDescent

# include "Vector.h"
# include "MatrixBase.h"
# include "SolvingMethod.h"

# include <stdexcept>
# ifndef STEEPESTDESCENT_H
# define STEEPESTDESCENT_H

template <typename T>
class SteepestDescent: public virtual SolvingMethod<T>
{
	public:
    SteepestDescent ( double error ): SolvingMethod<T> ( error ) {} 
    virtual Vector<T> operator()( const MatrixBase<T> & A, const Vector<T> & B )
    {
      if (A.size() != B.size())
        throw std:: length_error ( "Matrix and Vector must be the same size" );
      
      Vector<T> X ( B.size() );
      Vector<T> prevX ( B.size() );
      Vector<T> Diff ( B.size() );
      double alpha;
      SolvingMethod<T>:: iterations = 0;
      
      do
      {
        prevX = X;
        Diff = B - ( A * X );
        alpha = ( Diff * Diff ) / (( A * X ) * X );
        X = X + Diff * alpha;
        SolvingMethod<T>:: iterations++;
      } while ( (X - prevX).norm() > SolvingMethod<T>:: errorTolerance );
      
      return X;
    }
};

# endif