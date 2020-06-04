#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "projectile.h"
#include "ship.h"

using namespace std;


Ship::Ship( float maxy, float maxx, WINDOW * win ){
  
  max_x = maxx;
  max_y = maxy;
  x = max_x/2;
  y = max_y - 5;
  gamewin = win;

  init_logo();
}


void Ship::print(){

  for( unsigned int i=0; i<ship_logo.size(); i++){

    mvwprintw( gamewin, y+i, x-3, ship_logo[i].c_str() );
  }
}


void Ship::action( int ch, proj_vec& project ){
  
  switch( ch ){
    
    // Move to the right (if not on border of screen)
    case KEY_RIGHT:
      if ( x+6 <= max_x ) x += direction;
      break;
    
    // Move to the left (if not on border of screen)
    case KEY_LEFT:
      if ( x-5 >= 0 ) x -= direction;
      break;
    
    // Shoot projectile
    case KEY_UP:
      if ( project.size() < 3 ){
        Projectile proj( y, x, 0.8, gamewin );
        project.push_back( proj );
      }
      
      break;
    
  }
}


// Load ship data
void Ship::init_logo(){

  ifstream infile( "data/logos/ship.txt" );

  if ( infile.fail() )   
    {
      cout << "Your ship.txt file is missing!" << endl;
      exit( 1 );
    }

  string line;
  while( getline( infile, line ) ){

    ship_logo.push_back( line );
  }
  
  infile.close();
}
