#include <iostream>
#include <fstream>
#include <time.h>

#include "projectile.h"
#include "alien.h"

using namespace std;


Aliens::Aliens( float y, float x, int n, int m, float dir, WINDOW * win ){
  
  XL = x;
  XR = x + LENGTH;
  
  Y = y;
  
  direction = dir;
  
  N = n; //Number of columns
  M = m; //Number of rows
  
  lim_l = 0;
  lim_r = N;
  lim_b = M;
  
  gamewin = win;
  
  mat aliens_status_init( M, vec( N, 1 ) );
  aliens_status = aliens_status_init; 

  init_logo();
}


int Aliens::update_position( float max_y, float max_x ){
  
  float next_x;
  
  if ( lim_b == 0 ) return 2;
    
  for ( float j=0; j<M; j++ ){
    for ( float i=0; i<N; i++ ){
        
        if ( aliens_status[j][i] == 1 ) print_alien( Y + HEIGHT*j, XL + LENGTH*i );

    }
  }
  
  usleep( DELAY );
  
  if ( direction > 0 ){
    
    next_x = XR + direction;
    
    if( next_x  >= max_x - (lim_r-1)*LENGTH  ){
      
      direction *=-1;
      Y++;
      
      if( Y + lim_b*HEIGHT >= max_y - 4) return 1;
    }
    
    else{
      
      XR += direction;
      XL += direction;
    }
  }
  
  else{
    
    next_x = XL + direction;
    
    if( next_x < lim_l*LENGTH + 1){
      
      direction *= -1;
      Y++;
      
      if( Y + lim_b*HEIGHT >= max_y - 4) return 1;
    }
    
    else{
      
      XR += direction;
      XL += direction;
    }
  }
  
  return 0;
}


void Aliens::check_aliens_L(){
  
  for( int i=0; i<M; i++ ){
    

    if ( aliens_status[i][-lim_l] == 1 ) return;
  }
  
  lim_l--;
  
}


void Aliens::check_aliens_R(){
  
  for( int i=0; i<M; i++ ){
    
    if ( aliens_status[i][lim_r-1] == 1 ) return;
  }
  
  lim_r--;
}


void Aliens::check_aliens_B(){
  
  for( int i=0; i<N; i++ ){
    

    if ( aliens_status[lim_b-1][i] == 1 ) return;;
  }
  
  lim_b--;
  
}


void Aliens::print_alien( float y, float x ){

  for( unsigned int i=0; i<alien_logo.size(); i++){

    mvwprintw( gamewin, y+i, x, alien_logo[i].c_str() );
  }
}


void Aliens::print_white_space( float y, float x ){

  mvwprintw( gamewin, y+0, x, DALIEN1 );
  mvwprintw( gamewin, y+1, x, DALIEN1 );
  mvwprintw( gamewin, y+2, x, DALIEN1 );
  mvwprintw( gamewin, y+3, x, DALIEN1 );
}


void Aliens::throw_bomb( proj_vec& bombs ){
  
  float yindex_attack = 0;
  float xindex_attack = 0;
  
  do {
    
    xindex_attack = rand()%N;
    
    for (int i=(M-1); i>=0; i--){
      
      yindex_attack = i;
      
      if ( aliens_status[yindex_attack][xindex_attack] == 1 ) break;
    }
  
  } while ( aliens_status[yindex_attack][xindex_attack] != 1 );
  
  
  float x_coor = XL + (xindex_attack + 0.5)*LENGTH;
  float y_coor = Y + (2 + yindex_attack)*HEIGHT;
  
  Projectile bomb( y_coor, x_coor, -0.3, gamewin );
  bombs.push_back( bomb );
}

void Aliens::init_logo(){

  ifstream infile( "data/logos/alien.txt" );

  if ( infile.fail() )   
    {
      cout << "Your alien.txt file is missing!" << endl;
      exit( 1 );
    }

  string line;
  while( getline( infile, line ) ){

    alien_logo.push_back( line );
  }
}
