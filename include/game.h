#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <cmath>

#include "projectile.h"
#include "ship.h"
#include "alien.h"

using namespace std;

typedef vector< Projectile > proj_vec;

class Game{
  
  public:
    Game( int );
    
    void start();
    void begin();
    void play();
    void show_menu();
    void print_init_alien( int );
    float set_difficulty();
    void init_logo();

    void check_projectile_impact( class Aliens& );
    void check_bomb_impact( class Aliens&, class Ship&, int& w );
    void generate_bomb( class Aliens& );

    //High Score related functions
    void show_hiscores();
    void check_score();    
    void init_hiscores();
    void new_hiscore( string * );

  private:
    
    string lost, won;
    
    proj_vec project; //Shot by player
    proj_vec bombs; // Shot by aliens
    
    WINDOW * menuwin;
    WINDOW * gamewin;
    WINDOW * infowin;
    WINDOW * hswin;
    
    float speed;
    float bomb_threshold = 98;
    
    int y_max_std,  x_max_std;   //Max Coordinates for Std Screen
    int y_max_menu, x_max_menu; //For Menu Screen
    int y_max_info, x_max_info; //For Info Screen
    float y_max_game, x_max_game; //For Game Screen
    
    int Score = 0;
    
    vector< string > alien_logo;

    string names[5];
    string scores[5];
};

