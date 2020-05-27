#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "game.h"

using namespace std;


int main(){
  
  Game SpaceInvaders;
  
  SpaceInvaders.start();
  
  return 0;
}

