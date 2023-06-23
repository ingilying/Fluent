#ifndef LEXER_H
#define LEXER_H
#include "Token.h"
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace fluent {

// 终止符号
const char symbols_end[] = {'+', '-', '*', '/', '.', '-',
                            ',', '>', '<', '=', '!', ';'};
const size_t sym_len = sizeof(symbols_end);

/*
  类: Lexer
  作用: 词法分析器，将输入文件中的字符流根据词法提取Token
  用法:
  '''
  fluent::Lexer lexer("source.fl");
  if(lexer.Start()){ 
    auto tokens = lexer.GetTokens();
    for(auto i : tokens) {
      std::cout<< i.content << std::endl;
    }
  }
  '''
 */
class Lexer {
private:
  std::vector<Token> tokens;
  std::stringstream stream;
  unsigned int lines;
  std::string file_name;
  // 解析数字
  std::optional<Token> Number();
  // 解析符号
  std::optional<Token> Symbol();
  // 判断是否是结束符
  static bool isend(const char &c);

public:
  // 初始化
  explicit Lexer(const std::string file_name);
  // 开始解析
  bool Start();
  // 从字符串流中读取一个字符
  std::optional<char> Read();
  // 将一个字符放回字符串流
  void Back(char c);
  std::vector<Token> GetTokens();
  ~Lexer();
};
} // namespace fluent

#endif