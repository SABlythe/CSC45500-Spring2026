#include "Token.hpp"

using namespace std;

#define ERROR -1

void printToken(TokType ttype, const string &tval)
{
  if (ttype==EOI)
    {
      cout << "End of Input" << endl;
      return;
    }

  switch(ttype)
    {
    case ID:
      cout << "ID: ";
      break;
    case INT:
      cout << "INT: ";
      break;
    case MINUS:
      cout << "MINUS: ";
      break;
    case PLUS:
      cout << "PLUS: " ;
      break;
    case MULT:
      cout << "MULT: ";
      break;
    case DIV:
      cout << "DIV: ";
      break;
    case PLUSPLUS:
      cout << "PLUSPLUS: ";
      break;
    default:
      cout << "ERROR: "; 
    }

  cout << "[" << tval << "]";
  
}

TokType getToken(istream &is, string &tval)
{
  static int DFA[8][256];
  static bool tableFilled=false;

  if (!tableFilled)
    {
      // initialize every transition (arrow) to be an error
      for (int row=0; row<=7; row++)
	for (int col=0; col<=255; col++)
	  DFA[row][col] = ERROR;

      //from state 0
      for (char ch='a'; ch <= 'z'; ch++)
	DFA[0][(unsigned int) ch] = 1;
      for (char ch='A'; ch <= 'Z'; ch++)
	DFA[0][(unsigned int) ch] = 1;

      for (char ch='0'; ch <= '9'; ch++)
	DFA[0][(unsigned int) ch] = 2;

      DFA[0][(unsigned int) '-'] = 3;
      DFA[0][(unsigned int) '+'] = 4;
      DFA[0][(unsigned int) '*'] = 5;
      DFA[0][(unsigned int) '/'] = 6;

      //from state 1 
      for (char ch='a'; ch <= 'z'; ch++)
	DFA[1][(unsigned int) ch] = 1;
      for (char ch='A'; ch <= 'Z'; ch++)
	DFA[1][(unsigned int) ch] = 1;
      for (char ch='0'; ch <= '9'; ch++)
	DFA[1][(unsigned int) ch] = 1;

      // from state 2
      for (char ch='0'; ch <= '9'; ch++)
	DFA[2][(unsigned int) ch] = 2;

      // from state 4
      DFA[4][(unsigned int) '+'] = 7;
      
      tableFilled=true;
    }


  // skip over whitespace ....
  char dummy;
  //is >> dummy;
  dummy = is.get();
  while (isspace(dummy))
    dummy = is.get();

  //oops ... read something that wasn't a space. We need it to be
  // part of the token we are tryting to get !!!
  is.unget();

  // nothing left in the input stream? no more tokens!
  if (!is)
    return EOI;

  // initialize states 
  int currState = 0;
  int prevState = ERROR;
  tval="";

  while(currState!= ERROR)
    {
      // back up the current state
      prevState = currState; 

      // move on to the next state. 
      char nextChar = is.get();
      int nextState = DFA[currState][(unsigned int) nextChar]; 
      currState = nextState;

      // as long as next character was valid, add it to token value
      if (currState!=ERROR)
	tval+=nextChar;
    }

  // last char we got was not part of token, so might be part of
  //   next token
  is.unget();

  switch (prevState)
    {
    case 1:
      return ID;
      break;
    case 2:
      return INT;
      break;
    case 3:
      return MINUS;
      break;
    case 4:
      return PLUS;
      break;
    case 5:
      return MULT;
      break;
    case 6:
      return DIV;
      break;
    case 7:
      return PLUSPLUS;
      break;
    default:
      is.get();
      return ERROR_TOK;
      break;
    }
  return ERROR_TOK /* change to TokType based on prevState */; 
  

  
  
}
