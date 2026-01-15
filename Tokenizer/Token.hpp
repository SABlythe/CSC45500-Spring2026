#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <iostream>
#include <string>

enum TokType {ID, INT, MINUS, PLUS, MULT, DIV, PLUSPLUS, EOI};

void printToken(TokType t, const std::string& tval);

TokType getToken(std::istream &fromStream, std::string &intoVal); 


#endif
