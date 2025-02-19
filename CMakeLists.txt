cmake_minimum_required(VERSION 3.17)
project(LaboratorioDiProgrammazione)

set(GOOGLETEST_VERSION 1.11.0)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)
set(SOURCE_FILES Item.h Item.cpp Observer.h Subject.h ShoppingList.cpp ShoppingList.h User.cpp User.h)

add_executable(LaboratorioDiProgrammazione main.cpp)

add_library(core ${SOURCE_FILES})
target_link_libraries(LaboratorioDiProgrammazione core)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")