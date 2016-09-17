#include "rubikscube.h"

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
        addChild(t);
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
}

void RubiksCube::expand(double amount)
{
    for (int i = 0; i < 27; i++)
    {
        auto t = static_cast<osg::PositionAttitudeTransform*>(m_cubes[i]->getParent(0));
        t->setPosition(t->getPosition() * amount);
    }
}

bool RubiksCube::rotate(Cube *cube, bool clockwise)
{
    for (int i = 0; i < 27; i++)
    {
        if (cube == m_cubes[i])
        {
            if (i == 4)
            {
            }
        }
    }
}
