#include "viewerwidget.h"

#include <QLayout>
#include <osgQt/GraphicsWindowQt>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/ViewerEventHandlers>

ViewerWidget::ViewerWidget(QWidget* parent)
    :QWidget(parent)
{
    setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);
    setKeyEventSetsDone(0);

    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowName = "";
    traits->windowDecoration = false;
    traits->x = 0;
    traits->y = 0;
    traits->width = 100;
    traits->height = 100;
    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();

    osgQt::GraphicsWindowQt* window = new osgQt::GraphicsWindowQt(traits.get());

    createScene();
    m_view = new osgViewer::View();
    addView(m_view);

    osg::Camera* camera = m_view->getCamera();
    camera->setGraphicsContext( window );

    camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );

    m_view->setSceneData( m_scene );
    m_view->addEventHandler( new osgViewer::StatsHandler );
    m_view->setCameraManipulator( new osgGA::MultiTouchTrackballManipulator );
    window->setTouchEventsEnabled( true );

    QWidget* w = window->getGLWidget();
    QHBoxLayout* l = new QHBoxLayout;
    l->addWidget(w);
    this->setLayout(l);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(10);
}

void ViewerWidget::paintEvent(QPaintEvent *)
{
    frame();
}

void ViewerWidget::createScene()
{
    m_scene = new osg::Group();
    osg::Geode* cubeGeode = new osg::Geode();
    osg::Geometry* cubeGeometry = new osg::Geometry();

    cubeGeode->addDrawable(cubeGeometry);
    m_scene->addChild(cubeGeode);

    osg::Vec3Array* cubeVertices = new osg::Vec3Array;
    cubeVertices->push_back( osg::Vec3( 0, 0, 0) );  // 0 lower front left
    cubeVertices->push_back( osg::Vec3(10, 0, 0) );  // 1 lower front right
    cubeVertices->push_back( osg::Vec3(10,10, 0) );  // 2 lower back right
    cubeVertices->push_back( osg::Vec3( 0,10, 0) );  // 3 lower back left
    cubeVertices->push_back( osg::Vec3( 0, 0, 10) ); // 4 upper front left
    cubeVertices->push_back( osg::Vec3(10, 0, 10) ); // 5 upper front right
    cubeVertices->push_back( osg::Vec3(10,10, 10) ); // 6 upper back right
    cubeVertices->push_back( osg::Vec3( 0,10, 10) ); // 7 upper back left

    cubeGeometry->setVertexArray( cubeVertices );

    osg::DrawElementsUInt* cubeBase =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeBase->push_back(3);
    cubeBase->push_back(2);
    cubeBase->push_back(1);
    cubeBase->push_back(0);
    cubeGeometry->addPrimitiveSet(cubeBase);

    osg::DrawElementsUInt* cubeFront =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeFront->push_back(0);
    cubeFront->push_back(1);
    cubeFront->push_back(5);
    cubeFront->push_back(4);
    cubeGeometry->addPrimitiveSet(cubeFront);

    osg::DrawElementsUInt* cubeRight =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeRight->push_back(1);
    cubeRight->push_back(2);
    cubeRight->push_back(6);
    cubeRight->push_back(5);
    cubeGeometry->addPrimitiveSet(cubeRight);

    osg::DrawElementsUInt* cubeLeft =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeLeft->push_back(3);
    cubeLeft->push_back(0);
    cubeLeft->push_back(4);
    cubeLeft->push_back(7);
    cubeGeometry->addPrimitiveSet(cubeLeft);

    osg::DrawElementsUInt* cubeBack =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeBack->push_back(2);
    cubeBack->push_back(3);
    cubeBack->push_back(7);
    cubeBack->push_back(6);
    cubeGeometry->addPrimitiveSet(cubeBack);

    osg::DrawElementsUInt* cubeTop =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeTop->push_back(6);
    cubeTop->push_back(7);
    cubeTop->push_back(4);
    cubeTop->push_back(5);
    cubeGeometry->addPrimitiveSet(cubeTop);

    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) );
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) );
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) );
    colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) );
    colors->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f) );
    colors->push_back(osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f) );

    cubeGeometry->setColorArray(colors);
    cubeGeometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);

    m_scene->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
}
