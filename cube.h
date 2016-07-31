#ifndef CUBE_H
#define CUBE_H

#include <osg/Geometry>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>

enum CubeSide
{
    BOTTOM,
    FRONT,
    RIGHT,
    LEFT,
    BACK,
    TOP
};

class Cube
{
public:
    Cube();

    void setColor(CubeSide side, osg::Vec4 rgba);
    osg::Vec4 getColor(CubeSide side) const;

    void setPosition(osg::Vec3 pos);
    osg::Vec3 getPosition() const;

    osg::Group* getNode();

private:
    osg::Geometry* m_geometry;
    osg::Geode* m_geode;
    osg::PositionAttitudeTransform* m_transform;
};

#endif // CUBE_H
