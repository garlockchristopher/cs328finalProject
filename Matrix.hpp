/* Matrix.hpp
   Implementation for a templated Matrix class
   Christopher Garlock
 */

// Purpose: Constructor
// Parameters: The size of one of the sides of the square matrix
// Returns: nothing
// Postconditions: a size x size matrix is created
template<class T>
Matrix<T>:: Matrix(unsigned int size)
{
  Array<T> temp(size);
  for(unsigned int i=0;i<size;i++)
    m_matrix.push_back(temp);
  MatrixBase<T>::m_size = size;
}

// Purpose: Copy Constructor
// Parameters: The matrix to copy
// Returns: nothing
// Postconditions: A matrix identical to copy is created
template<class T>
Matrix<T>:: Matrix(const Matrix<T>& copy)
{
  Array<T> temp(copy.size());
  for(unsigned int i=0;i<copy.size();i++)
    m_matrix.push_back(temp);
  MatrixBase<T>::m_size = copy.size();
  *this = copy;
}

// Purpose: Assignment operator
// Parameters: Calling object, Matrix to be copied
// Returns: A reference to the updated Matrix
// Preconditions: assignment operator defined for type T
// Postconditions: The object is identical to the matrix on the right hand side
template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
  if(size() != rhs.size())
    throw std::length_error("Both matrices must be of the same size");
  for (unsigned int i = 0; i<size(); i++)
    for (unsigned int j = 0; j<size(); j++)
    {
      m_matrix[i][j] = rhs[i][j];
    }
  return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Symmetric<T>& rhs)
{
  if(size() != rhs.size())
    throw std::length_error("Both matrices must be of the same size");
  for (unsigned int i = 0; i<size(); i++)
    for (unsigned int j = 0; j<size(); j++)
    {
      m_matrix[i][j] = rhs(i,j);
    }
  return *this;
}

template<class T>
bool Matrix<T>::operator==(const Matrix<T>& rhs)const
{
  if(size() != rhs.size())
    return false;
  for (unsigned int i = 0; i<size(); i++)
    for (unsigned int j = 0; j<size(); j++)
      if (m_matrix[i][j] != rhs[i][j])
        return false;
  return true;
}

// Purpose: Allow the user to change the value of an index of the vector
// Parameters: The index
// Returns: a reference to the T at the specified index
template<class T>
Array<T>& Matrix<T>::operator[](unsigned int i)
{
  if(size()==0 || i>=size())
    throw std::out_of_range("The matrix is empty or you went past the end");
  return m_matrix[i];
}

// Purpose: Provide access to an index without allowing it to be changed
// Parameters: The index
// Returns: A read only reference to the index
template<class T>
const Array<T>& Matrix<T>::operator[](unsigned int i) const
{
  if(size()==0 || i>=size())
    throw std::out_of_range("The matrix is empty or you went past the end");
  return m_matrix[i];
}

// Purpose: Subtraction operator
// Parameters: Calling object, Matrix to subtract from the calling object
// Returns: The updated Matrix
// Preconditions: subtraction and assignment operators defined for type T
template <class T>
Matrix<T> Matrix<T>::operator- (const Matrix<T>& rhs)
{
  if (size()==0)
    throw std::length_error("Can not perform operations on an empty matrix.");
  if (size() != rhs.size())
    throw std::length_error("Both matrices must be of the same size.");
    
  Matrix<T> newMatrix(size());
  for (unsigned int i=0;i<size();i++)
    for (unsigned int j=0;j<size();j++)
    {
       newMatrix[i][j] = m_matrix[i][j] - rhs[i][j];
    } 
  return newMatrix;
}

// Purpose: Addition operator
// Parameters: Calling object, Matrix to add to the calling object
// Returns: The updated Matrix
// Preconditions: addition and assignment operators defined for type T
template <class T>
Matrix<T> Matrix<T>::operator+ (const Matrix<T>& rhs)
{
  if (size()==0)
    throw std::length_error("Can not perform operations on an empty matrix.");
  if (size() != rhs.size())
    throw std::length_error("Both matrices must be of the same size.");
    
  Matrix<T> newMatrix(size());
  for (unsigned int i=0;i<size();i++)
    for (unsigned int j=0;j<size();j++)
    {
       newMatrix[i][j] = m_matrix[i][j] + rhs[i][j];
    } 
  return newMatrix;
}

// Purpose: Multiplication operator (with other matrices)
// Parameters: Calling object, Matrix to multiply with the calling object
// Returns: The updated Matrix
// Preconditions: multiplication, addition and assignment operators defined for type T
template <class T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& rhs) const
{
  if (size()==0)
    throw std::length_error("Can not perform operations on an empty matrix.");
  if (size() != rhs.size())
    throw std::length_error("Both matrices must be of the same size.");

  Matrix<T> newMatrix(size());
  T sum = 0;
  for (unsigned int i=0;i<size();i++)
  {
    for (unsigned int j=0;j<size();j++)
    {
       for (unsigned int q=0;q<size();q++)
         sum = sum + m_matrix[i][q] * rhs[q][j];
       newMatrix[i][j] = sum;
       sum = 0;
    }
  }
  return newMatrix;
}

// Purpose: Multiplication operator (with a scalar)
// Parameters: Calling object, scalar to multiply with the calling object
// Returns: The updated Matrix
// Preconditions: multiplication and assignment operators defined for type T
template <class T>
Matrix<T> Matrix<T>::operator* (const T& rhs)
{
  if (size()==0)
    throw std::length_error("Can not perform operations on an empty matrix.");
  Matrix<T> newMatrix(size());
  for (unsigned int i=0;i<size();i++)
    for (unsigned int j=0;j<size();j++)
    {
       newMatrix[i][j] = m_matrix[i][j] * rhs;
    } 
  return newMatrix;
}

