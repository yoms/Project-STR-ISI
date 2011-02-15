project(Project-STR-ISI) # the name of your project

cmake_minimum_required(VERSION 2.4.0)

find_package(Qt4 REQUIRED) 
include(${QT_USE_FILE})


set(project_SRCS
    main.cpp
    TramWidget.cpp
    TramWindow.cpp
)

SET(project_MOC_HDRS
    TramWidget.h
    TramWindow.h
)

QT4_WRAP_CPP(project_MOC_SRCS ${project_MOC_HDRS})

SET(project_UIS
    tramwindow.ui
)


QT4_WRAP_UI(project_UIS_H ${project_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

qt4_automoc(${project_SRCS})
add_executable(Project-STR-ISI ${project_SRCS} ${project_MOC_SRCS} ${project_UIS_H} )
target_link_libraries(Project-STR-ISI ${QT_LIBRARIES})
