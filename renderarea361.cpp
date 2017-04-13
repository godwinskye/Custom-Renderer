#include "renderarea361.h"
#include <QImage>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QSizePolicy>
#include "drawable.h"

//using namespace std;

RenderArea361::RenderArea361(QWidget *parent) : QWidget(parent), Drawable()
{
    image = QImage(750, 750, QImage::Format_RGB888);
    image.fill(0x00f0f0f0);
    this->setSizePolicy(QSizePolicy());
    this->update();
}
void RenderArea361::setPixel(int x, int y, uint color) {
    image.setPixel(x, y, color);
}
uint RenderArea361::getPixel(int x, int y) {
    return (uint)(image.pixel(x, y));
}
void RenderArea361::updateScreen() {
    this->update();
}
QSize RenderArea361::sizeHint() const
{
    return QSize(750, 750);
}


void RenderArea361::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}
