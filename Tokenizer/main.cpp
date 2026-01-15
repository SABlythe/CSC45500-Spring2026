#include <fstream>
#include <iostream>
#include <string>
#include "Token.hpp"
using namespace std;

int main(int argc, char *argv[])
{
  ifstream ifile(argv[1]);
  if (!ifile)
    {
      cerr << "Unable to open:" << argv[1] << endl;
      return 1;
    }

  string tval;
  TokType ttype;

  ttype=getToken(ifile, tval);

  while(ifile)
    {
      printToken(ttype, tval);
      cout << endl;

      ttype=getToken(ifile, tval);
    }

  cout << "Done tokenizing" << endl;
  return 0;
}
