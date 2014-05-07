/* Symmetric.hpp
   Implementation for a templated Symmetrical matrix class
   Christopher Garlock
 */
template <class T>
Symmetric<T>::Symmetric(unsigned int size)
{
  for(unsigned int i = 1; i <= size; i++)
  {
    Array<T> temp(i);
    m_matrix.push_back(temp);
  }
  MatrixBase<T>::m_size = size;
}

template <class T>
Symmetric<T>::Symmetric(const Symmetric<T>& copy)
{
  for(unsigned int i = 1; i <= copy.MatrixBase<T>::size(); i++)
  {
    Array<T> temp(i);
    m_matrix.push_back(temp);
  }
  MatrixBase<T>::m_size = copy.MatrixBase<T>::size();
  *this = copy;
}

template <class T>
Symmetric<T>& Symmetric<T>::operator= (const Symmetric<T>& rhs)
{
  if(MatrixBase<T>::size() != rhs.MatrixBase<T>::size())
    throw std::length_error("Both Symmetrics must be of the same size");
  for(unsigned int i=0;i<MatrixBase<T>::size();i++)
    for(unsigned int j=0; j<=i; j++)
      m_matrix[i][j] = rhs[i][j];
  return *this;
}

template <class T>
Array<T>& Symmetric<T>::operator[] (const unsigned int index)
{
  if(MatrixBase<T>::size()==0 || index>=MatrixBase<T>::size())
    throw std::out_of_range("The matrix is empty or you went past the end");
  return m_matrix[index];
}

template <class T>
const Array<T>& Symmetric<T>::operator[] (const unsigned int index) const
{
  if(MatrixBase<T>::size()==0 || index>=MatrixBase<T>::size())
    throw std::out_of_range("The matrix is empty or you went past the end");
  return m_matrix[index];
}

template <class T>
Symmetric<T> Symmetric<T>::operator- (const Symmetric<T>& rhs) const
{
  if(MatrixBase<T>::size() != rhs.MatrixBase<T>::size())
    throw std::length_error("Both Diagonals must be of the same size");
  Symmetric<T> mySymmetric(MatrixBase<T>::size());
  for(unsigned int i=0;i<MatrixBase<T>::size();i++)
    for(unsigned int j=0; j<=i; j++)
    {
      mySymmetric[i][j] = m_matrix[i][j] - rhs[i][j];
    }
  return mySymmetric;
}

template <class T>
Symmetric<T> Symmetric<T>::operator+ (const Symmetric<T>& rhs) const
{
  if(MatrixBase<T>::size() != rhs.MatrixBase<T>::size())
    throw std::length_error("Both Diagonals must be of the same size");
  Symmetric<T> mySymmetric(MatrixBase<T>::size());
  for(unsigned int i=0;i<MatrixBase<T>::size();i++)
    for(unsigned int j=0; j<=i; j++)
    {
      mySymmetric(i,j) = m_matrix[i][j] + rhs[i][j];
    }
  return mySymmetric;
}

template <class T>
Symmetric<T> Symmetric<T>::operator* (const Symmetric<T>& rhs)
{
  bool symmetricProduct = false;
  //Check to see if the two Symmetrics commute (AB == BA)
  Matrix<T> A(MatrixBase<T>::size());
  A  = *this;
  Matrix<T> B(MatrixBase<T>::size());
  B = rhs;
  Matrix<T> AB(MatrixBase<T>::size());
  AB = A*B;
  Matrix<T> BA(MatrixBase<T>::size());
  BA  = B*A;
  if(AB == BA)
    symmetricProduct = true;
  if(!symmetricProduct)
    throw "Multiplication of these two Symmetrics would result in a non Symmetric Matrix!";

  Symmetric<T> newSymmetric(MatrixBase<T>::size());
  for(unsigned int i=0;i<MatrixBase<T>::size();i++)
    for(unsigned int j=0; j<=i; j++)
    {
      newSymmetric[i][j] = AB[i][j]; //use the computed product from above to fill the Symmetric
    }
  return newSymmetric;
}

template <class T>
Symmetric<T> Symmetric<T>::operator* (const T& rhs)
{
  if (MatrixBase<T>::size()==0)
    throw std::length_error("Can not perform operations on an empty Symmetric.");
  Symmetric<T> newSymmetric(MatrixBase<T>::size());
  for(unsigned int i=0;i<MatrixBase<T>::size();i++)
    for(unsigned int j=0; j<=i; j++)
      newSymmetric[i][j] = m_matrix[i][j] * rhs;
  return newSymmetric;
}

template <class T>
Vector<T> Symmetric<T>::operator* (const Vector<T>& rhs)
{
  if(MatrixBase<T>::size() != rhs.size())
    throw std::length_error("The Symmetric and Vector must be of the same size");
    
  Vector<T> newVector(MatrixBase<T>::size());
  for(unsigned int i=0;i<MatrixBase<T>::size();i++)
  {
    T sum = 0;
    for(unsigned int j=0; j<MatrixBase<T>::size(); j++)
    {
      sum+=operator()(i,j)*rhs[j];
    }
    newVector[i] = sum;
  }
  return newVector;
}

template <class T>
T& Symmetric<T>::operator()(const unsigned int row, const unsigned int col)
{
  if(col>row)
    return m_matrix[col][row];
  return m_matrix[row][col];
}

template <class T>
const T& Symmetric<T>::operator()(const unsigned int row, const unsigned int col)const
{
  if(col>row)
    return m_matrix[col][row];
  return m_matrix[row][col];
}

template<class T>
bool Symmetric<T>::diagonallyDominant()
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

template<class T>
Vector<T> Symmetric<T>::solve(Vector<T> b)
{
  /*
  if(!diagonallyDominant())
    throw ios_base::failure("Symmetric Matrix must be diagonally dominant.");
  
  T error;
  Vector<T> e(MatrixBase<T>::size());
  Vector<T> r(MatrixBase<T>::size());
  Vector<T> x(MatrixBase<T>::size());
  T q;
  
  //build initial x to begin iterative steepest descent method.
  for(unsigned int i=0 ;i<MatrixBase<T>::size();i++)
    x[i] = b[i]/operator()(i,i);

  //now apply the algorithm
  do
  {
    //get the next x.
    r = b - (*this)*x;
    q = (r*r)/(r*((*this)*r));
    x = x + r*q;
    
    //compute error
    e = (*this)*x - b;
    error = 0;
    for(unsigned int i=0; i<e.size(); i++)
    {
      error+=abs(e[i]);
    }
  }while(error>ERROR_THRESHOLD);
  return x;
  */
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