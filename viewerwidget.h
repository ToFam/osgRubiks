#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <osgViewer/View>
#include <osgViewer/CompositeViewer>
#include <osg/Group>

class ViewerWidget : public QWidget, public osgViewer::CompositeViewer
{
    Q_OBJECT

public:
    explicit ViewerWidget(QWidget* parent = 0);

    void paintEvent(QPaintEvent* /* event*/) Q_DECL_OVERRIDE;

private:
    void createScene();

    QTimer m_timer;
    osg::Group* m_scene;
    osgViewer::View* m_view;
};

#endif // VIEWERWIDGET_H
