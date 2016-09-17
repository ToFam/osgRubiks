#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H

#include <osg/Group>

#include "cube.h"

class RubiksCube : public osg::Group
{
public:
    RubiksCube();

    bool rotate(Cube* cube, bool clockwise);

    void expand(double amount);

private:
    Cube** m_cubes;
};

#endif // RUBIKSCUBE_H
