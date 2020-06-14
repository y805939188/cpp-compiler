add_library(
  lexer
  lexer/lexer.h
  lexer/lexer.cpp
)

add_library(
  token
  lexer/token.h
  lexer/token.cpp
)

add_library(
  keywords
  lexer/keywords.h
  lexer/keywords.cpp
)

add_library(
  ast
  ast/ast.h
  ast/ast.cpp
)

add_library(
  utils
  ./utils/utils.h
  ./utils/utils.cpp
)

target_link_libraries(lexer PRIVATE token)
target_link_libraries(lexer PRIVATE utils)
# target_link_libraries(lexer PRIVATE keywords)
target_link_libraries(token PRIVATE keywords)
target_link_libraries(token PRIVATE utils)
target_link_libraries(ast PRIVATE token)
target_link_libraries(ast PRIVATE utils)


target_include_directories(lexer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lexer/")
target_include_directories(token PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lexer/")
target_include_directories(keywords PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lexer/")
target_include_directories(ast PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/ast/")
target_include_directories(utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/utils/")
