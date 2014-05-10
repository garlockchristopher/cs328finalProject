/* Symmetric.h
   Definition for a templated Symmetrical matrix class
   Christopher Garlock
 */
 
#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include "Vector.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Matrix.h"

const double ERROR_THRESHOLD = .0001;

template <class T>
class Symmetric: public virtual MatrixBase<T>
{
  private:
    Array<Array<T> > m_matrix;
  public:
    //constructor
    //pre: size != 0
    Symmetric(unsigned int size);
    
    //copy constructor
    Symmetric(const Symmetric<T>& copy);
    
    //destructor
    virtual ~Symmetric(){}
    
    //assignment operator
    //pre: size of lhs and rhs are equal
    Symmetric<T>& operator= (const Symmetric<T>& rhs);
    
    //bracket operator
    //pre: index is < the size of the diagonal
    //returns the array at row index
    Array<T>& operator[] (const unsigned int index);
    
    //const version of above operator
    const Array<T>& operator[] (const unsigned int index) const;
    
    //subtraction operator
    //pre: both symmetrics are of the same size
    //returns the symmetric resulting from the subtraction
    Symmetric<T> operator- (const Symmetric<T>& rhs) const;
    
    //addition operator
    //pre: both symmetrics are of the same size
    //returns the symmetric resulting from the addition
    Symmetric<T> operator+ (const Symmetric<T>& rhs) const;
    
    // Purpose: Multiplication operator (with other matrices)
    // Parameters: Calling object, Symmetric to multiply with the calling object
    // Returns: The updated Symmetric
    // Preconditions: multiplication, addition and assignment operators defined for type T
    Symmetric<T> operator* (const Symmetric<T>& rhs) const;
    
    // Purpose: Multiplication operator (with a scalar)
    // Parameters: Calling object, scalar to multiply with the calling object
    // Returns: The updated Symmetric
    // Preconditions: multiplication and assignment operators defined for type T
    Symmetric<T> operator* (const T& rhs);
    
    // Purpose: Multiplication operator (with a vector)
    // Parameters: Calling object, Vector to multiply with the calling object
    // Returns: The updated Symmetric
    // Preconditions: multiplication and assignment operators defined for type T
    Vector<T> operator* (const Vector<T>& rhs) const;
    
    //parenthesis operator, returns a reference to position (row, col) of the matrix
    T& operator()(const unsigned int row, const unsigned int col);
    
    //const version of the operator above
    const T& operator()(const unsigned int row, const unsigned int col)const;
    
    //print function, used by base class MatrixBase to call this classes insertion operator
    virtual ostream& print(ostream& os){return os<<*this;}
    
    //read function, used by base class MatrixBase to call this classes extraction operator
    virtual istream& read(istream& is){return is>>*this;}
    
    //checks to see if the symmetric matrix is diagonally dominant, if it is returns true
    //otherwise returns false
    bool diagonallyDominant();
    
    //solves the equation Ax=b for x where A is the calling object
    //pre: size of b and calling object are the equal
    virtual Vector<T> solve(Vector<T> b);
    
    // Purpose: To output a matrix to an output stream
    // Parameters: lefthand operand should be an output stream and rhs should be a Symmetric
    // Returns: the same stream it was passed  
    // Postconditions: Elements of the array are added to output stream
    friend ostream& operator<< (ostream& os, const Symmetric<T>& mySym)
    {
       for (unsigned int i=0;i<mySym.MatrixBase<T>::size();i++)
       {
         for (unsigned int j=0;j<mySym.MatrixBase<T>::size();j++)
         {
           if (j>i)
             os<<setw(5)<<mySym[j][i]<<' ';
           else
             os<<setw(5)<<mySym[i][j]<<' ';
         }
         os<<endl;
       }
       return os;
    }
    
    
    // extraction operator: reads in a Symmetric from an input stream
    // pre: Symmetric in input stream is same size as calling object and is a valid Symmetric matrix
    // returns a reference to the input stream
    friend istream& operator>> (istream& is, Symmetric<T>& mySym)
    {
      for(unsigned int i=0; i<mySym.MatrixBase<T>::size(); i++)
        for (unsigned int j=0; j<mySym.MatrixBase<T>::size(); j++)
          is>>mySym(i,j);
      return is;
    }
};
#include "Symmetric.hpp"

#endif
