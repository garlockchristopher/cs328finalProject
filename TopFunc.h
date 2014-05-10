// Matt Garlock
// CS 328 Final Project
// topFunc

# ifndef TOPFUNC_H
# define TOPFUNC_H

template < typename T >
class TopFunc
{
  public:
    T operator () ( const T & x ) { return 0 * x; }
};

# endif
