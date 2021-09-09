#ifndef RESIZABLEFRAME_H
#define RESIZABLEFRAME_H

#include <QFrame>
#include <QMouseEvent>
#include <QLabel>
#include <QResizeEvent>
//#include <mainwindow.h>

class ResizableFrame : public QFrame
{
Q_OBJECT

public:
    explicit ResizableFrame(QWidget *parent = 0, int width = 800, int height = 600);
    ~ResizableFrame();
    void setFrameWidth(int width);
    void setFrameHeight(int height);
//void setMainWindow(Ui::MainWindow *ui);

    enum startPositions {topleft, left, bottomleft, bottom, bottomright, right, topright, top, move} startPositions;
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent *event);

private:
    QPoint dragStartPosition;
    QRect dragStartGeometry;
    QLabel *label;
    int posX;
    int posY;
    int frameWidth;
    int frameHeight;
    enum startPositions startPos;
};

#endif // RESIZABLEFRAME_H
