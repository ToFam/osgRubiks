#ifndef CUBE_H
#define CUBE_H

#include <osg/Geometry>
#include <osg/Geode>

enum CubeSide
{
    BOTTOM,
    FRONT,
    RIGHT,
    LEFT,
    BACK,
    TOP
};

class Cube : public osg::Geode
{
public:
    Cube();

    void setColor(CubeSide side, osg::Vec4 rgba);
    osg::Vec4 getColor(CubeSide side) const;

private:
    osg::Geometry* m_geometry;
};

#endif // CUBE_H
