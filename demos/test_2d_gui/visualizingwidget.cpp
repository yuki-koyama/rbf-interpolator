#include "visualizingwidget.h"
#include <cassert>
#include <QVector3D>
#include <QPaintEvent>
#include <QPainter>

using std::vector;

extern QColor getHeatMapColor(float x);

VisualizingWidget::VisualizingWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    background   = QBrush(QColor(0xff, 0xff, 0xff));
    circleBrush  = QBrush(QColor(0x00, 0x00, 0x00));
    circlePen    = QPen(QColor(0x00, 0x00, 0x00));
    circleRadius = 10.0;
    circlePen.setWidth(2.0);
}

void VisualizingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    const QRect &rect = event->rect();

    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect, background);
    painter.save();

    int w = rect.width();
    int h = rect.height();

    QImage image(w, h, QImage::Format_ARGB32);

    for (int x = 0; x < w; ++ x) {
        for (int y = 0; y < h; ++ y) {
            double x1 = static_cast<double>(x) / static_cast<double>(w - 1);
            double x2 = static_cast<double>(y) / static_cast<double>(h - 1);
            vector<double> xVec;
            xVec.push_back(x1);
            xVec.push_back(x2);
            double value = interpolator.getInterpolatedValue(xVec);
            QColor color = getHeatMapColor(value);
            image.setPixel(x, y, qRgba(color.red(), color.green(), color.blue(), color.alpha()));
        }
    }

    painter.drawImage(0, 0, image);

    vector<double>          ys = interpolator.getYs();
    vector<vector<double> > xs = interpolator.getXs();

    assert(ys.size() == xs.size());
    int nPoints = ys.size();

    for (int i = 0; i < nPoints; ++ i) {
        double y  = ys[i];
        double x1 = xs[i][0];
        double x2 = xs[i][1];

        int x1Screen = static_cast<int>(x1 * (w - 1));
        int x2Screen = static_cast<int>(x2 * (w - 1));

        QColor color = getHeatMapColor(y);

        circleBrush = QBrush(color);
        painter.setBrush(circleBrush);
        painter.setPen(circlePen);

        painter.drawEllipse(QRectF(x1Screen - circleRadius, x2Screen - circleRadius, circleRadius * 2.0, circleRadius * 2.0));
    }

    painter.restore();
    painter.end();
}

QColor getHeatMapColor(float x) {
    x = std::min(1.0f, x);
    x = std::max(0.0f, x);

    QVector3D r(1.0f, 0.0f, 0.0f);
    QVector3D y(1.0f, 1.0f, 0.0f);
    QVector3D g(0.0f, 1.0f, 0.0f);
    QVector3D c(0.0f, 1.0f, 1.0f);
    QVector3D b(0.0f, 0.0f, 1.0f);
    QVector3D result;
    if (x < 0.25f) {
        float t = x * 4.0f;
        result = t * c + (1.0f - t) * b;
    } else if (x < 0.5f) {
        float t = (x - 0.25f) * 4.0f;
        result = t * g + (1.0f - t) * c;
    } else if (x < 0.75f) {
        float t = (x - 0.5f) * 4.0f;
        result = t * y + (1.0f - t) * g;
    } else {
        float t = (x - 0.75f) * 4.0f;
        result = t * r + (1.0f - t) * y;
    }
    int cr = static_cast<int>(result.x() * 255.0f);
    int cg = static_cast<int>(result.y() * 255.0f);
    int cb = static_cast<int>(result.z() * 255.0f);
    return QColor(cr, cg, cb);
}


