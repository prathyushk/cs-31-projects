#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);

int main()
{
  string h[8] = { "bernie", "hillary", "donald", "jeb", "", "carly", "ben", "donald" };
  assert(lookup(h, 7, "carly") == 5);
  assert(lookup(h, 8, "donald") == 2);
  assert(lookup(h, 2, "donald") == -1);
  assert(lookup(h, -4, "donald") == -1);
  string h1[5] = { "addy", "donald", "donald", "donald", "donald" };
  assert(lookup(h1, 5, "donald") == 1);
  assert(positionOfMax(h, 7) == 3);
  assert(positionOfMax(h, -7) == -1);
  assert(positionOfMax(h1, 5) == 1);
  string g[4] = { "bernie", "hillary", "jeb", "carly" };
  assert(differ(h, 4, g, 4) == 2);
  assert(differ(h, -4, g, 4) == -1);
  assert(differ(h, 4, g, -4) == -1);
  assert(differ(h, 3, g, 2) == 2);
  assert(differ(h, 2, g, 3) == 2);
  assert(appendToAll(g, -4, "?") == -1);
  assert(appendToAll(g, 0, "?") == 0 && g[0] == "bernie" && g[3] == "carly");
  assert(appendToAll(g, 4, "") == 4 && g[0] == "bernie" && g[3] == "carly");
  assert(appendToAll(g, 4, "?") == 4 && g[0] == "bernie?" && g[3] == "carly?");
  assert(rotateLeft(g, 4, 4) == -1);
  assert(rotateLeft(g, -4, 1) == -1);
  assert(rotateLeft(g, 4, -5) == -1);
  assert(rotateLeft(g, 4, 3) == 3 && g[1] == "hillary?" && g[3] == "carly?");
  assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jeb?" && g[3] == "hillary?");
  string e[5] = { "donald", "jeb", "", "carly", "bob" };
  assert(subsequence(h, 7, e, 4) == 2);
  assert(subsequence(h, 2, e, 4) == -1);
  assert(subsequence(h, -7, e, 4) == -1);
  assert(subsequence(h, 7, e, -4) == -1);
  assert(subsequence(h, 7, e, 5) == -1);
  assert(subsequence(h, 7, h, 7) == 0);
  assert(subsequence(h, 0, e, 0) == 0);
  string d[5] = { "hillary", "hillary", "hillary", "ben", "ben" };
  assert(countRuns(d, 5) == 2);
  assert(countRuns(d, -5) == -1);
  assert(countRuns(d, 0) == 0);
  string d1[1] = { "ben" };
  assert(countRuns(d, 1) == 1);
  string f[3] = { "jeb", "donald", "marco" };
  assert(lookupAny(h, 7, f, 3) == 2);
  assert(lookupAny(h, 0, f, 3) == -1);
  assert(lookupAny(h, 7, f, 0) == -1);
  assert(lookupAny(h, -7, f, 3) == -1);
  assert(lookupAny(h, 7, f, -3) == -1);
  string f2[2] = { "jeb", "donald" };
  string f3[2] = { "john", "ben" };
  assert(lookupAny(f2, 2, f3, 2) == -1);
  assert(flip(f, 3) == 3 && f[0] == "marco" && f[2] == "jeb");
  assert(flip(f, -3) == -1);
  string f1[4] = { "john", "jeb", "carly", "marco"};
  assert(flip(f1, 4) == 4 && f1[0] == "marco" && f1[1] == "carly" && f1[2] == "jeb");  
  assert(split(h, 7, "carly") == 3 && h[3] == "carly");
  assert(split(h, 0, "carly") == 0);
  assert(split(h, -5, "carly") == -1);
  assert(split(h, 7, "zack") == 7);
  cout << "All tests succeeded" << endl;
  return 0;
}

int appendToAll(string a[], int n, string value)
{
  if(n < 0)
    return -1;
  //add to every element in a[]
  for(int i = 0; i < n; i++)
    a[i] += value;
  return n;
}

int lookup(const string a[], int n, string target)
{
  if(n < 0)
    return -1;
  //look at every element in a[] and see if it is equal to target
  for(int i = 0; i < n; i++)
    if(a[i] == target)
      return i; //found at index i
  return -1; //not found
}

