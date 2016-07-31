#include "rubikscube.h"

RubiksCube::RubiksCube()
{
    m_group = new osg::Group();

    m_cubes = new Cube*[27];
    for (int i = 0; i < 27; i++)
    {
        m_cubes[i] = new Cube();
        m_group->addChild(m_cubes[i]->getNode());

        float x = 1.1 * ((i % 3) - 1);
        float y = 1.1 * (((int)(i / 3) % 3) - 1);
        float z = 1.1 * ((int)(i / 9) - 1);

        m_cubes[i]->setPosition(osg::Vec3(x, y, z));
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

osg::Group* RubiksCube::getGroup()
{
    return m_group;
}
