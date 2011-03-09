project(Project-STR-ISI) # the name of your project

cmake_minimum_required(VERSION 2.4.0)

set(QT_USE_QTTEST = TRUE)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})


set(project_SRCS
    main.cpp
    TramWidget.cpp
    TramWindow.cpp
    TramPropertiesWidget.cpp
    Tram.cpp
    Trajet.cpp
    Drawable.cpp
    Porte.cpp
    Traction.cpp
    Borne.cpp
    Composteur.cpp
    BorneAchat.cpp
    Feu.cpp
    Station.cpp
    Obstacle.cpp
    Personne.cpp
    Chauffeur.cpp
    Thread.cpp
    Carte.cpp
    Stepable.cpp
    ArretUrgence.cpp
    Timer.cpp
)

SET(project_MOC_HDRS
    TramWidget.h
    TramPropertiesWidget.h
    TramWindow.h
)

QT4_WRAP_CPP(project_MOC_SRCS ${project_MOC_HDRS})

SET(project_UIS
    tramwindow.ui
    trampropertieswidget.ui
)


QT4_WRAP_UI(project_UIS_H ${project_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

qt4_automoc(${project_SRCS})
add_executable(Project-STR-ISI ${project_SRCS} ${project_MOC_SRCS} ${project_UIS_H} )
target_link_libraries(Project-STR-ISI ${QT_LIBRARIES} ${QT_QTTEST_LIBRARIES})
