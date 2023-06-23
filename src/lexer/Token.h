#ifndef TOKEN_H
#define TOKEN_H
#include <string>

namespace fluent{

enum class TokenType
{
    STRING,
    IDENTITY,
    NUMBER,
    FLOAT_NUMBER,
    SYMBOL,
    NONE
};


class Token
{
public:
    std::string content;
    TokenType type;
    unsigned int line;
    std::string file_name;
    explicit Token(std::string content,TokenType type,unsigned int line,const std::string file_name);
    explicit Token(const std::string file_name,unsigned int line);
    Token();
    ~Token();
};
}

#endif