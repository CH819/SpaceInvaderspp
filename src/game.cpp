#include "projectile.h"
#include "ship.h"
#include "alien.h"
#include "game.h"

using namespace std;

Game::Game( int h ){
  
  lost = "YOU DIED!";
  won = "YOU WON!";
  speed = 0.3;
  
  init_hiscores();
}


void Game::Start(){
  
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  nodelay( stdscr, 0 );
  curs_set(FALSE);
  
  int height = 9;
  int width = 30;

  getmaxyx( stdscr, yMaxSTD,  xMaxSTD );

  //Setting up Menu Window
  menuwin = newwin( height, width, yMaxSTD/2 , (xMaxSTD - width)/2 );
  keypad( menuwin, true );
   
  //Setting up Game Window 
  gamewin = newwin( yMaxSTD - 2, xMaxSTD, 0, 0 );
  keypad( gamewin, true );
  nodelay( gamewin, 1 );
  getmaxyx( gamewin, yMaxGame,  xMaxGame );
  
  //Setting up Info Window
  infowin = newwin( 3, xMaxSTD, yMaxSTD - 3, 0 );
  getmaxyx( infowin, yMaxInfo,  xMaxInfo );
  
  //Setting up High Score Window  
  hswin = newwin( 3, xMaxSTD - 12, yMaxSTD/2 , 4 );
  
  ShowMenu();
}


void Game::ShowMenu(){
  

  int height = 9;
  int width = 30;

  box( menuwin, 0, 0 );
  
  PrintInitAlien( xMaxSTD );
  refresh();
  wrefresh( menuwin );

  int n = 4;
  string choices[n] = { "PLAY", "SET DIFFICULTY", "HIGH SCORES", "EXIT" };

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

      mvwprintw( menuwin, 2*i+1, (width - choices[i].length())/2, choices[i].c_str() );
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
         
         show_hiscores();
         break;
         
       case 3:
        endwin(); 
        exit(1);
        break;
         
       default:
        break;
      }
      
      break;
    }
  }
  
  endwin();
}


