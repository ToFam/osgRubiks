cmake_minimum_required(VERSION 2.6.3)
project(osgRubiks)

find_package(OpenSceneGraph REQUIRED osg osgViewer osgGA)
find_package(Qt5 REQUIRED Core Gui Widgets)

include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

add_executable(osgRubiks WIN32 main.cpp)
target_link_libraries (osgRubiks
	Qt5::Widgets
	Qt5::Gui
	Qt5::Core
	${OPENSCENEGRAPH_LIBRARIES}
)
