#include "resizableframe.h"

#include <QDebug>
#include <QVBoxLayout>

ResizableFrame::ResizableFrame(QWidget *parent, int width, int height) : frameWidth(width), frameHeight(height), posX(0), posY(0),
                                                                         QFrame(parent)
{
  setMouseTracking(true);
  setFrameStyle(QFrame::Box | QFrame::Plain);
#ifdef __linux__
  // Not sure if this works on other platforms as well
  setWindowFlags(Qt::FramelessWindowHint);
#endif
  //setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowTransparentForInput | Qt::WindowStaysOnTopHint);
  setGeometry(posX, posY, width, height); // Just some fixed values to test
                                          // Set a solid green thick border.
  setObjectName("testframe");
  //setMouseTracking(true);
  setStyleSheet("#testframe {border: 5px solid green;}");

  // IMPORTANT: A QRegion's coordinates are relative to the widget it's used in. This is not documented.
  //QRegion wholeFrameRegion(0,0,width,height);
  //QRegion innerFrameRegion = wholeFrameRegion.subtracted(QRegion(1,1,width,height));
  //setMask(innerFrameRegion);
  setWindowOpacity(0.5);
  QVBoxLayout *layout = new QVBoxLayout(this);
  label = new QLabel(this);
  label->setText(QString::number(width) + "x" + QString::number(height));
  label->setGeometry(width / 2, height / 2, 200, 200);
  label->setStyleSheet("font: 25pt;");
  layout->insertWidget(0, label);
  layout->setAlignment(label, Qt::AlignHCenter);
}

ResizableFrame::~ResizableFrame()
{
}

void ResizableFrame::setFrameHeight(int height)
{
  frameHeight = height;
  setGeometry(posX, posY, frameWidth, frameHeight);
  label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));
}

void ResizableFrame::setFrameWidth(int width)
{
  frameWidth = width;
  setGeometry(posX, posY, frameWidth, frameHeight);
  label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));
}

void ResizableFrame::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
    dragStartPosition = event->pos();
    dragStartGeometry = geometry();
    qDebug() << "Frame Geometry: " << frameGeometry();
    qDebug() << "Frame Width: " << width() << " Height:" << height();
    label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));
  }
}

void ResizableFrame::resizeEvent(QResizeEvent *event)
{
  frameWidth = width();
  frameHeight = height();
  label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));
}

void ResizableFrame::mouseMoveEvent(QMouseEvent *event)
{
  if (!(event->buttons() & Qt::LeftButton))
  {
    // No drag, just change the cursor and return

    if (event->x() <= 3 && event->y() <= 3)
    {
      startPos = topleft;
      setCursor(Qt::SizeFDiagCursor);
    }
    else if (event->x() <= 3 && event->y() >= height() - 3)
    {
      startPos = bottomleft;
      setCursor(Qt::SizeBDiagCursor);
    }
    else if (event->x() >= width() - 3 && event->y() <= 3)
    {
      startPos = topright;
      setCursor(Qt::SizeBDiagCursor);
    }
    else if (event->x() >= width() - 3 && event->y() >= height() - 3)
    {
      startPos = bottomright;
      setCursor(Qt::SizeFDiagCursor);
    }
    else if (event->x() <= 3)
    {
      startPos = left;
      setCursor(Qt::SizeHorCursor);
    }
    else if (event->x() >= width() - 3)
    {
      startPos = right;
      setCursor(Qt::SizeHorCursor);
    }
    else if (event->y() <= 3)
    {
      startPos = top;
      setCursor(Qt::SizeVerCursor);
    }
    else if (event->y() >= height() - 3)
    {
      startPos = bottom;
      setCursor(Qt::SizeVerCursor);
    }
    else
    {
      startPos = move;
      setCursor(Qt::SizeAllCursor);
    }
    return;
  }

  switch (startPos)
  {
  case topleft:
    posX = dragStartGeometry.left() - (dragStartPosition.x() - event->x());
    posY = dragStartGeometry.top() - (dragStartPosition.y() - event->y());
    frameWidth = dragStartGeometry.width() + (dragStartPosition.x() - event->x());
    frameHeight = height() + (dragStartPosition.y() - event->y());
    label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));

    setGeometry(posX,
                posY,
                frameWidth,
                frameHeight);
    dragStartGeometry = geometry();

    break;

  case bottomleft:
    posX = dragStartGeometry.left() - (dragStartPosition.x() - event->x());
    posY = dragStartGeometry.top();
    frameWidth = dragStartGeometry.width() + (dragStartPosition.x() - event->x());
    frameHeight = event->y();
    label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));

    setGeometry(posX,
                posY,
                frameWidth,
                frameHeight);
    dragStartGeometry = geometry();
    break;

  case topright:
    posX = dragStartGeometry.left();
    posY = dragStartGeometry.top() - (dragStartPosition.y() - event->y());
    frameWidth = event->x();
    frameHeight = height() + (dragStartPosition.y() - event->y());
    label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));

    setGeometry(posX,
                posY,
                frameWidth,
                frameHeight);
    dragStartGeometry = geometry();
    break;

  case bottomright:
    posX = dragStartGeometry.left();
    posY = dragStartGeometry.top();
    frameWidth = event->x();
    frameHeight = event->y();
    label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));

    setGeometry(posX,
                posY,
                frameWidth,
                frameHeight);
    break;

  case left:
    posX = dragStartGeometry.left() - (dragStartPosition.x() - event->x());
    posY = dragStartGeometry.top();
    frameWidth = dragStartGeometry.width() + (dragStartPosition.x() - event->x());
    frameHeight = height();
    label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));

    setGeometry(posX,
                posY,
                frameWidth,
                frameHeight);
    dragStartGeometry = geometry();
    break;

  case right:
    posX = dragStartGeometry.left();
    posY = dragStartGeometry.top();
    frameWidth = event->x();
    frameHeight = height();
    label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));

    setGeometry(posX,
                posY,
                frameWidth,
                frameHeight);
    break;

  case top:
    posX = dragStartGeometry.left();
    posY = dragStartGeometry.top() - (dragStartPosition.y() - event->y());
    frameWidth = dragStartGeometry.width();
    frameHeight = height() + (dragStartPosition.y() - event->y());
    label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));

    setGeometry(posX,
                posY,
                frameWidth,
                frameHeight);
    dragStartGeometry = geometry();
    break;

  case bottom:
    posX = dragStartGeometry.left();
    posY = dragStartGeometry.top();
    frameWidth = width();
    frameHeight = event->y();
    label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));

    setGeometry(posX,
                posY,
                frameWidth,
                frameHeight);
    break;

  case move:
    posX = dragStartGeometry.left() - (dragStartPosition.x() - event->x());
    posY = dragStartGeometry.top() - (dragStartPosition.y() - event->y());
    frameWidth = width();
    frameHeight = height();
    label->setText(QString::number(frameWidth) + "x" + QString::number(frameHeight));

    setGeometry(posX,
                posY,
                frameWidth,
                frameHeight);
    dragStartGeometry = geometry();
    break;

  default:
    break;
  }
  // qDebug() << "Frame geometry: "<< frameGeometry();
}
