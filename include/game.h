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
    
    void Start();
    void begin();
    void Play();
    void ShowMenu();
    void PrintInitAlien( int );
    float SetDifficulty();
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
    
    int yMaxSTD,  xMaxSTD;   //Max Coordinates for Std Screen
    int yMaxMenu, xMaxMenu; //For Menu Screen
    int yMaxInfo, xMaxInfo; //For Info Screen
    float yMaxGame, xMaxGame; //For Game Screen
    
    int Score = 0;
    
    vector< string > alien_logo;

    string names[5];
    string scores[5];
};

