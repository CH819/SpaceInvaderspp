#include <iostream>

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

  
  gamewin = win;
  
  mat AliensStatus_init( M, vec( N, 1 ) );
  AliensStatus = AliensStatus_init;
  
}

void Aliens::UpdatePosition( float max_x ){
  
  float next_x;
  
  for ( float j=0; j<M; j++ ){
    for ( float i=0; i<N; i++ ){
        
        if ( AliensStatus[j][i] == 1 ) PrintAlien( Y + HEIGHT*j, XL + LENGTH*i );
        
        else PrintWhiteSpace( Y + HEIGHT*j, XL + LENGTH*i );
    
    }
  }
  
  usleep( DELAY );
  
  if ( direction > 0 ){
    
    next_x = XR + direction;
    
    if( next_x  >= max_x - (LimR-1)*LENGTH  ){
      
      direction *=-1;
      Y++;
    }
    
    else{
      
      XR += direction;
      XL += direction;
    }
  }
  
  else{
    
    next_x = XL + direction;
    
    if( next_x < LimL*LENGTH ){
      
      direction *= -1;
      Y++;
    }
    
    else{
      
      XR += direction;
      XL += direction;
    }
  }
}

void Aliens::CheckAliensL(){
  
  int counter = 0;
  for( int i=0; i<M; i++ ){
    

    if ( AliensStatus[i][-LimL] == 1 ) counter++;
  }
  
  if ( counter == 0 ) LimL--;
  
}

void Aliens::CheckAliensR(){
  
  for( int i=0; i<M; i++ ){
    
    if ( AliensStatus[i][LimR-1] == 1 ) return;
  }
  
  LimR--;
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
