// Chris Garlock
// CS 328 Final Project
// Implementation file for the ABuilder class

template<class T>
Vector<T> BBuilder<T>::operator()(unsigned int n, TopFunc<T> tFunc, BotFunc<T> bFunc, LeftFunc<T> lFunc, RightFunc<T> rFunc)
{
  unsigned int size = (n-1)*(n-1);
  Vector<T> b(size);
  unsigned int pos = 0;
  
  for( int i=0; i<sqrt(size); i++) //start at bottom row and iterate up
    for(int j=0; j<sqrt(size); j++) //start at left column and iterate right
    {
      if(i==0 && j==0) //bottom left corner
        b[pos++] = lFunc(1.0/static_cast<T>(sqrt(size)+1)) + bFunc(1.0/static_cast<T>(sqrt(size)+1));
        
      else if(i==0 && j==sqrt(size)-1) //bottom right corner
        b[pos++] = rFunc(1.0/static_cast<T>(sqrt(size)+1)) + bFunc(1 - (1.0/static_cast<T>(sqrt(size)+1)));
        
      else if(i==sqrt(size) - 1 && j==0) //top left corner
        b[pos++] = lFunc(1 - (1.0/static_cast<T>(sqrt(size)+1))) + tFunc(1.0/static_cast<T>(sqrt(size)+1));
        
      else if (i==sqrt(size) - 1 && j==sqrt(size) - 1) //top right corner
        b[pos++] = rFunc(1 - (1.0/static_cast<T>(sqrt(size)+1))) + tFunc(1 - (1.0/static_cast<T>(sqrt(size)+1)));
        
      else if(i==0) //bottom row, not on corner
        b[pos++] = bFunc(static_cast<T>(j+1) / static_cast<T>(sqrt(size)+1));
        
      else if(j==0) //left column, not on corner
        b[pos++] = lFunc(static_cast<T>(i+1) / static_cast<T>(sqrt(size)+1));
        
      else if(i==sqrt(size) - 1) //top row, not on corner
        b[pos++] = tFunc(static_cast<T>(j+1) / static_cast<T>(sqrt(size)+1));
        
      else if(j==sqrt(size) - 1) //right column, not on corner
        b[pos++] = rFunc(static_cast<T>(i+1) / static_cast<T>(sqrt(size)+1));
      
      else //somewhere in middle
        b[pos++] = 0;      
    }
  for(unsigned int i = 0; i<size; i++)
    b[i] = b[i] * 0.25;
  return b;
}