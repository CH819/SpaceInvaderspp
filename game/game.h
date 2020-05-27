#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <vector>

#include "projectile.h"
#include "ship.h"
#include "alien.h"

using namespace std;

typedef vector< Projectile > proj_vec;

class Game{
  public:
    Game( int );
    void start();
    
    
  private:
    proj_vec project;
    
};

