#include "projectile.h"
#include "ship.h"
#include "alien.h"
#include "game.h"

using namespace std;

Game::Game( int h ){
  
  lost = "YOU DIED!";
  won = "NEXT WAVE";
  
  init_hiscores();
  init_logo();
}


void Game::begin(){
  
  initscr();
  raw();
  keypad( stdscr, true );
  noecho();
  
  int ch;
  
  mvprintw( 0, 1, "For the correct experiente, please maximize this window");
  mvprintw( 1, 1, "After that, press F3");
  
  refresh();
  
  while (1){
    ch = getch();
    if ( ch == KEY_F(3) ) break;
  }
  
  endwin();
  
  start();
}


void Game::start(){
  
  //Setting up ncurses
  initscr(); //Initializes the main window
  noecho();  //Don't echo inputs from the user
  cbreak();  
  curs_set(0);
  nodelay( stdscr, 0 );
  curs_set(FALSE);

  Score = 0; //Initial Score
  speed = 0.3; //Default speed

  //Variables for the Menu
  static int height = 9; 
  static int width = 30;

  //Get max number of rows and columbs from main window
  getmaxyx( stdscr, y_max_std, x_max_std ); 
  
  //Setting up Menu Window
  menuwin = newwin( height, width, y_max_std/2 , (x_max_std - width)/2 );
  keypad( menuwin, true );
  
  //Setting up Game Window 
  gamewin = newwin( y_max_std - 2, x_max_std, 0, 0 );
  keypad( gamewin, true );
  nodelay( gamewin, 1 );
  getmaxyx( gamewin, y_max_game,  x_max_game );
  
  //Setting up Info Window
  infowin = newwin( 3, x_max_std, y_max_std - 3, 0 );
  getmaxyx( infowin, y_max_info,  x_max_info );
  
  //Setting up High Score Window  
  hswin = newwin( 3, x_max_std - 12, y_max_std/2 , 4 );
  
  show_menu();
}


