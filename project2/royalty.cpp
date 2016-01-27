#include <iostream>
#include <string>

using namespace std;

int main()
{
  //get all the necessary input
  int units;
  string title;
  double price;
  bool premium;
  cout << "Units sent: ";
  cin >> units;
  cin.ignore(10000, '\n'); //so getline doesn't immediately pick up the newline
  cout << "Title: ";
  getline(cin, title);
  cout << "Base price: ";
  cin >> price;
  cin.ignore(10000, '\n'); //so getline doesn't immediately pick up the newline
  cout << "Premium item? (y/n): ";
  string yn;
  getline(cin, yn);
  cout << "---" << endl;
  //make sure all input is valid
  //check to see if units is negative
  if(units < 0)
    {
      cout << "The number of units sent must be nonnegative." << endl;
      return 1; //exit the program with error code
    }
  //check to see if the title is an empty string
  if(title == "")
    {
      cout << "You must enter a title." << endl;
      return 1; //exit the program with error code
    }
  //check to see if the price is negative
  if(price < 0)
    {
      cout << "The base price must be nonnegative." << endl;
      return 1; //exit the program with error code
    }
  //check to see if it is premium or not and assign true or false to a boolean if the input is valid, otherwise exit
  if(yn == "y")
    premium = true;
  else if(yn == "n")
    premium = false;
  else
    {
      cout << "You must enter y or n." << endl;
      return 1; //exit the program with error code
    }
  double royalties = 0;
  if(units > 1200)
    {
      //calculates royalties for up to the first the units that are above the 1200 number mark
      royalties += (units-1200)*price*.14;
      units -= units-1200; //already calculated units for units above 1200 so these are subtracted
    }
  if(units > 400)
    {
      //calculates royalties for the units 401-1200(if there are that many) and adds to the running total
      if(premium)
	royalties += (units-400)*price*.16;
      else
	royalties += (units-400)*price*.13;
      units -= units-400; //already calculated for units above 400 so these are subtracted
    }
  //units should be less than or equal to 400 by now so this calculates the royalties for 1-400
  royalties += units*price*.09;
  cout.setf(ios::fixed); //used fixed point
  cout.precision(2); //two digits after the decimal point
  cout << title << " earned $" << royalties << " in royalties." << endl; //print the output text while calculating the royalties using another function
  return 0;
}


