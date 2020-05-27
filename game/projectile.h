#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

class Projectile{
  
  public:
    Projectile( int, int );
    void print();
    void move();
  
  private:
    int direction = 1;
    int max_y;
    int y, x;
};

#endif
