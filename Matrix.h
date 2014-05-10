/* Matrix.h
   Definition for a templated Matrix class
   Christopher Garlock
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <iostream>

//forward declaration for Symmetric
template <class T>
class Symmetric;

template <class T>
class Matrix: public virtual MatrixBase<T>
{
  private:
    Array<Array<T> > m_matrix;
    //unsigned int m_size;
  
  public:
    // Purpose: Constructor
    // Parameters: The size of one of the sides of the square matrix
    // Returns: nothing
    // Postconditions: a size x size matrix is created
    Matrix(unsigned int size);
    
    // Purpose: Copy Constructor
    // Parameters: The matrix to copy
    // Returns: nothing
    // Postconditions: A matrix identical to copy is created
    Matrix(const Matrix<T>& copy);
    
    // Purpose: Destructor
    // Parameters: none
    // Returns: nothing
    // Postconditions: Memory is deallocated and the object is destroyed
    virtual ~Matrix(){}
    
    // Purpose: accessor for size
    // Parameters: none
    // Returns: the size of one of the sides of the square matrix
    // Note: This really doesn't need to be defined but for purposes of recycling this class
    //            From another assignment, I just modified it so I wouldn't have to change
    //            as much code
    virtual unsigned int size() const{return MatrixBase<T>::m_size;} 
    
    // Purpose: Assignment operator
    // Parameters: Calling object, Matrix to be copied
    // Returns: A reference to the updated Matrix
    // Preconditions: assignment operator defined for type T
    // Postconditions: The object is identical to the matrix on the right hand side
    Matrix<T>& operator=(const Matrix<T>& rhs);
    
    Matrix<T>& operator=(const Symmetric<T>& rhs);
    
    bool operator==(const Matrix<T>& rhs)const;
    
    // Purpose: Allow the user to change the value of an index of the vector
    // Parameters: The index
    // Returns: a reference to the T at the specified index
    Array<T>& operator[](unsigned int i);
    
    // Purpose: Provide access to an index without allowing it to be changed
    // Parameters: The index
    // Returns: A read only reference to the index
    const Array<T>& operator[](unsigned int i) const;
    
    // Purpose: Subtraction operator
    // Parameters: Calling object, Matrix to subtract from the calling object
    // Returns: The updated Matrix
    // Preconditions: subtraction and assignment operators defined for type T
    Matrix<T> operator- (const Matrix<T>& rhs);
    
    // Purpose: Addition operator
    // Parameters: Calling object, Matrix to add to the calling object
    // Returns: The updated Matrix
    // Preconditions: addition and assignment operators defined for type T
    Matrix<T> operator+ (const Matrix<T>& rhs);
    
    // Purpose: Multiplication operator (with other matrices)
    // Parameters: Calling object, Matrix to multiply with the calling object
    // Returns: The updated Matrix
    // Preconditions: multiplication, addition and assignment operators defined for type T
    Matrix<T> operator* (const Matrix<T>& rhs);
    
    // Purpose: Multiplication operator (with a scalar)
    // Parameters: Calling object, scalar to multiply with the calling object
    // Returns: The updated Matrix
    // Preconditions: multiplication and assignment operators defined for type T
    Matrix<T> operator* (const T& rhs);
    
    // Purpose: Multiplication operator (with a vector)
    // Parameters: Calling object, Vector to multiply with the calling object
    // Returns: The updated Vector
    // Preconditions: multiplication and assignment operators defined for type T
    Vector<T> operator* (const Vector<T>& rhs);
    
    // Purpose: To swap two rows in a matrix
    // Parameters: the rows to swap
    // Returns: nothing
    // Preconditions: assignment operator defined for type T
    // Postconditions: the two specified rows are interchanged.
    void swapRow (unsigned int row1,  unsigned int row2);
    
    // Purpose: Finds the index of the the row with the maximum value in the
    //                specified column. Will only search rows below the index
    //                of the specified column
    // Parameters: Column to search
    // Returns: The index of the row
    // Preconditions: greater than operator defined for type T
    int findMaxRow(unsigned int col);
    
    // Purpose: To perform a row operation on the Matrix
    // Parameters:  the indexes of two rows and a multiplier
    // Returns: nothing
    // Preconditions: multiplication, addition, and assignment operators
    //                        defined for type T
    // Postconditions: row1 is multiplied by mult and added to row2
    void rowOp (unsigned int row1, T mult, unsigned int row2);
    
    // Purpose: Find the transpose of the matrix
    // Parameters:  none
    // Returns: The transposed matrix
    // Preconditions: assignment operator defined for type T
    Matrix<T> transpose() const;
    
    T& operator()(const unsigned int row, const unsigned int col) {return m_matrix[row][col];}
    
    const T& operator()(const unsigned int row, const unsigned int col)const {return m_matrix[row][col];}
    
    virtual ostream& print(ostream& os){return os<<*this;}
    
    virtual istream& read(istream& is){return is>>*this;}
    
     virtual Vector<T> solve(Vector<T> b);
    
    // Purpose: To output a matrix to an output stream
    // Parameters: lefthand operand should be an output stream and rhs should be a Matrix
    // Returns: the same stream it was passed  
    // Postconditions: Elements of the array are added to output stream
    friend ostream& operator<< (ostream& os, const Matrix<T>& myMatrix)
    {
       for (unsigned int i=0;i<myMatrix.size();i++)
       {
         for (unsigned int j=0;j<myMatrix.size();j++)
         {
           os<< setw(10) << myMatrix[i][j]<<' ';
         }
         os<<endl;
       }
       return os;
    }
    
    // Purpose: To read elements into a Matrix
    // Parameters: lefthand operand should be an input stream and rhs should be a Matrix
    // Returns: the same stream it was passed  
    // Postconditions: reads in a T and places it into the array
     friend istream& operator>> (istream& is, Matrix<T>& myMatrix)
    {
       for (unsigned int i=0;i<myMatrix.size();i++)
         for (unsigned int j=0;j<myMatrix.size();j++)
         {
           is>>myMatrix[i][j];
         }
       return is;
    }
};

#include "Matrix.hpp"
#endif