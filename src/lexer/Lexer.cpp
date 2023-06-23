#include "Lexer.h"
#include <easylogging++.h>
#include <fstream>

using namespace fluent;

Lexer::Lexer(const std::string file_name) {
  this->file_name = file_name;
  std::ifstream fs;
  fs.open(file_name);
  if (!fs.is_open()) {
    LOG(ERROR) << file_name << "cannot be opened!";
  }
  this->stream = std::stringstream();
  stream << fs.rdbuf();
  this->tokens = std::vector<Token>();
}

void Lexer::Back(char c) { this->stream.putback(c); }

std::optional<char> Lexer::Read() {
  char c;
  if (this->stream.eof()) {
    return std::nullopt;
  }
  this->stream >> c;
  return {c};
}

bool Lexer::Start() {
  lines = 1;

  while (!this->stream.eof()) {
    auto co = this->Read();
    if (co.has_value()) {
      char c = co.value();
      if ('0' <= c && c <= '9') { // Number
        this->Back(c);
        auto t = Number();
        if (t.has_value()) {
          Token tt = t.value();
          this->tokens.push_back(tt);
        } else
          return false;
      } else if (c == '\r' || c == ' ') {
        continue;
      } else if (c == '\n') {
        this->lines += 1;
      }
    } else {
      LOG(INFO) << "File Finish";
    }
  }
}

std::optional<Token> Lexer::Number() {
  Token current;
  current.file_name = this->file_name;
  current.line = this->lines;
  current.type = TokenType::NUMBER;
  std::string s;
  while (!this->stream.eof()) {
    char c = this->Read().value();
    if ('0' <= c && c <= '9') {
      s.push_back(c);
    } else if (c == '.') {
      s.push_back(c);
    } else if (isend(c)) {
      break;
    } else {
      LOG(ERROR) << current.file_name << ": Line " << current.line;
      LOG(ERROR) << "Not a standard number token";
      return std::nullopt;
    }
  }
  current.content = s;
  return current;
}

bool Lexer::isend(const char &c) {
  for (int i = 0; i < sym_len; i++)
    if (symbols_end[i] == c)
      return true;
  return false;
}

std::vector<Token> Lexer::GetTokens() {
  return this->tokens;
}