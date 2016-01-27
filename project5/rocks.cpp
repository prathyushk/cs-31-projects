#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cstring>
#include <cctype>
#include "utilities.h"
using namespace std;

const int MAXWORDS = 9000;

int manageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);
void findRocksAndPebbles(const char secret[], const char guess[], int& rocks, int& pebbles);
bool exists(const char words[][MAXWORDLEN+1], int nWords, const char[]);
bool isValid(const char word[]);

int main()
{
  //values to keep track of game statistics
  int sum = 0, min = -1, max = 0;
  char wordList[MAXWORDS][MAXWORDLEN+1];
  int nWords = loadWords(wordList, MAXWORDS);
  if(nWords < 1)
    {
      cout << "No words were loaded, so I can't play the game." << endl;
      return -1;
    }
  cout << "How many rounds do you want to play? ";
  int rounds;
  cin >> rounds;
  cin.ignore(10000,'\n'); //cin does not take the \n which will interfere with getting input in the future so characters up to and including the \n are ignored
  if(rounds < 1)
    {
      cout << "The number of rounds must be positive." << endl;
      return -1;
    }
  for(int i = 1; i <= rounds; i++) //run for each round
    {
      cout << endl;
      cout << "Round " << i << endl;
      int wordnum = randInt(0,nWords-1); //generate random index for word in the "dictionary"
      cout << "The secret word is " << strlen(wordList[wordnum]) << " letters long." << endl;
      int tries = manageOneRound(wordList, nWords, wordnum); //run round
      if(tries == 1)
	cout << "You got it in 1 try." << endl;
      else
	cout << "You got it in " << tries << " tries." << endl;
      sum += tries; //keeps track of sum of scores for average
      if(tries < min || min < 0)
	min = tries;
      if(tries > max)
	max = tries;
      cout.precision(2);
      cout.setf(ios::fixed);
      cout << "Average: " << static_cast<double>(sum)/i << ", minimum: " << min << ", maximum: " << max << endl; //i is the round number so can be used to calculate average
    }
}

bool exists(const char words[][MAXWORDLEN+1], int nWords, const char word[])
{
  //checks if 'word' is contained in 'words'
  for(int i = 0; i < nWords; i++)
    {
      if(!strcmp(words[i],word)) //strcmp will return 0 if theyre equal
	return true;
    }
  return false;
}

bool isValid(const char word[])
{
  //checks if 'word' consists of all lower case characters that are 4-6 in number
  int len = strlen(word);
  for(int i = 0; word[i] != '\0'; i++)
    {
      if(!islower(word[i]))
	  return false;
    }
  if(len > MAXWORDLEN || len < MINWORDLEN)
    return false;
  return true; //none of the conditions have been triggered, 'word' is valid
}

void findRocksAndPebbles(const char secret[], const char guess[], int& rocks, int& pebbles)
{
  rocks = 0;
  pebbles = 0;
  bool marks[6] = {false, false, false, false, false ,false}; //keeps track of characters that have already been accounted for in secret
  bool guessMarks[6] = {false, false, false, false, false, false}; //keeps track of characters that have been already been accounted for in guess
  //find rocks
  for(int i = 0; secret[i] != '\0'; i++)
    {
      if(guess[i] == '\0') //reached the end of guess, this is the end of checking for rocks
	break;
      if(secret[i] == guess[i])
	{
	  //found rock, increment and mark the locations
	  rocks++;
	  marks[i] = true;
	  guessMarks[i] = true;
	}
    }
  //find pebbles
  for(int i = 0; secret[i] != '\0'; i++)
    {
      //if a character in secret has already been marked, then we know it is a rock already so no need to check if its a pebble
      if(!marks[i])
	{
	  for(int j = 0; guess[j] != '\0'; j++)
	    {
	      //make sure character j of guess has not already been marked and check if it is a pebble
	      if(!guessMarks[j] && secret[i] == guess[j])
		{
		  //found pebble, increment and mark the locations
		  pebbles++;
		  marks[i] = true;
		  guessMarks[j] = true;
		  break; //done with this character of secret
		}
	    }
	}
    }  
}

int manageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum)
{
  if(nWords < 1 || wordnum < 0 || wordnum >= nWords)
    return -1;
  int tries = 0; //keeps track of number of attempts used
  while(1)
    {
      cout << "Probe word: ";
      char guess[101];
      cin.getline(guess,101);
      int len = strlen(guess);
      if(!isValid(guess)) //checks if the guess is a valid string
	cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl; 
      else if(!exists(words,nWords,guess)) //checks if guess is contained in the word list
	cout << "I don't know that word." << endl;
      else
	{
	  tries++;
	  int rocks, pebbles;
	  findRocksAndPebbles(words[wordnum], guess, rocks, pebbles); //counts rocks and pebbles in the guess
	  if(rocks == strlen(words[wordnum]) && len == strlen(words[wordnum])) //if the number of rocks it found are equal to the number of characters in the secret word and the length of the guess is equal to the length of the secret word, then the correct word has been entered
	    return tries;
	  cout << "Rocks: " << rocks << ", Pebbles: " << pebbles << endl;
	}
    }
}
