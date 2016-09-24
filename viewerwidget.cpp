#include "viewerwidget.h"

#include <QLayout>
#include <osgQt/GraphicsWindowQt>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/ViewerEventHandlers>

#include "rubikscube.h"
#include "rubikshandler.h"

ViewerWidget::ViewerWidget(QWidget* parent)
    :QWidget(parent)
{
    setThreadingModel(osgViewer::Viewer::SingleThreaded);
    setKeyEventSetsDone(0);

    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowName = "";
    traits->windowDecoration = false;
    traits->x = 0;
    traits->y = 0;
    traits->width = sizeHint().width();
    traits->height = sizeHint().height();
    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();

    osgQt::GraphicsWindowQt* window = new osgQt::GraphicsWindowQt(traits.get());

    createScene();

    osg::Camera* camera = getCamera();
    camera->setGraphicsContext( window );

    camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );

    setSceneData( m_scene );
    addEventHandler( new osgViewer::StatsHandler );
    addEventHandler( new RubiksHandler(m_cube) );
    setCameraManipulator( new osgGA::MultiTouchTrackballManipulator );
    window->setTouchEventsEnabled( true );

    QWidget* w = window->getGLWidget();
    QHBoxLayout* l = new QHBoxLayout;
    l->addWidget(w);
    this->setLayout(l);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(10);
}

void ViewerWidget::rotate(RubiksCube::Side side, bool clockwise)
{
    m_cube->rotate(side, clockwise);
}

void ViewerWidget::paintEvent(QPaintEvent *)
{
    frame();

    m_cube->frame(getFrameStamp()->getReferenceTime());
}

void ViewerWidget::createScene()
{
    m_scene = new osg::Group();

    m_cube = new RubiksCube();
    m_scene->addChild(m_cube);

    m_scene->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
}
