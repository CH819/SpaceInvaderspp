#include <iostream>

#include "projectile.h"
#include "ship.h"
#include "alien.h"
#include "game.h"

using namespace std;

Game::Game( int h ){
  
  lost = "YOU DIED!";
  won = "YOU WON!";
  speed = 0.3;
}

void Game::Start(){
  
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  nodelay( stdscr, 0 );
  curs_set(FALSE);
  //keypad( stdscr, true );
  
  int height = 6;
  int width = 30;

  getmaxyx( stdscr, yMaxSTD,  xMaxSTD );

  menuwin = newwin( height, width, yMaxSTD/2 , (xMaxSTD - width)/2 );
  keypad( menuwin, true );
   
   
  gamewin = newwin( yMaxSTD - 2, xMaxSTD, 0, 0 );
  keypad( gamewin, true );
  nodelay( gamewin, 1 );
  getmaxyx( gamewin, yMaxGame,  xMaxGame );
  
  ShowMenu();
}

void Game::ShowMenu(){
  

  int height = 6;
  int width = 30;

  box( menuwin, 0, 0 );
  
  PrintInitAlien( xMaxSTD );
  refresh();
  wrefresh( menuwin );

  int n = 3;
  string choices[n] = { "PLAY", "SET DIFFICULTY", "EXIT" };

  int choice;
  int highlight = 0;
  
    while( 1 ){
    
    clear();
    
    getmaxyx( stdscr, yMaxSTD, xMaxSTD );

    
    box( menuwin, 0, 0 );
    
    PrintInitAlien( xMaxSTD );
    refresh();
    wrefresh( menuwin );

    for( int i=0; i<n; i++){

      if( i == highlight ){

        //Changes attribute for a window
        wattron( menuwin, A_REVERSE ); //Puts selected item in negative
      }

      mvwprintw( menuwin, i+1, (width - choices[i].length())/2, choices[i].c_str() );
      wattroff( menuwin, A_REVERSE ); //Turns off the attribute change
    }

    choice = wgetch( menuwin );

    switch( choice ){

    case KEY_UP:
      highlight--;
      if( highlight == -1 ) highlight = 0;

      break;

    case KEY_DOWN:
      highlight++;

      if( highlight == n ) highlight = n-1;
      break;

    default:
      break;

    }

    if( choice == 10 ){
      
      werase( menuwin );
      clear();
      
      switch( highlight ){
        
       case 0:
        Play();
        break;
      
       case 1:
        SetDifficulty();
        break;
        
       case 2:
        endwin(); 
        break;
         
       default:
        break;
      }
      
      break;
    }
  }
  
  getch();
  endwin();
}

float Game::SetDifficulty(){
  
  int yMaxSTD, xMaxSTD;

  int height = 6;
  int width = 30;

  getmaxyx( stdscr, yMaxSTD, xMaxSTD );

  box( menuwin, 0, 0 );
  
  PrintInitAlien( xMaxSTD );
  refresh();
  wrefresh( menuwin );

  int n = 4;
  string choices[n] = { "BABY", "NERD", "80's KID WITH NO LIFE", "RETURN" };

  int choice;
  int highlight = 0;
 

    while( 1 ){
    
    clear();
    
    getmaxyx( stdscr, yMaxSTD, xMaxSTD );

    //menuwin = newwin( height, width , yMaxSTD/2 , (xMaxSTD - width)/2 );
    box( menuwin, 0, 0 );
    
    PrintInitAlien( xMaxSTD );
    refresh();
    wrefresh( menuwin );
    //keypad( menuwin, true );

    for( int i=0; i<n; i++){

      if( i == highlight ){

        //Changes attribute for a window
        wattron( menuwin, A_REVERSE ); //Puts selected item in negative
      }

      mvwprintw( menuwin, i+1, (width - choices[i].length())/2, choices[i].c_str() );
      wattroff( menuwin, A_REVERSE ); //Turns off the attribute change
    }

    choice = wgetch( menuwin );

    switch( choice ){

    case KEY_UP:
      highlight--;
      if( highlight == -1 ) highlight = 0;

      break;

    case KEY_DOWN:
      highlight++;

      if( highlight == n ) highlight = n-1;
      break;

    default:
      break;

    }

    if( choice == 10 ){
      
      //delwin( menuwin );
      clear();
      
      switch( highlight ){
        
       case 0:
        speed = 0.3;
        break;
      
       case 1:
        speed = 0.5;
        break;
        
       case 2:
        speed = 1; 
        break;
        
       case 3:
        break;
         
       default:
        break;
      }
      
      break;
    }
  }

  
  werase( menuwin );
  ShowMenu();
  
  return 0.3;
}

void Game::Play(){
  
  
  int ch, xindex, yindex, w;
  
  Aliens A1( 0., 0., 10, 4, speed, gamewin );
  Ship ship( yMaxGame, xMaxGame, gamewin );
  
  
  while(1) {
    
    werase( gamewin );
    
    w = A1.UpdatePosition( yMaxGame, xMaxGame );
    
    switch( w ){
      
     case 0:
      break;
      
     case 1:
      clear();
       
      mvprintw( yMaxGame/2, xMaxGame/2, lost.c_str() );
      refresh();
      usleep( 2000000 );
      
      ShowMenu();
      break;
    
     case 2:
      clear();
       
      mvprintw( yMaxGame/2, xMaxGame/2, won.c_str() );
      refresh();
      usleep( 2000000 );
      
      ShowMenu();
      return;
    }
    
    ship.print();
    
    ch = wgetch( gamewin );
    ship.action( ch, project );
    
    box( gamewin, 0, 0 );
    
    for ( int i=0; i<project.size(); i++){
      
      project[i].print();
      project[i].move();
      
      if (project[i].y <= 0 ){
        
          project.erase( project.begin() + i );
          break;
      }
      
      xindex = (project[i].x - A1.XL)/LENGTH;
      yindex = (project[i].y - A1.Y)/HEIGHT;
      
      if ( yindex >= 0 && yindex < A1.M ){
        if ( xindex >= 0 && xindex < A1.N ){
          
          if ( A1.AliensStatus[yindex][xindex] == 1 ){
            
            A1.AliensStatus[yindex][xindex] = 0;
            project.erase( project.begin() + i );
          }
        }
      }
    }
    
    A1.CheckAliensL();
    A1.CheckAliensR();
    A1.CheckAliensB();
    
    wrefresh( gamewin );
    
    if ( ch == KEY_F(1) ) break;    
  
  }
  
  return;
}

void Game::PrintInitAlien( int x ){

  string InitAlien[] = { AMenu1, AMenu2, AMenu3, AMenu4, AMenu5, AMenu6, AMenu7,
                         AMenu8, AMenu9, AMenu10, AMenu11, AMenu12, AMenu13,
                         AMenu14, AMenu15, AMenu16, AMenu17 };

  for( int i=0; i<17; i++ ){

    mvprintw( i, x/2 - InitAlien[i].length()/2, InitAlien[i].c_str() );
  }
}


