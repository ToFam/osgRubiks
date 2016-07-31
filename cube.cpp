#include "cube.h"

Cube::Cube()
{
    m_geometry = new osg::Geometry();
    osg::Vec3Array* cubeVertices = new osg::Vec3Array;
    cubeVertices->push_back( osg::Vec3( 0, 0, 0) );  // 0 lower front left
    cubeVertices->push_back( osg::Vec3( 1, 0, 0) );  // 1 lower front right
    cubeVertices->push_back( osg::Vec3( 1, 1, 0) );  // 2 lower back right
    cubeVertices->push_back( osg::Vec3( 0, 1, 0) );  // 3 lower back left
    cubeVertices->push_back( osg::Vec3( 0, 0, 1) ); // 4 upper front left
    cubeVertices->push_back( osg::Vec3( 1, 0, 1) ); // 5 upper front right
    cubeVertices->push_back( osg::Vec3( 1, 1, 1) ); // 6 upper back right
    cubeVertices->push_back( osg::Vec3( 0, 1, 1) ); // 7 upper back left

    m_geometry->setVertexArray(cubeVertices);

    osg::DrawElementsUInt* cubeBase =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeBase->push_back(3);
    cubeBase->push_back(2);
    cubeBase->push_back(1);
    cubeBase->push_back(0);
    m_geometry->addPrimitiveSet(cubeBase);

    osg::DrawElementsUInt* cubeFront =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeFront->push_back(0);
    cubeFront->push_back(1);
    cubeFront->push_back(5);
    cubeFront->push_back(4);
    m_geometry->addPrimitiveSet(cubeFront);

    osg::DrawElementsUInt* cubeRight =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeRight->push_back(1);
    cubeRight->push_back(2);
    cubeRight->push_back(6);
    cubeRight->push_back(5);
    m_geometry->addPrimitiveSet(cubeRight);

    osg::DrawElementsUInt* cubeLeft =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeLeft->push_back(3);
    cubeLeft->push_back(0);
    cubeLeft->push_back(4);
    cubeLeft->push_back(7);
    m_geometry->addPrimitiveSet(cubeLeft);

    osg::DrawElementsUInt* cubeBack =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeBack->push_back(2);
    cubeBack->push_back(3);
    cubeBack->push_back(7);
    cubeBack->push_back(6);
    m_geometry->addPrimitiveSet(cubeBack);

    osg::DrawElementsUInt* cubeTop =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeTop->push_back(6);
    cubeTop->push_back(7);
    cubeTop->push_back(4);
    cubeTop->push_back(5);
    m_geometry->addPrimitiveSet(cubeTop);

    osg::Vec4Array* colors = new osg::Vec4Array;
    for (int i = 0; i < 6; i++)
        colors->push_back(osg::Vec4(0, 0, 0, 1.0f) );

    m_geometry->setColorArray(colors);
    m_geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);

    m_geode = new osg::Geode();
    m_geode->addChild(m_geometry);

    m_transform = new osg::PositionAttitudeTransform();
    m_transform->addChild(m_geode);
}

void Cube::setColor(CubeSide side, osg::Vec4 rgba)
{
    osg::Vec4Array* colors = static_cast<osg::Vec4Array*>(m_geometry->getColorArray());
    (*colors)[side] = rgba;
}

osg::Vec4 Cube::getColor(CubeSide side) const
{
    const osg::Vec4Array* colors = static_cast<const osg::Vec4Array*>(m_geometry->getColorArray());
    return (*colors)[side];
}

osg::Vec3 Cube::getPosition() const
{
    return m_transform->getPosition();
}

void Cube::setPosition(osg::Vec3 pos)
{
    m_transform->setPosition(pos);
}

osg::Group* Cube::getNode()
{
    return m_transform;
}
