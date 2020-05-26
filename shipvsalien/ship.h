#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

class Ship{
  
  public:
    Ship( int, int );
    void print();
    void move( int );
    void shoot();
  
  private:
    int direction = 1;
    int max_y;
    int max_x;
    int y, x;
};
