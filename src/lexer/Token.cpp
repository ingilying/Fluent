#include "Token.h"

using namespace fluent;

Token::Token(std::string content,TokenType type,unsigned int line,std::string file_name) {
    this->content = content;
    this->type = type;
    this->line = line;
    this->file_name = file_name;
}

Token::Token(const std::string file_name,unsigned int line) {
    this->file_name =file_name;
    this->line = line;
}


Token::Token() 
: type(TokenType::NONE) {

}


Token::~Token() {
    
}

