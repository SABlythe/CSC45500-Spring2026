#include <fstream>
#include <iostream>
#include <string>
#include "Token.hpp"
using namespace std;



// after some thought, decided i wanted idlist to return
//  the number of id's in the list 
int idlist(istream &is)
{
  // data about nextToken
  string tval;
  TokType ttype;



  // check if next token is ID. if not, we need to be able
  //   to go "backwards" 
  int pos = is.tellg();     // remember where we are in the input
  ttype=getToken(is, tval);
  
  if (ttype!=ID)
    {
      // ERROR!!!!
      is.seekg(pos);       // go back to pos (the last known good location)
      cerr << "Expected ID, but didn't find it!" << endl;
      return -9999999;
    }

  // do we have a comma? 
  pos = is.tellg();
  ttype=getToken(is, tval);


  if (ttype!=COMMA)
    {
      is.seekg(pos);
      // <idlist> -> ID matched !!!
      return 1;
    }

  // if we get here, we are trying to match
  //  <idlist> -> ID COMMA <idlist>

  int recursiveCount = idlist(is); 
  return 1+ recursiveCount;
}