int positionOfMax(const string a[], int n)
{
  if(n <= 0) //if the size is 0 or less, then there is no max
    return -1;
  int maxPos = 0; //assume the max is at position 0 first
  for(int i = 0; i < n; i++)
    {
      if(a[i] > a[maxPos]) //check if every element in a[] is greater than the current max at the time
	maxPos = i; //the new max is at i
    }
  return maxPos;
}

int rotateLeft(string a[], int n, int pos)
{
  if(n < 0 || pos >= n || pos < 0) //pos has to be a valid index in the array 
    return -1;
  string temp = a[pos]; //this is the string that will be moved to the end
  for(int i = pos; i < n-1; i++) //left shift everything from pos + 1
    {
      a[i] = a[i+1];
    }
  a[n-1] = temp; //place the removed string at the end
  return pos;
}

int countRuns(const string a[], int n)
{
  if(n < 0)
    return -1;
  if(n == 0) //there are no runs in an array size 0
    return 0;
  int count = 1; //if there is at least one element that means there is at least 1 run
  for(int i = 0; i < n - 1; i++) //every time one element is different from the next, that means there is another run
    {
      if(a[i] != a[i+1])
	count++;
    }
  return count;
}

int flip(string a[], int n)
{
  if(n < 0)
    return -1;
  for(int i = 0; i < n/2; i++) //rotate around the center, with an even n, the two centers are swapped and with an odd n, the center stays in place
    {
      string temp = a[i];
      a[i] = a[n-1-i];
      a[n-1-i] = temp;
    }
  return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
  if(n1 < 0 || n2 < 0)
    return -1;
  int lowest; //find which array is shorter
  if(n1 < n2)
    lowest = n1;
  else
    lowest = n2;
  for(int i = 0; i < lowest; i++) //see if there is a different element before the shortest array runs out
    {
      if(a1[i] != a2[i])
	return i;
    }
  return lowest;
}


int subsequence(const string a1[], int n1, const string a2[], int n2)
{
  int difference = n1 - n2; //the maximum position in a1 that can hold all of a2
  if(difference < 0 || n1 < 0 || n2 < 0) //if a2 is longer than a1, then a1 cannot hold a2
    return -1;
  for(int i = difference; i >= 0; i--) //starting from the maximum position that can hold a2, and moving left, check if a2 is contained
    {
      bool equal = true; //assumes it is contained until one that does not match up is found
      for(int j = i; j < i + n2; j++) //loops through the subsequence in a1 with all of a2 and checks if they are equal
	{
	  if(a1[j] != a2[j-i])
	    {
	      equal = false;
	      break;
	    }
	}
      if(equal)
	return i;
    }
  return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
  if(n1 < 0 || n2 < 0)
    return -1;
  for(int i = 0; i < n1; i++) //loops through every element in a1
    {
      for(int j = 0; j < n2; j++) //checks if the ith element in a1 is equal to any element in a2
	{
	  if(a1[i] == a2[j])
	    return i;
	}
    }
  return -1;
}


int split(string a[], int n, string splitter)
{
  if(n < 0)
    return -1;
  int greaterPos = 0; //first assumes there are no strings < splitter
  for(int i = 0; i < n; i++) //loops through whole array
    {
      if(a[i] < splitter)
	{
	  greaterPos++; //greaterPos must be moved up 1 because there needs to be one string before it since there is one more string that is < splitter now
	  if(i >= greaterPos) //checks if this string is on the side that is greater than splitter
	    {
	      //if so, the string must be moved to before greaterPos, so greaterPos-1 and i are swapped
	      string temp = a[i];
	      a[i] = a[greaterPos-1];
	      a[greaterPos-1] = temp;
	    }
	}
    }
  //make sure that if a string equal to splitter is in the array, it is in the middle.
  for(int i = 0; i < n; i++)
    {
      if(a[i] == splitter && i != greaterPos)
	{
	  string temp = a[greaterPos];
	  a[greaterPos] = a[i];
	  a[i] = temp;
	}
    }
  return greaterPos;
}
