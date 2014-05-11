// Matt Garlock
// CS 328 Final Project
// topFunc

# ifndef TOPFUNC_H
# define TOPFUNC_H

template < typename T >
class TopFunc
{
  public:
    // returns the z value for the point ( x , 1 )
    T operator () ( const T & x ) { return 0 * x; }
};

# endif
