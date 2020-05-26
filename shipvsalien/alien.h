#include <unistd.h>
#include <ncurses.h>
#include <vector>

#define ALIENH1 "     ___      "
#define ALIENH2 " ___/   \\___ "
#define ALIENH3 "/   '---'   \\"
#define ALIENH4 "'--_______--' "
#define DALIEN1 "**************"
#define DALIEN2 "              "

#define LENGHT 14
#define HEIGHT 4

#define DELAY 30000

using namespace std;

typedef vector< double > vec;
typedef vector< vec > mat;

class Alien{

 public:

  //Initialize alient with uppper y and left x
  Alien( int, int );

  void GetXPosition( int * );
  void UpdatePosition( int );

  void PrintAlien( int, int );
  void PrintWhiteSpace( int, int );

 private:

  int XL, XR; //Horizontal positions: Left and Right
  int Y; //Vertical position of upper part
  int direction;
  int Counter;
};
