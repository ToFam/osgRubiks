#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H

#include <osg/Group>

#include "cube.h"

class RubiksCube : public osg::Group
{
public:
    RubiksCube();

    enum Side
    {
        RED,
        GREEN,
        BLUE,
        WHITE,
        YELLOW,
        ORANGE
    };

    void rotate(Side side, bool clockwise);
    void rotate(Cube* cube, bool clockwise);

    void expand(double amount);

    void frame(double elapsedTime);

private:
    void rotate(double angle);

    Cube** m_cubes;

    bool m_rotating;
    bool m_clockwise;
    Cube** m_rotatingCubes;
    double m_angle;

    double m_time;
};

#endif // RUBIKSCUBE_H
