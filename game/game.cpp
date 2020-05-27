#include <iostream>

#include "projectile.h"
#include "ship.h"
#include "alien.h"
#include "game.h"

using namespace std;

Game::Game( int h ){
  
}

void Game::start(){
  
  float max_y = 0, max_x = 0;
  int ch, xindex, yindex;
  
  initscr();
  noecho();
  curs_set(FALSE);
  //raw();
  cbreak();
  keypad( stdscr, true );
  nodelay(stdscr, 1);  
  
  getmaxyx(stdscr, max_y, max_x);
  
  Aliens A1( 0., 0., 3, 3 );
  Ship ship( max_y, max_x );
  
  
  while(1) {
    
    //getmaxyx(stdscr, max_y, max_x);
    clear();
    
    A1.UpdatePosition( max_x );
    ship.print();
    
    ch = getch();
    ship.action( ch, project );
    
    for ( int i=0; i<project.size(); i++){
      project[i].print();
      project[i].move();
      
      if (project[i].y <= 0 ){
          project.erase( project.begin() + i );
          break;
      }
      
      xindex = (project[i].x - A1.XL)/LENGTH;
      yindex = (project[i].y - A1.Y)/HEIGHT;
      
      if ( yindex >= 0 && yindex <= A1.N ){
        if ( xindex >= 0 && xindex <= A1.M ){
          
          if ( A1.AliensStatus[xindex][yindex] == 1 ){
            
            A1.AliensStatus[xindex][yindex] = 0;
            project.erase( project.begin() + i );
          }
        }
      }
    }
    
    refresh();
    
    if ( ch == KEY_F(1) ) break;
    
  }
  
  endwin();
  
}


