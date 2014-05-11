/*
Filename: MatrixBase.h
Author: Chris Garlock
Purpose: An abstract base class designed to be the parent of several different types of matrices
*/

# include <istream>
# include <ostream>
# include <iostream>
# include "Vector.h"

#ifndef MATRIXBASE_H
#define MATRIXBASE_H

template <class T>
class MatrixBase
{
  protected:
    unsigned int m_size;
    
  public:
    //virtual accessor function for size
    virtual unsigned int size() const{return m_size;}
    
    //pure virtual () operator, returns the value of the matrix at the specified row and column
    virtual T& operator()(const unsigned int row, const unsigned int col) = 0;
    
    //const version of above function
    virtual const T& operator()(const unsigned int row, const unsigned int col)const = 0;
    
    //pure virtual * operator, used for Matrix - Vector multiplication.
    virtual Vector<T> operator* ( const Vector<T> & rhs ) const = 0;
    
    //pure virtual print function - should be used to call the insertion operator
    virtual ostream& print(ostream& os) = 0;
    
     //pure virtual read function - should be used to call the extraction operator
    virtual istream& read(istream& is) = 0;
    
    //pure virtual function that gives x for the equation Ax=b when provided b.
    virtual Vector<T> solve(Vector<T> b) = 0;
    
    //virtual destructor
    virtual ~MatrixBase(){}
    
    //returns true if a matrix is diagonallyDominant.  Defaults to false if the 
    //function is not overwritten by the derived class
    virtual bool diagonallyDominant()const{return false;}
};

template <class T>
std::ostream& operator<<(std::ostream& os, MatrixBase<T>& base)
{
  return base.print(os);
}

template <class T>
std::istream& operator>>(std::istream& is, MatrixBase<T>& base)
{
  return base.read(is);
}
#endif