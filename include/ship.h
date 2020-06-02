#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <fstream>

#include "projectile.h"

using namespace std;

typedef vector< Projectile > proj_vec;

class Ship{
  friend class Game;
  
  public:
    Ship( float, float, WINDOW * );
    void print();
    void action( int, proj_vec& );
    void init_logo();
  
  private:
    int direction = 1;
    int max_y;
    int max_x;
    int y, x;

    vector< string > ship_logo;
    
    WINDOW * gamewin;
};

#endif
