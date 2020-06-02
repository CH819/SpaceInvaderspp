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
  
  LimL = 0;
  LimR = N;
  LimB = M;
  
  gamewin = win;
  
  mat AliensStatus_init( M, vec( N, 1 ) );
  AliensStatus = AliensStatus_init;
  
}


int Aliens::UpdatePosition( float max_y, float max_x ){
  
  float next_x;
  
  if ( LimB == 0 ) return 2;
    
  for ( float j=0; j<M; j++ ){
    for ( float i=0; i<N; i++ ){
        
        if ( AliensStatus[j][i] == 1 ) PrintAlien( Y + HEIGHT*j, XL + LENGTH*i );

    }
  }
  
  usleep( DELAY );
  
  if ( direction > 0 ){
    
    next_x = XR + direction;
    
    if( next_x  >= max_x - (LimR-1)*LENGTH  ){
      
      direction *=-1;
      Y++;
      
      if( Y + LimB*HEIGHT >= max_y - 4) return 1;
    }
    
    else{
      
      XR += direction;
      XL += direction;
    }
  }
  
  else{
    
    next_x = XL + direction;
    
    if( next_x < LimL*LENGTH + 1){
      
      direction *= -1;
      Y++;
      
      if( Y + LimB*HEIGHT >= max_y - 4) return 1;
    }
    
    else{
      
      XR += direction;
      XL += direction;
    }
  }
  
  return 0;
}


void Aliens::CheckAliensL(){
  
  for( int i=0; i<M; i++ ){
    

    if ( AliensStatus[i][-LimL] == 1 ) return;
  }
  
  LimL--;
  
}


void Aliens::CheckAliensR(){
  
  for( int i=0; i<M; i++ ){
    
    if ( AliensStatus[i][LimR-1] == 1 ) return;
  }
  
  LimR--;
}


void Aliens::CheckAliensB(){
  
  for( int i=0; i<N; i++ ){
    

    if ( AliensStatus[LimB-1][i] == 1 ) return;;
  }
  
  LimB--;
  
}


void Aliens::PrintAlien( float y, float x ){

  mvwprintw( gamewin, y+0, x, ALIENH1 );
  mvwprintw( gamewin, y+1, x, ALIENH2 );
  mvwprintw( gamewin, y+2, x, ALIENH3 );
  mvwprintw( gamewin, y+3, x, ALIENH4 );
}


void Aliens::PrintWhiteSpace( float y, float x ){

  mvwprintw( gamewin, y+0, x, DALIEN1 );
  mvwprintw( gamewin, y+1, x, DALIEN1 );
  mvwprintw( gamewin, y+2, x, DALIEN1 );
  mvwprintw( gamewin, y+3, x, DALIEN1 );
}


void Aliens::ThrowBomb( proj_vec& bombs ){
  
  float yindex_attack = 0;
  float xindex_attack = 0;
  
  do {
    
    xindex_attack = rand()%N;
    
    for (int i=(M-1); i>=0; i--){
      
      yindex_attack = i;
      
      if ( AliensStatus[yindex_attack][xindex_attack] == 1 ) break;
    }
  
  } while ( AliensStatus[yindex_attack][xindex_attack] != 1 );
  
  
  float x_coor = XL + (xindex_attack + 0.5)*LENGTH;
  float y_coor = Y + (2 + yindex_attack)*HEIGHT;
  
  Projectile bomb( y_coor, x_coor, -0.3, gamewin );
  bombs.push_back( bomb );
}
