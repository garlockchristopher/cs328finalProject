/* Banded.hpp
   Implimentation for a templated Banded matrix class
   Christopher Garlock
 */
template <class T>
Banded<T>::Banded(unsigned int size):M_ZERO(0)
{
  if(size < 2)
    throw std::length_error("A Banded must have size >= 2.");
  Array<T> midTemp(size);
  Array<T> topBotTemp(size-1);
  m_tBand = topBotTemp;
  m_mBand = midTemp;
  m_bBand = topBotTemp;
  MatrixBase<T>::m_size = size;
}

template <class T>
Banded<T>::Banded(const Banded<T>& copy):M_ZERO(0)
{
  Array<T> midTemp(copy.MatrixBase<T>::size());
  Array<T> topBotTemp(copy.MatrixBase<T>::size()-1);
  m_tBand = topBotTemp;
  m_mBand = midTemp;
  m_bBand = topBotTemp;
  MatrixBase<T>::m_size = copy.MatrixBase<T>::m_size;
  *this = copy;
}

template <class T>
Banded<T>& Banded<T>::operator= (const Banded<T>& rhs)
{
  if(MatrixBase<T>::size() != rhs.MatrixBase<T>::size())
    throw std::length_error("Both banded matrices must be of the same size");
  for (unsigned int i=0; i<MatrixBase<T>::size(); i++)
  {
    m_mBand[i] = rhs.m_mBand[i];
    if(i != MatrixBase<T>::size() - 1)
    {
      m_tBand[i] = rhs.m_tBand[i];
      m_bBand[i] = rhs.m_bBand[i];
    }
  }
  return *this;
}

template <class T>
T& Banded<T>::operator()(const unsigned int row, const unsigned int col)
{
  if(row >= MatrixBase<T>::size() || col >= MatrixBase<T>::size())
    throw std::out_of_range("Row and Column must be < size.");
  if(row > col + 1 || col > row + 1)
      return m_zero = 0;
  if(row > col) //bottom band
    return m_bBand[col];
  else if(row == col)
    return m_mBand[col];
  else
    return m_tBand[row];
}

template <class T>
const T& Banded<T>::operator()(const unsigned int row, const unsigned int col)const
{
  if(row >= MatrixBase<T>::size() || col >= MatrixBase<T>::size())
    throw std::out_of_range("Row and Column must be < size.");
  if(row > col + 1 || col > row + 1)
    return M_ZERO;
  if(row > col) //bottom band
    return m_bBand[col];
  else if(row == col)
    return m_mBand[col];
  else
    return m_tBand[row];
}

template <class T>
Banded<T> Banded<T>::operator- (const Banded<T>& rhs) const
{
  if(MatrixBase<T>::size() != rhs.MatrixBase<T>::size())
    throw std::length_error("Both Banded matrices must be of the same size");
  Banded newBanded(MatrixBase<T>::size());
  for (unsigned int i=0; i<MatrixBase<T>::size(); i++)
  {
    newBanded.m_mBand[i] = m_mBand[i] - rhs.m_mBand[i];
    if(i != MatrixBase<T>::size() - 1)
    {
      newBanded.m_tBand[i] = m_tBand[i] - rhs.m_tBand[i];
      newBanded.m_bBand[i] = m_bBand[i] - rhs.m_bBand[i];
    }
  }
  return newBanded;
}

template <class T>
Banded<T> Banded<T>::operator+ (const Banded<T>& rhs) const
{
  if(MatrixBase<T>::size() != rhs.MatrixBase<T>::size())
    throw std::length_error("Both Banded matrices must be of the same size");
  Banded newBanded(MatrixBase<T>::size());
  for (unsigned int i=0; i<MatrixBase<T>::size(); i++)
  {
    newBanded.m_mBand[i] = m_mBand[i] + rhs.m_mBand[i];
    if(i != MatrixBase<T>::size() - 1)
    {
      newBanded.m_tBand[i] = m_tBand[i] + rhs.m_tBand[i];
      newBanded.m_bBand[i] = m_bBand[i] + rhs.m_bBand[i];
    }
  }
  return newBanded;
}

