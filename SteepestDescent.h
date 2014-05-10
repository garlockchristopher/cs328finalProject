// Matt Garlock
// CS328 Final Project
// Header File for SteepestDescent

# include <stdexcept>
# ifndef STEEPESTDESCENT_H
# define STEEPESTDESCENT_H

template <typename T>
class SteepestDescent: public SolvingMethod
{
	public:
    SteepestDescent ( double error ): SolvingMethod ( error ) {} 
    virtual Vector<T> operator()( const MatrixBase<T> & A, const Vector<T> B )
    {
      if (mat.getSize() != vec.getSize())
        throw std:: length_error ( "Matrix and Vector must be the same size" );
      
      Vector<T> X ( B.size() );
      Vector<T> prevX ( B.size() );
      Vector<T> Diff ( B.size() );
      double alpha;
      iterations = 0;
      
      do
      {
      
        prevX = X;
        Diff = B - ( A * X );
        alpha = ( Diff * Diff ) / (( A * X ) * X );
        X = X + Diff * alpha;
        iterations++;
        
      } while ( (X - prevX).norm() > errorTolerance )
      
      return X;
    }
};