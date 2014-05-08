/* Diagonal.hpp
   Implementation for a templated Diagonal matrix class
   Christopher Garlock
 */

template <class T>
Diagonal<T>:: Diagonal(unsigned int size):M_ZERO(0)
{
  Array<T> temp(size);
  m_matrix = temp;
  MatrixBase<T>::m_size = size;
}

template <class T>
Diagonal<T>:: Diagonal(const Diagonal<T>& copy):M_ZERO(0)
{
  Array<T> temp(copy.MatrixBase<T>::size());
  m_matrix = temp;
  MatrixBase<T>::m_size = copy.MatrixBase<T>::size();
  *this = copy;
}

template <class T>
Diagonal<T>& Diagonal<T>::operator= (const Diagonal<T>& rhs)
{
  if(MatrixBase<T>::size() != rhs.MatrixBase<T>::size())
    throw std::length_error("Both Diagonals must be of the same size");
  for(unsigned int i = 0; i < MatrixBase<T>::size(); i++)
    m_matrix[i] = rhs.m_matrix[i];
  return *this;
}

template <class T>
Diagonal<T> Diagonal<T>::operator- (const Diagonal<T>& rhs) const
{
  if(MatrixBase<T>::size() != rhs.MatrixBase<T>::size())
    throw std::length_error("Both Diagonals must be of the same size");
  Diagonal newDiag(MatrixBase<T>::size());
  for(unsigned int i=0; i < MatrixBase<T>::size(); i++)
    newDiag[i] = m_matrix[i] - rhs.m_matrix[i];
  return newDiag;
}

template <class T>
Diagonal<T> Diagonal<T>::operator+ (const Diagonal<T>& rhs) const
{
  if(MatrixBase<T>::size() != rhs.MatrixBase<T>::size())
    throw std::length_error("Both Diagonals must be of the same size");
  Diagonal newDiag(MatrixBase<T>::m_size);
  for(unsigned int i=0; i < MatrixBase<T>::m_size; i++)
    newDiag[i] = m_matrix[i] + rhs.m_matrix[i];
  return newDiag;
}

template <class T>
Diagonal<T> Diagonal<T>::operator* (const Diagonal<T>& rhs)
{
  if(MatrixBase<T>::size() != rhs.MatrixBase<T>::size())
    throw std::length_error("Both Diagonals must be of the same size");
  Diagonal newDiag(MatrixBase<T>::m_size);
  for(unsigned int i=0; i < MatrixBase<T>::m_size; i++)
    newDiag[i] = m_matrix[i] * rhs.m_matrix[i];
  return newDiag;
}

template <class T>
Diagonal<T> Diagonal<T>::operator* (const T& rhs)
{
  if (MatrixBase<T>::size()==0)
    throw std::length_error("Can not perform operations on an empty Diagonal.");
  Diagonal newDiag(MatrixBase<T>::m_size);
  for(unsigned int i=0; i < MatrixBase<T>::size(); i++)
    newDiag[i] = m_matrix[i] * rhs;
  return newDiag;
}

template <class T>
Vector<T> Diagonal<T>::operator* (const Vector<T>& rhs)
{
  if(MatrixBase<T>::size() != rhs.size())
    throw std::length_error("The Diagonal and Vector must be of the same size");
  Vector<T> newVec(MatrixBase<T>::size());
  for(unsigned int i=0; i < MatrixBase<T>::size(); i++)
    newVec[i] = m_matrix[i] * rhs[i];
  return newVec;
}

template <class T>
T& Diagonal<T>::operator()(const unsigned int row, const unsigned int col)
{
  if(row != col)
    return m_zero = 0;
  return m_matrix[row];
}

template <class T>
const T& Diagonal<T>::operator()(const unsigned int row, const unsigned int col)const
{
  if(row != col)
    return M_ZERO;
  return m_matrix[row];
}

template <class T>
Vector<T> Diagonal<T>::solve(Vector<T> b)
{
  if(b.size() != MatrixBase<T>::size())
    throw std::length_error("the size of b and the calling object must be equal.");
  Vector<T> x(b.size());
  for(unsigned int i=0;i<MatrixBase<T>::size();i++)
    x[i] = b[i]/operator[](i);
  return x;
}
