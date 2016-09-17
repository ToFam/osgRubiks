#ifndef RUBIKSHANDLER_H
#define RUBIKSHANDLER_H

#include <osgGA/GUIEventHandler>

#include "rubikscube.h"

class RubiksHandler : public osgGA::GUIEventHandler
{
public:
    RubiksHandler(RubiksCube* cube);

    bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

private:
    RubiksCube* m_cube;
};

#endif // RUBIKSHANDLER_H
