// Matt Garlock
// CS328 Final Project
// SolvingMethod header file


# include "MatrixBase.h"
# include "Vector.h"

# ifndef SOLVINGMETHOD_H
# define SOLVINGMETHOD_H

template <typename T>
class SolvingMethod
{
  protected:
    double errorTolerance;
    string name;
    unsigned int iterations;
    
  public:
    //constructor
    SolvingMethod ( double error, string name ): errorTolerance(error), name(name), iterations(0) {}
    
    //pure virtual operator() takes a matrix and a vector of the same size, and solves for x using the
    //method of the derived class
    virtual Vector<T> operator() ( const MatrixBase<T> & A, const Vector<T> & X ) = 0;
    
    //returns the name of the method being used
    string getName() const { return name; }
    
    //returns the number of iterations used to calculate the last solution given.
    unsigned int getIterations () const { return iterations; }
    
    //sets errorTolerance to be equal to error
    void setTolerance(double error) {errorTolerance = error;}
};

# endif