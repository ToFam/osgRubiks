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

    void rotate(Side side, bool clockwise, bool instant = false);
    void rotate(Cube* cube, bool clockwise, bool instant = false);

    void scramble();
    void reset();

    void expand(double amount);

    void frame(double elapsedTime);

private:
    void rotate(double angle);

    Cube** m_cubes;

    bool m_rotating;
    bool m_clockwise;
    Cube** m_rotatingCubes;
    double m_angle;
    double m_rotatingSpeed;
    constexpr static double STANDARD_ROT_SPEED = 2;

    int m_scrambleCountdown;

    double m_time;
};

#endif // RUBIKSCUBE_H