void Game::show_menu(){

  static int height = 9;
  static int width = 30;

  //Prints a box around the window
  box( menuwin, 0, 0 );
  
  print_init_alien( x_max_std );
  refresh();
  wrefresh( menuwin );

  int n = 4;

  //Options for the menu
  string choices[n] = { "PLAY", "SET DIFFICULTY", "HIGH SCORES", "EXIT" };

  int choice;
  int highlight = 0;
  
    while( 1 ){
    
    clear();
    
    //If the user changes the size of the screen, then the values update
    getmaxyx( stdscr, y_max_std, x_max_std );
    
    box( menuwin, 0, 0 );
    
    print_init_alien( x_max_std );
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

    //Comparing strings as ints using their ascii value
    switch( choice ){

    case KEY_UP:
      highlight--;
      if( highlight == -1 ) highlight = 0; //so it can't go down indefenitely

      break;

    case KEY_DOWN:
      highlight++;
      if( highlight == n ) highlight = n-1; //So it can go up indefenitely

      break;

    default:
      break;

    }

    //10 is equivalent to an enter
    if( choice == 10 ){
      
      werase( menuwin );
      clear();
      
      //Using the highlighet item as the choice
      switch( highlight ){
        
       case 0:
        play();
        break;
      
       case 1:
        set_difficulty();
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

//The comments for this function are the same as the ones for show_menu()
float Game::set_difficulty(){
  
  int y_max_std, x_max_std;

  int height = 9;
  int width = 30;

  getmaxyx( stdscr, y_max_std, x_max_std );

  box( menuwin, 0, 0 );
  
  print_init_alien( x_max_std );
  refresh();
  wrefresh( menuwin );

  int n = 4;
  string choices[n] = { "BABY", "NERD", "80's KID WITH NO LIFE", "RETURN" };

  int choice;
  int highlight = 0;

    while( 1 ){
    
    clear();
    
    getmaxyx( stdscr, y_max_std, x_max_std );

    //menuwin = newwin( height, width , y_max_std/2 , (x_max_std - width)/2 );
    box( menuwin, 0, 0 );
    
    print_init_alien( x_max_std );
    refresh();
    wrefresh( menuwin );
    //keypad( menuwin, true );

    for( int i=0; i<n; i++ ){

      if( i == highlight ){

        //Changes attribute for a window
        wattron( menuwin, A_REVERSE ); //Puts selected item in negative
      }

      mvwprintw( menuwin, i*2+1, (width - choices[i].length())/2, choices[i].c_str() );
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
        bomb_threshold = 98;
        break;
      
       case 1:
        speed = 0.5;
        bomb_threshold = 97;
        break;
        
       case 2:
        speed = 1;
        bomb_threshold = 96;
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
  show_menu();
  
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
        
        if ( A1.aliens_status[yindex][xindex] == 1 ){
          
          A1.aliens_status[yindex][xindex] = 0;
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
    
    if ( bombs[i].y > y_max_game ){
      
      bombs.erase( bombs.begin() + i );
      break;
    }
    
    if ( bombs[i].y >= (ship.y+1) && bombs[i].y <= ship.max_y ){
      if ( bombs[i].x >= (ship.x-3) && bombs[i].x <= (ship.x+3) ){
        
        bombs.clear();
        
        w = 1;
        break;
        
      }
    }
  }
}


void Game::generate_bomb( class Aliens& A1 ){
  
  //float number = ((double) rand() / (RAND_MAX));;
  int number = rand()%100;;
  
  if ( number > bomb_threshold ) A1.throw_bomb( bombs );
}


void Game::play(){
  
  //Clears the menu
  wclear( menuwin );
  int ch, w;
  
  srand( time(NULL) );
  
  //Creating our aliens and our ship
  Aliens A1( 1., 1., 4, 4, speed, gamewin );
  Ship ship( y_max_game, x_max_game, gamewin );
  
  //Options for infowin
  string Info[2] = { "Return to Menu: F1", "Score: " };
 
  
  while(1) {
    
    werase( gamewin );
    
    // Print and update positions
    w = A1.update_position( y_max_game, x_max_game );
    
    //reprint boxes
    box( gamewin, 0, 0 );
    box( infowin, 0, 0 );
    //reprint messages
    mvwprintw( infowin, 1, 1, Info[0].c_str() );
    mvwprintw( infowin, 1, x_max_info - 15, (Info[1] + to_string(Score)).c_str() );
    
    //Print ship
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
       
      mvprintw( y_max_game/2, x_max_game/2, lost.c_str() );
      refresh();
      usleep( 2000000 );

      check_score();
      start();
      break;
    
     case 2:
      clear();
       
      mvprintw( y_max_game/2, x_max_game/2, won.c_str() );
      refresh();
      usleep( 2000000 );
      
      speed += 0.2;

      play();
      return;
    }
        
    // Check borders of alien cluster
    A1.check_aliens_L();
    A1.check_aliens_R();
    A1.check_aliens_B();
    
    //Erase what's in the windows 
    wrefresh( gamewin );
    wrefresh( infowin );
    
    //re-starts the program
    if ( ch == KEY_F(1) ) start();
  
  }
  
  return;
}


void Game::print_init_alien( int x ){

  for( unsigned int i=0; i<alien_logo.size(); i++ ){

    mvprintw( i, x/2 - alien_logo[i].length()/2, alien_logo[i].c_str() );
  }
}

void Game::show_hiscores(){
  
  box( menuwin, 0, 0 );
  
  print_init_alien( x_max_std );
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
  show_menu();
}

void Game::init_hiscores(){
  
  //Fills names and scores with high scores data
  ifstream hiscore_file( "data/hiscores.txt" );
  int i = 0;
  
  if ( hiscore_file.fail() )   
    {
      cout << "Your hiscore.txt file is missing!" << endl;
      exit( 1 );
    }

  while( hiscore_file >> names[i] >> scores[i] && i<4){
    i++;
  }
  
  //Closes the file
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

  init_hiscores();
}

void Game::new_hiscore( string * namePTR ){
  
  clear();
  echo(); //So you can see what you're typing

  //ncurses is written in C, so a string doesn't work
  char str[40];
  
  box( hswin, 0, 0 );
  mvprintw( y_max_game/2, x_max_game/2 - 8, "NEW HIGH SCORE!" );
  mvprintw( y_max_game/2, x_max_game/2 - 8, "Enter a name with up to 20 characters with no spaces and no special characters" );
  
  refresh();
  wrefresh(hswin);
  
  mvwprintw( hswin, 1, 1, "Enter your name: " );  
  wrefresh( hswin );
  
  //Fill str by reference
  wgetstr( hswin, str );
  
  //create a string using std::string::string( *char )
  string name( str );
  
  *namePTR = name;

  return;
}


//Fill alien_logo
void Game::init_logo(){

  ifstream infile( "data/logos/alien_menu.txt" );

  if ( infile.fail() )   
    {
      cout << "Your alien_menu.txt file is missing!" << endl;
      exit( 1 );
    }

  string line;
  while( getline( infile, line ) ){

    alien_logo.push_back( line );
  }

  infile.close();
}
