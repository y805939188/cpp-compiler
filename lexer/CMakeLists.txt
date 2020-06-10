# add_library(
#   lexer
#   src/lexer/token.h
#   src/lexer/token.cpp
#   src/lexer/keywords.h
#   src/lexer/keywords.cpp
#   src/lexer/lexer.cpp
# )

add_library(
  lexer
  src/lexer/lexer.cpp
)

add_library(
  token
  src/lexer/token.h
  src/lexer/token.cpp
)

add_library(
  keywords
  src/lexer/keywords.h
  src/lexer/keywords.cpp
)

add_library(
  utils
  src/utils/utils.h
  src/utils/utils.cpp
)

target_link_libraries(lexer PRIVATE token)
# target_link_libraries(lexer PRIVATE keywords)
target_link_libraries(token PRIVATE keywords)
target_link_libraries(token PRIVATE utils)

target_include_directories(lexer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(token PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(keywords PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