template <class T>
Banded<T> Banded<T>::operator* (const Banded<T>& rhs)
{
  if(MatrixBase<T>::size() != rhs.MatrixBase<T>::size())
    throw std::length_error("Both Banded matrices must be of the same size");
  bool lTopZeros = true; //false if there are any nonzero elements in the 
                                     //top band of left hand side
  bool lBotZeros = true; //false ... bottom band of left hand side
  bool rTopZeros = true; //false ... top band of right hand side
  bool rBotZeros = true; //false ... bottom band of right hand side
  for (unsigned int i=0; i<MatrixBase<T>::size() - 1; i++)
  {
    if (m_tBand[i] != 0)
      lTopZeros = false;
    if (m_bBand[i] != 0)
      lBotZeros = false;
    if (rhs.m_tBand[i] != 0)
      rTopZeros = false;
    if (rhs.m_bBand[i] != 0)
      rBotZeros = false;
  }
  
  //check to see if result is a banded matrix, if not, throw an exception
  if ( !( (lTopZeros && lBotZeros) 
       || (lTopZeros && rBotZeros)
       || (rTopZeros && lBotZeros)
       || (rTopZeros && rBotZeros)))
    throw "The result of this multiplication will not be a banded matrix.";
  
  //compute result
  Banded<T> newBand(MatrixBase<T>::size());
  for (unsigned int i=0; i<MatrixBase<T>::size(); i++)
  {
    if(i == 0) //top row
    {
      newBand.m_mBand[i] = m_mBand[i] * rhs.m_mBand[i] + m_tBand[i] * rhs.m_bBand[i];
      newBand.m_tBand[i] = m_mBand[i] * rhs.m_tBand[i] + m_tBand[i] * rhs.m_mBand[i+1];
    }
    else if(i == MatrixBase<T>::size()-1) //bottom row
    {
      newBand.m_bBand[i-1] = m_bBand[i-1] * rhs.m_mBand[i-1] + m_mBand[i] * rhs.m_bBand[i-1];
      newBand.m_mBand[i] = m_bBand [i-1] * rhs.m_tBand[i-1] + m_mBand[i] * rhs.m_mBand[i];
    }
    else //arbitrary row that is not the top or bottom
    {
      newBand.m_bBand[i-1] = m_bBand[i-1] * rhs.m_tBand[i-1] + m_mBand[i] * rhs.m_bBand[i-1];
      newBand.m_mBand[i] = m_tBand[i-1] * rhs.m_bBand[i-1] + m_mBand[i] * rhs.m_mBand[i] + m_bBand[i] * rhs.m_tBand[i];
      newBand.m_tBand[i] = m_tBand[i] * rhs.m_mBand[i] + m_mBand[i+1] * rhs.m_tBand[i];
    }
  }
  return newBand;
}

template <class T>
Banded<T> Banded<T>::operator* (const T& rhs)
{
  if (MatrixBase<T>::size()==0)
    throw std::length_error("Can not perform operations on an empty Banded Matrix.");
    
  Banded<T> newBand(MatrixBase<T>::size());
  
  for (unsigned int i=0; i<MatrixBase<T>::size(); i++)
  {
    newBand.m_mBand[i] = m_mBand[i] * rhs;
    if(i != MatrixBase<T>::size() - 1)
    {
      newBand.m_tBand[i] = m_tBand[i] * rhs;
      newBand.m_mBand[i] = m_mBand[i] * rhs;
    }
  }
  return newBand;
}

template <class T>
Vector<T> Banded<T>::operator* (const Vector<T>& rhs) const
{
  if(MatrixBase<T>::size() != rhs.size())
    throw std::length_error("The Banded and Vector must be of the same size");
  Vector<T> newVec(MatrixBase<T>::size());

  for (unsigned int i = 0; i<MatrixBase<T>::size(); i++)
  {
    if(i==0) //top row
      newVec[i] = m_mBand[i] * rhs[i] + m_tBand[i] * rhs[i+1];
    else if(i == MatrixBase<T>::size()-1) //bottom row
      newVec[i] = m_bBand[i-1] * rhs[i-1] + m_mBand[i] * rhs[i];
    else //not edge case
      newVec[i] = m_bBand[i-1] * rhs[i-1] + m_mBand[i] * rhs[i] + m_tBand[i] * rhs[i+1];
  }
  return newVec;
}

template<class T>
Vector<T> Banded<T>::solve(Vector<T> b)
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
