add_library(
  lexer
  src/lexer/token.h
  src/lexer/token.cpp
  src/lexer/lexer.cpp
)

target_include_directories(lexer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
