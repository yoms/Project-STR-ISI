project(Project-STR-ISI) # the name of your project

cmake_minimum_required(VERSION 2.4.0)

link_directories(${CMAKE_BINARY_DIR})

set(QT_USE_QTTEST = TRUE)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
set(GNATLIB_PATH "/usr/lib" "/usr/lib64" "/usr/lib/gcc/i686-pc-linux-gnu/4.5.2/adalib")

find_library(libgnat "gnat" ${GNATLIB_PATH})
find_library(libgnarl "gnarl" ${GNATLIB_PATH})
MACRO( ADA_COMPILE_LINK )
  FOREACH( _adafilename ${ARGN})
         add_custom_target(
                ${_adafilename}
                gnatmake "-A${CMAKE_CURRENT_SOURCE_DIR}" ${_adafilename}
                COMMAND
                gnatbind ${_adafilename} -n -C -o "${_adafilename}.binder.c"
                COMMAND
                gcc -c -o "${_adafilename}.binder.o" "${_adafilename}.binder.c"
                COMMAND
                ar rcs libstatic${_adafilename}.a *.o
        )
  ENDFOREACH( _adafilename )
ENDMACRO( ADA_COMPILE_LINK )

set(project_SRCS
    main.cpp
    TramWidget.cpp
    TramWindow.cpp
    TramPropertiesWidget.cpp
    Tram.cpp
    Trip.cpp
    Drawable.cpp
    Door.cpp
    TerminalComposting.cpp
    TerminalPurchasing.cpp
    Light.cpp
    StationLight.cpp
    Station.cpp
    Obstacle.cpp
    Person.cpp
    Thread.cpp
    ThreadWithMessages.cpp
    EmergencyStop.cpp
    Timer.cpp
    ObstacleWidget.cpp
    Message.cpp
)

SET(project_MOC_HDRS
    ObstacleWidget.h
    TramWidget.h
    TramPropertiesWidget.h
    TramWindow.h
)

QT4_WRAP_CPP(project_MOC_SRCS ${project_MOC_HDRS})

SET(project_UIS
    tramwindow.ui
    trampropertieswidget.ui
    obstaclewidget.ui
)

set( ada_SRCS
api
borneachat
composteur
gestioncomposteur
)
set( staticada_LIBS
staticapi
staticborneachat
staticcomposteur
staticgestioncomposteur
)

ADA_COMPILE_LINK( ${ada_SRCS})

QT4_WRAP_UI(project_UIS_H ${project_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

qt4_automoc(${project_SRCS})
add_executable(Project-STR-ISI ${project_SRCS} ${project_MOC_SRCS} ${project_UIS_H} )
target_link_libraries(Project-STR-ISI ${QT_LIBRARIES} ${QT_QTTEST_LIBRARIES} gnat gnarl ${staticada_LIBS})