float Game::SetDifficulty(){
  
  int yMaxSTD, xMaxSTD;

  int height = 9;
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


void Game::check_projectile_impact( class Aliens& A1 ){
  
  int xindex, yindex;
  
  for ( int i=0; i<project.size(); i++ ){
    
    project[i].print();
    project[i].move();
    
    if ( project[i].y <= 0 ){
      
      project.erase( project.begin() + i );
      break;
    }
    
    xindex = floor((project[i].x - A1.XL)/LENGTH);
    yindex = floor((project[i].y - A1.Y)/HEIGHT);
    
    if ( yindex >= 0 && yindex < A1.M ){
      if ( xindex >= 0 && xindex < A1.N ){
        
        if ( A1.AliensStatus[yindex][xindex] == 1 ){
          
          A1.AliensStatus[yindex][xindex] = 0;
          project.erase( project.begin() + i );
          
          Score += 100;
        }
      }
    }
  }
}


void Game::check_bomb_impact( class Aliens& A1, class Ship& ship, int& w ){
  
  for ( int i=0; i<bombs.size(); i++ ){
    
    bombs[i].print();
    bombs[i].move();
    
    if ( bombs[i].y > yMaxGame ){
      
      bombs.erase( bombs.begin() + i );
      break;
    }
    
    if ( bombs[i].y >= (ship.y+1) && bombs[i].y <= ship.max_y ){
      if ( bombs[i].x >= (ship.x-3) && bombs[i].x <= (ship.x+3) ){
        
        w = 1;
        break;
        
      }
    }
  }
}


void Game::generate_bomb( class Aliens& A1 ){
  
  //srand();
  float number = ((double) rand() / (RAND_MAX));;
  
  if ( number > 0.98 ) A1.ThrowBomb( bombs );
}


void Game::Play(){
  
  wclear( menuwin );
  int ch, w;
  
  srand( time(NULL) );
  
  Aliens A1( 1., 1., 3, 3, speed, gamewin );
  Ship ship( yMaxGame, xMaxGame, gamewin );
  

  string Info[2] = { "Return to Menu: F1", "Score: " };
 
  
  while(1) {
    
    werase( gamewin );
    
    // Print and update positions
    w = A1.UpdatePosition( yMaxGame, xMaxGame );
    
    box( gamewin, 0, 0 );
    box( infowin, 0, 0 );
    mvwprintw( infowin, 1, 1, Info[0].c_str() );
    mvwprintw( infowin, 1, xMaxInfo - 15, (Info[1] + to_string(Score)).c_str() );
    
    ship.print();
    
    ch = wgetch( gamewin );
    ship.action( ch, project );
    //box( gamewin, 0, 0 );
    
    // Throw bomb
    generate_bomb( A1 );
    
    // Check if either cluster or player were hit
    check_projectile_impact( A1 );
    check_bomb_impact( A1, ship, w );
    
    // Check if player won, lost or neither
    switch( w ){
      
     case 0:
      break;
      
     case 1:
      clear();
       
      mvprintw( yMaxGame/2, xMaxGame/2, lost.c_str() );
      refresh();
      usleep( 2000000 );
      
      Start();
      break;
    
     case 2:
      clear();
       
      mvprintw( yMaxGame/2, xMaxGame/2, won.c_str() );
      refresh();
      usleep( 2000000 );
      
      Start();
      return;
    }
        
    // Check borders of alien cluster
    A1.CheckAliensL();
    A1.CheckAliensR();
    A1.CheckAliensB();
    
    
    wrefresh( gamewin );
    wrefresh( infowin );
    

    if ( ch == KEY_F(1) ) Start();    
  
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

void Game::show_hiscores(){
  
  box( menuwin, 0, 0 );
  
  PrintInitAlien( xMaxSTD );
  refresh();
  wrefresh( menuwin );
  


  string h = "Press Any Key to Return";
  int i = 0;
  for( int i=0; i<5; i++ ){

    mvwprintw( menuwin, i+1, 2, names[i].c_str() );
    mvwprintw( menuwin, i+1, 27 - scores[i].length(), scores[i].c_str() );
  }
  
  wattron( menuwin, A_REVERSE );
  mvwprintw( menuwin, 7, 3, h.c_str() );
  wattroff( menuwin, A_REVERSE );
  
  wrefresh( menuwin );
  
  getch();
  werase( menuwin );
  ShowMenu();
}

void Game::init_hiscores(){
  
  ifstream hiscore_file( "data/hiscores.txt" );
  int i = 0;
  
  while( hiscore_file >> names[i] >> scores[i] && i<4){
    i++;
  }
  
  hiscore_file.close();
}

void Game::check_score(){
      
  ofstream outfile;
  
  outfile.open( "data/hiscores.txt" );
  
  bool check = true;
  int counter = 0;
  string new_name;
  
  for (int i=0; i<5; i++){
    
    
    if( Score>stoi(scores[i]) && check){
      
      new_hiscore( &new_name );
      outfile << new_name << " " << to_string(Score) << endl;
      check = false;
      counter++;
    }
    
    if( counter == 5 ) break;
    
    outfile << names[i] << " " << scores[i] << endl;
    
    counter++;
  }
  
  outfile.close();
}

void Game::new_hiscore( string * namePTR ){
  
  clear();
  echo();
  char str[20];
  
  box( hswin, 0, 0 );
  mvprintw( yMaxGame/2, xMaxGame/2 - 8, "NEW HIGH SCORE!" );
  mvprintw( yMaxGame/2, xMaxGame/2 - 8, "Enter a name with up to 20 characters" );
  
  refresh();
  wrefresh(hswin);
  
  mvwprintw( hswin, 1, 1, "Enter your name: " );  
  wrefresh( hswin );
  
  wgetstr( hswin, str );
  
  string name( str );
  
  *namePTR = name;
}
