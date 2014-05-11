// Matt Garlock
// CS 328 Final Project
// Implementation file for the ABuilder class

template <class T>
void fillSubMatrix ( MatrixBase<T> & fillMatrix, MatrixBase<T> & subMatrix, unsigned int startRow, unsigned int startCol )
{
  for ( unsigned int i = 0; i < subMatrix.size(); i++ )
  {
    for ( unsigned int j = 0; j < subMatrix.size(); j++ )
    {
      fillMatrix( startRow + i , startCol + j ) = subMatrix ( i , j );
    }
  }
  return;
}

template <class T>
Symmetric<T> ABuilder<T>:: operator() ( unsigned int n )
{
  unsigned int subMatrixSize = n - 1;
  unsigned int matrixSize = ( n - 1 ) * ( n - 1 );

  Diagonal<T> subAndSuperDiagonalSubMatrix ( subMatrixSize );
  for ( unsigned int i = 0; i < subMatrixSize; i++ )
  {
    subAndSuperDiagonalSubMatrix( i, i ) = -.25;
  }
  
  Banded<T> diagonalSubMatrix ( subMatrixSize );
  for ( unsigned int i = 0; i < subMatrixSize - 1; i++ )
  {
    diagonalSubMatrix ( i , i ) = 1;
    diagonalSubMatrix ( i + 1 , i ) = -.25;
    diagonalSubMatrix ( i , i + 1 ) = -.25;
  }
  diagonalSubMatrix ( subMatrixSize - 1 , subMatrixSize - 1 ) = 1;

  Symmetric<T> A ( matrixSize );
  for ( unsigned int i = 0; i < subMatrixSize - 1; i++ )
  {
    fillSubMatrix ( A, diagonalSubMatrix, i * subMatrixSize, i * subMatrixSize );
    fillSubMatrix ( A, subAndSuperDiagonalSubMatrix, ( i + 1 ) * subMatrixSize, i * subMatrixSize );
  }
  fillSubMatrix ( A, diagonalSubMatrix, ( subMatrixSize - 1 ) * subMatrixSize, ( subMatrixSize - 1 ) * subMatrixSize );
  return A;
}