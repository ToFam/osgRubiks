#include "rubikshandler.h"

#include <osgUtil/LineSegmentIntersector>
#include <osgViewer/View>

#include <osg/PositionAttitudeTransform>

#include "cube.h"

RubiksHandler::RubiksHandler(RubiksCube* cube) : m_cube(cube)
{

}

bool RubiksHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    switch (ea.getEventType())
    {
    case osgGA::GUIEventAdapter::SCROLL:
        if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_ALT)
        {
            osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
            if (!view)
                break;

            switch (ea.getScrollingMotion())
            {
            case osgGA::GUIEventAdapter::SCROLL_DOWN:
            case osgGA::GUIEventAdapter::SCROLL_RIGHT:
                m_cube->expand(0.9);
                break;
            case osgGA::GUIEventAdapter::SCROLL_LEFT:
            case osgGA::GUIEventAdapter::SCROLL_UP:
                m_cube->expand(1.1);
                break;
            }
        }
        break;
    case osgGA::GUIEventAdapter::PUSH:
    {
        osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
        if (!view)
            break;

        osgUtil::LineSegmentIntersector::Intersections intersections;

        if (view->computeIntersections(ea,intersections))
        {
            for(osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
                hitr != intersections.end();
                ++hitr)
            {
                auto it = hitr->nodePath.end();
                do{
                    it--;
                    Cube* c = dynamic_cast<Cube*>(*it);
                    if (c)
                    {
                        if (ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
                            m_cube->rotate(c, false);
                        else
                            m_cube->rotate(c, true);
                        return false;
                    }
                }while(it != hitr->nodePath.begin());
            }
        }
        break;
    }
    }

    return false;
}
