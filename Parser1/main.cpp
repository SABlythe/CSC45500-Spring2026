#include <fstream>
#include <iostream>
#include <string>
#include "Token.hpp"
using namespace std;

// data about nextToken
string tval;
TokType ttype;

// after some thought, decided i wanted idlist to return
//  the number of id's in the list 
int idlist(istream &is)
{
  if (ttype!=ID)
    {
      // ERROR!!!!
      cerr << "Expected ID, but didn't find it!" << endl;
      return -9999999;
    }

  // consume the ID token, and get the next token
  ttype=getToken(is, tval);


  if (ttype!=COMMA)
    {
      // <idlist> -> ID matched !!!
      return 1;
    }

  // if we get here, we are trying to match
  //  <idlist> -> ID COMMA <idlist>

  // consume the ID token, and get the next token
  ttype=getToken(is, tval);

  int recursiveCount = idlist(is); 
  return 1+ recursiveCount;
}

int main(int argc, char *argv[])
{
  ifstream ifile(argv[1]);
  if (!ifile)
    {
      cerr << "Unable to open:" << argv[1] << endl;
      return 1;
    }

  // get next token in input stream
  ttype=getToken(ifile, tval);

  cout << "There are " << idlist(ifile) << " id's" << endl;

  cout << "Done parsing" << endl;
  return 0;
}
