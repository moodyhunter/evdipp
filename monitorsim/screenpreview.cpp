#include <QVBoxLayout>
#include <QPainter>
#include <QDateTime>
#include "screenpreview.h"

ScreenPreview::ScreenPreview(QEvdiScreen& screen, QWidget* parent)
    : QWidget(parent)
    , cursorEnabled(false)
    , cursorPosition()
    , cursorHotpoint()
    , latestBufferId(-1)
    , screen(screen)
{
    connect(&screen, &QEvdiScreen::screen_updated, this, &ScreenPreview::latest_buffer);
    connect(&screen, &QEvdiScreen::cursor_changed, this, &ScreenPreview::update_cursor);
    connect(&screen, &QEvdiScreen::cursor_moved, this, &ScreenPreview::move_cursor);
    createTimer(60);
}

void ScreenPreview::createTimer(unsigned fps)
{
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update_screen()));
    updateTimer->start(1000.0 / fps);
}

void ScreenPreview::latest_buffer(int buffer_id)
{
    latestBufferId = buffer_id;
}

void ScreenPreview::update_cursor(QImage cursor_image, bool enabled, int hot_x, int hot_y)
{
    cursorEnabled = enabled;
    if (cursorEnabled) {
        cursorImage = cursor_image;
        cursorHotpoint = QPoint(hot_x, hot_y);
    }
}

void ScreenPreview::move_cursor(int x, int y)
{
    cursorPosition = QPoint(x, y);
}

void ScreenPreview::update_screen()
{
    screen.update();
}

void ScreenPreview::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if (latestBufferId >= 0) {
        painter.drawImage(QPoint(0, 0), screen.image_for_buffer(latestBufferId));
    }
    if (cursorEnabled) {
        painter.drawImage(cursorPosition - cursorHotpoint, cursorImage);
    }
    QWidget::paintEvent(e);
    update();
}

QSize ScreenPreview::sizeHint() const
{
    return latestBufferId >= 0 ? screen.image_for_buffer(latestBufferId).size() : minimumSizeHint();
}

QSize ScreenPreview::minimumSizeHint() const
{
    return QSize(800, 600);
}

void ScreenPreview::save_screenshot()
{
    QImage image = screen.image_for_buffer(latestBufferId);
    QPainter painter(&image);
    if (cursorEnabled) {
        painter.drawImage(cursorPosition - cursorHotpoint, cursorImage);
    }
    image.save(QString("screenshot ") + QDateTime::currentDateTimeUtc().toString(Qt::RFC2822Date) + ".png");
}
