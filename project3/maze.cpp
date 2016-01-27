#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
#include <stdlib.h>
#include "grid.h"
using namespace std;

bool isRouteWellFormed(string route);
int navigateSegment(int r, int c, char dir, int maxSteps);
int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps);
bool isInside(int r, int c); //checks if the cell is within the grid
void findDirMovement(char dir, int& radd, int& cadd); //finds unit vector(radd,cadd) in the direction 'dir'

int main()
{
  setSize(3,4);
  setWall(1,4);
  setWall(2,2);
  setWall(3,2);
  draw(3,1,3,3);
  assert(isRouteWellFormed("n2e1"));
  assert(isRouteWellFormed("N2eE01n0e2e1w1W1s1S1"));
  assert(isRouteWellFormed("W42"));
  assert(!isRouteWellFormed("3sn"));
  assert(!isRouteWellFormed("N144"));
  assert(!isRouteWellFormed("w2+n3"));
  assert(!isRouteWellFormed("e1x"));
  assert(navigateSegment(3, 1, 'N', 2) == 2);
  assert(navigateSegment(-1,1,'N',2) == -1);
  assert(navigateSegment(3,1,'x',2) == -1);
  assert(navigateSegment(3,1,'N',0) == 0);
  assert(navigateSegment(3,1,'N',1)==1);
  assert(navigateSegment(3,1,'N',3)==2);
  assert(navigateSegment(3,1,'E',3)==0);
  int len = -999;
  assert(navigateRoute(3,1, 3,4, "N2eE01n0s1S1e1w1e1W1e1", len) == 0  &&  len == 11);
  len = -999;
  assert(navigateRoute(-1,1,3,4,"N2",len)==2);
  assert(navigateRoute(3,1,-3,4,"N2",len)==2);
  assert(navigateRoute(3,1,3,4,"e1x",len)==2);
  assert(navigateRoute(3,1,3,4,"N2",len)==1 && len == 2);
  len = -999;
  assert(navigateRoute(3,1,3,4,"E3",len)==3 && len == 0);
  len = -999;
  assert(navigateRoute(3,1,3,1,"",len)==0 && len == 0);
  len = -999;
  setSize(20,20);
  assert(navigateRoute(1,1,16,1,"S15",len)==0 && len == 15);
  cout << "All tests succeeded" << endl;
}

bool isRouteWellFormed(string route)
{
  //iterate through entire string
  for(size_t i = 0; i < route.size(); i++)
    {
      if(isalpha(route[i]))
	{
	  //character at i is part of the alphabet
	  char lower = tolower(route[i]);
	  //check if the alphabet at i is a valid direction
	  if(lower != 'n' && lower != 's' && lower != 'e' && lower != 'w')
	    return false;
	}
      else if(isdigit(route[i]))
	{
	  //character at i is a digit
	  //the first character in the string must not be a digit, direction must be given first
	  if(i == 0)
	    return false;
	  //create a substring from character at i to either the end of the string 'route' or three characters forward
	  string sub = route.substr(i,3);
	  //first check if the substring is actually 3 characters long and then if the last two characters are both digits, that means a number with three digits was given(since it has already been determined that the character at i is a digit. In that case the input is invalid
	  if(sub.size() == 3 && isdigit(sub[1]) && isdigit(sub[2]))
	    return false;
	}
      else
	//the character at i is neither a digit nor does it belong to the alphabet
	return false;
    }
  //iterated through the whole string without finding anything that is invalid
  return true;
}

int navigateSegment(int r, int c, char dir, int maxSteps)
{
  //convert to lowercase to check if 'dir' is valid
  dir = tolower(dir);
  //check if (r,c) is valid and empt
  //check if a valid maxSteps was given
  //check if dir is valid
  if(!isInside(r,c) || isWall(r,c) || maxSteps < 0 ||
     (dir != 'n' && dir != 's' && dir != 'e' && dir != 'w'))
    return -1;
  int nsteps = 0, rx = r, cx = c, radd, cadd;
  findDirMovement(dir,radd,cadd); //find the values that need to be added to r and c to move in 'dir'
  //set (rx,cx) to the cell adjacent to (r,c) in the direction 'dir' 
  rx += radd;
  cx += cadd;
  while(isInside(rx,cx) && !isWall(rx,cx) && nsteps < maxSteps) //check if position to move into is empty and valid and less steps than maxSteps have been taken
    {
      nsteps++; //one step can be taken
      //change focus to cell that is adjacent to previously checked cell in the direction 'dir'
      rx += radd;
      cx += cadd;
    }
  return nsteps;
}

int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps)
{
  //check if input route is valid and if the starting and ending positions are empty and valid
  if(!isRouteWellFormed(route) || !isInside(sr,sc) || !isInside(er,ec)
     || isWall(sr,sc) || isWall(er,ec))
    return 2;
  nsteps = 0;
  size_t i = 0;
  //create two integers to keep track of the current position
  int pr = sr, pc = sc;
  //iterate through the whole 'route' string
  while(i != route.size())
    {
      //first character should be a direction character as checked by isRouteWellFormed
      char dir = route[i];
      //default number of steps in 'dir' is 1 unless specified
      int steps = 1;
      //checks if there is a next character and if its a digit
      if(i+1 < route.size() && isdigit(route[i+1]))
	{
	  //checks if there is another character and if it also is a digit
	  if(i+2 < route.size() && isdigit(route[i+2]))
	    {
	      //the number of steps in 'dir' is two digits
	      //find the substring that contains the number of steps and convert it to an integer
	      steps = (route[i+1] - '0')*10; //get the tens digit of the number of steps
	      steps += route[i+2] - '0'; //add the ones digit of the number of steps
	      //move i forward to the next direction character
	      i+=3;
	    }
	  else
	    {
	      //the number of steps in 'dir' is a single digit
	      //find the substring that contains the number of steps and convert it to an integer
	      steps = route[i+1] - '0'; //get the digit for the number of steps
	      //move i forward to the next direction character
	      i+=2;
	    }
	}
      else
	//no number of steps was given so move i forward to the next direction character and treat number of steps as default
	i++;
      //calculates how many steps it is possible to move in 'dir'
      int can_step = navigateSegment(pr,pc,dir,steps);
      //add this number to the running total
      nsteps += can_step;
      int radd, cadd;
      //find the direction to move in terms of a unit vector(radd,cadd)
      findDirMovement(dir,radd,cadd);
      //move current position the number of steps its possible to move in the direction 'dir'
      pr += can_step*radd; 
      pc += can_step*cadd;
      //checks if a wall or edge was hit before it the number of desired steps was reached
      if(can_step < steps)
	return 3;
    }
  //checks if the final position is the end point
  if(pr != er || pc != ec)
    return 1;
  else
    //final position is the end point
    return 0;
}

//create a unit vector(radd,cadd) in the given 'dir'
void findDirMovement(char dir, int& radd, int& cadd)
{
  radd = 0; 
  cadd = 0;
  switch(tolower(dir))
    {
    case 'n':
      radd = -1; //north is subtracting one from the row
      break;
    case 's':
      radd = 1; //south is adding one to the row 
      break;
    case 'e':
      cadd = 1; //east is adding one to column
      break;
    default:
      cadd = -1; //west is subtracting one from the column
      break;
    }
}

//checks if (r,c) is within the bounds of the grid
bool isInside(int r, int c)
{
  int rows = getRows();
  int cols = getCols();
  return r > 0 && r <= rows && c > 0 && c <= cols;
}
