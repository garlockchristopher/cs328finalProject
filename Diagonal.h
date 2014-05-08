/* Diagonal.h
   Definition for a templated Diagonal matrix class
   Christopher Garlock
 */
 
 #ifndef DIAGONAL_H
#define DIAGONAL_H

#include "Vector.h"
#include "Matrix.h"
#include <stdexcept>
#include <iostream>

template <class T>
class Diagonal: public virtual MatrixBase<T>
{
  private:
    Array<T> m_matrix;
    const T M_ZERO;
    T m_zero;
  public:
    //constructor
    //pre: size != 0
    Diagonal(unsigned int size);
    
    //copy constructor
    Diagonal(const Diagonal<T>& copy);
    
    //destructor
    virtual ~Diagonal(){}
    
    //assignment operator
    //pre: size of lhs and rhs are equal
    Diagonal<T>& operator= (const Diagonal<T>& rhs);
    
    //bracket operator
    //pre: index is < the size of the diagonal
    //returns the element at position (index,index) of the diagonal matrix
    T& operator[] (const unsigned int index){return m_matrix[index];}
    
    //const version of above operator
    const T& operator[] (const unsigned int index) const {return m_matrix[index];}
    
    //subtraction operator
    //pre: both diagonals are of the same size
    //returns the diagonal resulting from the subtraction
    Diagonal<T> operator- (const Diagonal<T>& rhs) const;
    
    //addition operator
    //pre: both diagonals are of the same size
    //returns the diagonal resulting from the addition
    Diagonal<T> operator+ (const Diagonal<T>& rhs) const;
    
    // Purpose: Multiplication operator (with other matrices)
    // Parameters: Calling object, Diagonal to multiply with the calling object
    // Returns: The updated Diagonal
    // Preconditions: multiplication, addition and assignment operators defined for type T
    Diagonal<T> operator* (const Diagonal<T>& rhs);
    
    // Purpose: Multiplication operator (with a scalar)
    // Parameters: Calling object, scalar to multiply with the calling object
    // Returns: The updated Diagonal
    // Preconditions: multiplication and assignment operators defined for type T
    Diagonal<T> operator* (const T& rhs);
    
    // Purpose: Multiplication operator (with a vector)
    // Parameters: Calling object, Vector to multiply with the calling object
    // Returns: The resulting vector
    // Preconditions: multiplication, addition, and assignment operators defined for type T
    Vector<T> operator* (const Vector<T>& rhs);
    
    //parenthesis operator, returns a reference to position (row, col) of the matrix
    //note: if you try to change an element where row!=col, it will actually change m_zero
    //this will have no effect on the matrix and will not effect future return values from this function
    T& operator()(const unsigned int row, const unsigned int col);
    
    //const version of the operator above
    const T& operator()(const unsigned int row, const unsigned int col)const;
    
    //print function, used by base class MatrixBase to call this classes insertion operator
    virtual ostream& print(ostream& os){return os<<*this;}
    
    //read function, used by base class MatrixBase to call this classes extraction operator
    virtual istream& read(istream& is){return is>>*this;}
    
    //solves the equation Ax=b for x where A is the calling object
    //pre: size of b and calling object are the equal
    virtual Vector<T> solve(Vector<T> b);
    
    // Purpose: To output a diagonal to an output stream
    // Parameters: lefthand operand should be an output stream and rhs should be a Diagonal
    // Returns: the same stream it was passed  
    // Postconditions: Elements of the array are added to output stream
    friend ostream& operator<< (ostream& os, const Diagonal<T>& myDiag)
    {
       for (unsigned int i=0;i<myDiag.MatrixBase<T>::size();i++)
       {
         for (unsigned int j=0;j<myDiag.MatrixBase<T>::size();j++)
         {
           if(i==j)
             os<<myDiag[i]<<' ';
           else
             os<<"0 ";
         }
         os<<endl;
       }
       return os;
    }
    
    // extraction operator: reads in a diagonal from an input stream
    // pre: diagonal in input stream is same size as calling object and is a valid diagonal matrix
    // returns a reference to the input stream
    friend istream& operator>> (istream& is, Diagonal<T>& myDiag)
    {
      T input;
      for (unsigned int i=0; i<myDiag.MatrixBase<T>::size(); i++)
        for(unsigned int j=0; j<myDiag.MatrixBase<T>::size(); j++)
        {
          if(j != i)
          {
            is>>input;
            if (input != 0)
              throw ios_base::failure ("This input violates the properties of a diagonal matrix.");
          }
          else
            is>>myDiag(i,j);
        }
      return is;
    }
};

#include "Diagonal.hpp"

#endif
