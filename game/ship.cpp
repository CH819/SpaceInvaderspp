#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "projectile.h"
#include "ship.h"

using namespace std;

Ship::Ship( float maxy, float maxx ){
  
  max_x = maxx;
  max_y = maxy;
  x = max_x/2;
  y = max_y - 5;
}


void Ship::print(  ){
  
  mvprintw(y, x, "o");
  mvprintw(y+1, x-2, "ooooo");
  mvprintw(y+2, x-3, "ooooooo");
  mvprintw(y+3, x-3, " o   o ");
  
  //refresh();
}


void Ship::action( int ch, proj_vec& project ){
  
  switch( ch ){
    
    case KEY_RIGHT:
      if ( x+6 <= max_x ) x += direction;
      break;
    
    case KEY_LEFT:
      if ( x-5 >= 0 ) x -= direction;
      break;
    
    case KEY_UP:
      if (project.size() < 3){
        Projectile proj( y, x );
        project.push_back( proj );
      }
      
      break;
    
  }
}
