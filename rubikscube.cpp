#include "rubikscube.h"

#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

RubiksCube::RubiksCube()
{
    m_cubes = new Cube*[27];
    for (int i = 0; i < 27; i++)
    {
        m_cubes[i] = new Cube();
        osg::PositionAttitudeTransform* t = new osg::PositionAttitudeTransform;

        float x = 1.1 * ((i % 3) - 1);
        float y = 1.1 * (((int)(i / 3) % 3) - 1);
        float z = 1.1 * ((int)(i / 9) - 1);

        t->setPosition(osg::Vec3(x, y, z));
        t->addChild(m_cubes[i]);

        osg::MatrixTransform* mt = new osg::MatrixTransform;
        mt->setMatrix(osg::Matrix::identity());
        mt->addChild(t);
        addChild(mt);
    }

    for (int i = 0; i < 9; i++)
        m_cubes[i]->setColor(CubeSide::BOTTOM, osg::Vec4(1,0,0,1));
    for (int i = 18; i < 27; i++)
        m_cubes[i]->setColor(CubeSide::TOP, osg::Vec4(1,0.5,0,1));

    for (int i = 0; i < 27; i++)
    {
        if (i % 9 == 3)
            i += 6;
        if (i >= 27)
            break;
        m_cubes[i]->setColor(CubeSide::FRONT, osg::Vec4(0,0,1,1));
    }

    for (int i = 0; i < 27; i += 3)
        m_cubes[i]->setColor(CubeSide::LEFT, osg::Vec4(1, 1, 1, 1));

    for (int i = 2; i < 27; i += 3)
        m_cubes[i]->setColor(CubeSide::RIGHT, osg::Vec4(1, 1, 0, 1));

    for (int i = 0; i < 27; i++)
    {
        if (i % 9 == 0)
            i += 6;
        m_cubes[i]->setColor(CubeSide::BACK, osg::Vec4(0, 0.5, 0, 1));
    }

    m_rotating = false;
    m_rotatingCubes = new Cube*[9];
}

void RubiksCube::frame(double elapsedTime)
{
    double frameTime = elapsedTime - m_time;
    m_time = elapsedTime;
    if (m_rotating)
        rotate(frameTime);
}

void RubiksCube::expand(double amount)
{
    for (int i = 0; i < 27; i++)
    {
        auto t = static_cast<osg::PositionAttitudeTransform*>(m_cubes[i]->getParent(0));
        t->setPosition(t->getPosition() * amount);
    }
}

void RubiksCube::rotate(Side side, bool clockwise)
{
    switch(side)
    {
    case RED:
        rotate(m_cubes[4], clockwise);
        return;
    case ORANGE:
        rotate(m_cubes[22], clockwise);
        return;
    case BLUE:
        rotate(m_cubes[10], clockwise);
        return;
    case WHITE:
        rotate(m_cubes[12], clockwise);
        return;
    case YELLOW:
        rotate(m_cubes[14], clockwise);
        return;
    case GREEN:
        rotate(m_cubes[16], clockwise);
        return;
    }
}

void RubiksCube::rotate(Cube *cube, bool clockwise)
{
    if (m_rotating)
        return;

    int i;
    for (i = 0; i < 27; i++)
        if (m_cubes[i] == cube)
            break;

    if (i == 27)
        return;

    m_rotatingCubes[0] = m_cubes[i];

    int j_start, j_max, j_increment = 1, j_jumpOn = -1;
    int rotNumber = 1;

    switch (i)
    {
    // BOTTOM
    case 4:
        j_start = 0; j_max = 8;
        break;
    // TOP
    case 22:
        j_start = 18; j_max = 26;
        break;
    // LEFT
    case 12:
        j_start = 0; j_max = 26; j_increment = 3;
        break;
    // RIGHT
    case 14:
        j_start = 2; j_max = 26; j_increment = 3;
        break;
    // FRONT
    case 10:
        j_start = 0; j_max = 26; j_jumpOn = 3;
        break;
    // BACK
    case 16:
        j_start = 6; j_max = 26; j_jumpOn = 0;
        break;
    default:
        return;
    }

    // Create rotating cubes list
    int j = j_start;
    while (j <= j_max)
    {
        if (j_jumpOn > -1)
        {
            if (j % 9 == j_jumpOn)
                j += 6;
            if (j > j_max)
                break;
        }

        if (j != i)
        {
            m_rotatingCubes[rotNumber] = m_cubes[j];
            rotNumber++;
        }

        j += j_increment;
    }

    // Set cube array to post-Rotation
    //
    // [6] [7] [8]     [8] [5] [3]
    // [4] [0] [5] --> [7] [0] [2]
    // [1] [2] [3]     [6] [4] [1]
    //
    if ((clockwise && (i == 4 || i == 12 || i == 16)) ||
       (!clockwise && (i == 22 || i == 14 || i == 10)))
    {
        j = j_start;
        m_cubes[j] = m_rotatingCubes[6];
        j += j_increment;
        m_cubes[j] = m_rotatingCubes[4];
        j += j_increment;
        m_cubes[j] = m_rotatingCubes[1];
        j += j_increment;
        if (j_jumpOn >= 0)
            j += 6;
        m_cubes[j] = m_rotatingCubes[7];
        j += j_increment;
       //m_cubes[j] = m_rotatingCubes[0];
        j += j_increment;
        m_cubes[j] = m_rotatingCubes[2];
        j += j_increment;
        if (j_jumpOn >= 0)
            j += 6;
        m_cubes[j] = m_rotatingCubes[8];
        j += j_increment;
        m_cubes[j] = m_rotatingCubes[5];
        j += j_increment;
        m_cubes[j] = m_rotatingCubes[3];
        j += j_increment;
    }
    //
    // [6] [7] [8]     [1] [4] [6]
    // [4] [0] [5] --> [2] [0] [7]
    // [1] [2] [3]     [3] [5] [8]
    //
    else
    {
        j = j_start;
        m_cubes[j] = m_rotatingCubes[3];
        j += j_increment;
        m_cubes[j] = m_rotatingCubes[5];
        j += j_increment;
        m_cubes[j] = m_rotatingCubes[8];
        j += j_increment;
        if (j_jumpOn >= 0)
            j += 6;
        m_cubes[j] = m_rotatingCubes[2];
        j += j_increment;
       //m_cubes[j] = m_rotatingCubes[0];
        j += j_increment;
        m_cubes[j] = m_rotatingCubes[7];
        j += j_increment;
        if (j_jumpOn >= 0)
            j += 6;
        m_cubes[j] = m_rotatingCubes[1];
        j += j_increment;
        m_cubes[j] = m_rotatingCubes[4];
        j += j_increment;
        m_cubes[j] = m_rotatingCubes[6];
        j += j_increment;
    }

    m_clockwise = clockwise;
    m_rotating = true;
    m_angle = 0;

}

void RubiksCube::rotate(double angle)
{
    m_angle += angle;

    if (m_angle >= 1)
    {
        angle -= m_angle - 1;
        m_rotating = false;
    }

    osg::Vec3d center = static_cast<osg::PositionAttitudeTransform*>(m_rotatingCubes[0]->getParent(0))->getPosition();
    osg::Matrix m = osg::Matrix::translate(center) *
                    osg::Matrix::rotate(((m_clockwise) ? -1 : 1) * osg::PI_2 * angle, center) *
                    osg::Matrix::translate(-center);

    for (int i = 0; i < 9; i++)
    {
        auto mt = static_cast<osg::MatrixTransform*>(m_rotatingCubes[i]->getParent(0)->getParent(0));

        mt->setMatrix(mt->getMatrix() * m);
    }
}
