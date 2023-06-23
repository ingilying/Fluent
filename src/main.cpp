#include "lexer/Lexer.h"
#include <easylogging++.h>
#include <magic_enum.hpp>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
  LOG(INFO) << "Fluent Language by Ingil Ying";
  fluent::Lexer lexer("/home/ingil/projects/fluent/test/test.fl");
  if (lexer.Start()) {
    auto tokens = lexer.GetTokens();
    for (auto i : tokens) {
      LOG(INFO) << i.content << " " << magic_enum::enum_name(i.type);
    }
  } else
    LOG(ERROR) << "lex the file failed.";
  return 0;
}
