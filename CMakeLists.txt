cmake_minimum_required(VERSION 2.8.11)
project(osgRubiks)

find_package(OpenSceneGraph REQUIRED osg osgViewer osgGA osgQt)
find_package(Qt5 REQUIRED Core Gui Widgets OpenGL)

include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

set (SRC main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    viewerwidget.h
    viewerwidget.cpp
    cube.h
    cube.cpp
    rubikscube.h
    rubikscube.cpp
    rubikshandler.h
    rubikshandler.cpp
    )
    
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(osgRubiks WIN32 ${SRC})
target_link_libraries (osgRubiks
	Qt5::Widgets
	Qt5::Gui
	Qt5::Core
        Qt5::OpenGL
	${OPENSCENEGRAPH_LIBRARIES}
)
