#include <unistd.h>
#include <ncurses.h>
#include <vector>

#define ALIENH1 "     ___      "
#define ALIENH2 " ___/   \\___ "
#define ALIENH3 "/   '---'   \\"
#define ALIENH4 "'--_______--' "

#define DALIEN1 "              "

#define LENGHT 14
#define HEIGHT 4

#define DELAY 30000

using namespace std;

typedef vector< double > vec;
typedef vector< vec > mat;

class Aliens{

 public:

  //Initialize alient with uppper y and left x
  Aliens( float, float, int, int );
  //~Aliens( );

  //void GetXPosition( float* );
  void UpdatePosition( float );

  void PrintAlien( float, float );
  void PrintWhiteSpace( float, float );

 private:

  float XL, XR; //Horizontal positions: Left and Right
  float Y; //Vertical position of upper part
  float direction;
  mat AliensStatus;
  
  int N, M;
};
