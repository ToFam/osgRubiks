#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H

#include "cube.h"

class RubiksCube
{
public:
    RubiksCube();

    osg::Group* getGroup();
private:
    Cube** m_cubes;
    osg::Group* m_group;
};

#endif // RUBIKSCUBE_H
