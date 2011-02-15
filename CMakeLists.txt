project(Snake) # the name of your project

cmake_minimum_required(VERSION 2.4.0)

find_package(Qt4 REQUIRED) 
include(${QT_USE_FILE})


set(snake_SRCS
    main.cpp
    GameForm.cpp
    GameField.cpp
)

SET(snake_MOC_HDRS
  GameForm.h
  GameField.h
)

QT4_WRAP_CPP(snake_MOC_SRCS ${snake_MOC_HDRS})

SET(snake_UIS
    soliter.ui
)


QT4_WRAP_UI(snake_UIS_H ${snake_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

qt4_automoc(${snake_SRCS})
add_executable(Snake ${snake_SRCS} ${snake_MOC_SRCS} ${snake_UIS_H} )
target_link_libraries(Snake ${QT_LIBRARIES})
