#ifndef VISUALIZINGWIDGET_H
#define VISUALIZINGWIDGET_H

#include <QOpenGLWidget>
#include <QBrush>
#include <QPen>
#include "interpolator.h"

class VisualizingWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit VisualizingWidget(QWidget *parent = 0);

    Interpolator interpolator;
    
signals:

protected:
    void paintEvent(QPaintEvent *event);
    
public slots:
    
private:
    QBrush background;
    QBrush circleBrush;
    QPen   circlePen;
    double circleRadius;
};

#endif // VISUALIZINGWIDGET_H
