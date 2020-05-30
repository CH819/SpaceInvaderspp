#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

class Projectile{
  
  friend class Game;
  
  public:
    Projectile( float, float, float, WINDOW * );
    void print();
    void move();
  
  private:
    float direction;
    float max_y;
    float y, x;
    WINDOW * gamewin;
};

#endif
