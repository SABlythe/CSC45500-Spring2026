#include <fstream>
#include <iostream>
#include <string>
#include "Token.hpp"
using namespace std;



int idlist(istream &is);

int main(int argc, char *argv[])
{
  ifstream ifile(argv[1]);
  if (!ifile)
    {
      cerr << "Unable to open:" << argv[1] << endl;
      return 1;
    }

  cout << "There are " << idlist(ifile) << " id's" << endl;

  cout << "Done parsing" << endl;
  return 0;
}