// Purpose: Multiplication operator (with a vector)
// Parameters: Calling object, Vector to multiply with the calling object
// Returns: The updated Matrix
// Preconditions: multiplication and assignment operators defined for type T
template <class T>
Vector<T> Matrix<T>::operator* (const Vector<T>& rhs) const
{
  if (size()==0)
    throw std::length_error("Can not perform operations on an empty matrix.");
  if (size() != rhs.size())
    throw std::length_error("The size of the Vector and Matrix must be the same");
    
  Vector<T> newVector(size());

  for (unsigned int i=0;i<size();i++)
  {
    T sum = 0;
    for (unsigned int j=0;j<size();j++)
    {
      sum += m_matrix[i][j]*rhs[j];
    }
    newVector[i] = sum;
  }
  return newVector;
}

// Purpose: To swap two rows in a matrix
// Parameters: the rows to swap
// Returns: nothing
// Preconditions: assignment operator defined for type T
// Postconditions: the two specified rows are interchanged.
template <class T>
void Matrix<T>::swapRow(unsigned int row1, unsigned int row2)
{
  if(size()<2)
    throw std::length_error("Must have at least two rows to swap.");
  if(row1 >= size() || row2 >= size())
    throw std::out_of_range("One or more of the specified rows is out of range.");
  if(row1 == row2)
    return; //nothing to do.
  T temp;
  for (unsigned int i=0;i<size();i++)
  {
    temp = m_matrix[row1][i];
    m_matrix[row1][i] = m_matrix[row2][i];
    m_matrix[row2][i] = temp;
  }
  return;
}

// Purpose: Finds the index of the the row with the maximum value in the
//                specified column. Will only search rows below the index
//                of the specified column
// Parameters: Column to search
// Returns: The index of the row
// Preconditions: greater than operator defined for type T
template <class T>
int Matrix<T>::findMaxRow(unsigned int col)
{
  if(size()==0)
    throw std::length_error("Matrix can not be empty.");
  if(size()==1)
    return 0;
    
  int max = col;
  unsigned int i;
  for(i=col;i<size();i++)
  {
    if(m_matrix[i][col] > m_matrix[max][col])
      max = i;
  }
  return max;
}

// Purpose: To perform a row operation on the Matrix
// Parameters:  the indexes of two rows and a multiplier
// Returns: nothing
// Preconditions: multiplication, addition, and assignment operators
//                        defined for type T
// Postconditions: row1 is multiplied by mult and added to row2
template <class T>
void Matrix<T>::rowOp (unsigned int row1, T mult, unsigned int row2)
{
  if(size()<2)
    throw std::length_error("Must have at least two rows for a row operation.");
  if(row1 >= size() || row2 >= size())
    throw std::out_of_range("One or more of the specified rows is out of range.");
  Array<T> add;
  for (unsigned int i=0; i<size(); i++)
  {
    add.push_back(m_matrix[row1][i]*mult);
    m_matrix[row2][i] = m_matrix[row2][i] + add[i];
  }
  return;
}

// Purpose: Find the transpose of the matrix
// Parameters:  none
// Returns: The transposed matrix
// Preconditions: assignment operator defined for type T
template <class T>
Matrix<T> Matrix<T>::transpose() const
{
  Matrix<T> transposed(size());
  for (unsigned int i = 0; i<size(); i++)
    for (unsigned int j = 0; j<size(); j++)
      transposed[j][i] = m_matrix[i][j];
  return transposed;
}

template <class T>
Vector<T> Matrix<T>::solve(Vector<T> b)
{
  Matrix<T> myMatrix(MatrixBase<T>::size());
  for(unsigned int i=0;i<myMatrix.size(); i++)
    for(unsigned int j=0;j<myMatrix.size(); j++)
      myMatrix[i][j] = operator()(i,j);
  //Forward elimination with partial pivoting
  for(unsigned int i=0;i<myMatrix.size()-1;i++) // need to eliminate things down to last column
  {
    //PIVOT
    int rowWithMax;
    rowWithMax = myMatrix.findMaxRow(i); //find row # with maximum element in col xzcV
    myMatrix.swapRow(i,rowWithMax);
    b.swapRow(i,rowWithMax);
    //Eliminate all the values below swapped row
    T mult;  //used as the multiplier in the row operations
    for (unsigned int j=myMatrix.size()-1;j>i;j--)
    {
      if(myMatrix[j][i] != 0)
      {
        mult = -(myMatrix[j][i]/myMatrix[i][i]);
        myMatrix.rowOp(i,mult,j);
        b.rowOp(i,mult,j);
        myMatrix[j][i] = 0;
      }
    }
  }
  
  //now solve the matrix using back substitution
  Vector<T> solution(myMatrix.size());
  //start at bottom row, work up.
  for(int i = myMatrix.size() - 1; i>=0; i--) 
  {
    T subtractMe = 0;
    //gives 0 iterations at bottom row and one more for each row up after that
    for(int j = myMatrix.size() - 1 - i; j>0 ; j--)
      subtractMe = subtractMe + myMatrix[i][myMatrix.size()-j] * solution[solution.size()-j];
    solution[i] = (b[i] - subtractMe)/myMatrix[i][i];    
  }
  return solution;
}

template<class T>
bool Matrix<T>::diagonallyDominant()
{
  bool retVal = true;
  for(unsigned int i=0; i<MatrixBase<T>::size(); i++)
  {
    T sum = 0;
    for(unsigned int j=0; j<MatrixBase<T>::size(); j++)
      if(i!=j)
        sum+=abs(operator()(i,j));
    if (sum >= abs(m_matrix[i][i]))
      retVal = false;
  }
  return retVal;
}