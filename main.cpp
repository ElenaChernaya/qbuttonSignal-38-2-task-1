#include "QButtonSignal_38_2_Task1.h"
#include <QtWidgets/QApplication>

#include <QPixmap>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

#include <QMediaPlayer>



class ImageButton : public QPushButton
{
    Q_OBJECT

public:
    ImageButton() = default;
    ImageButton(QWidget* parent);

    void paintEvent(QPaintEvent* e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent* k) override;

public slots:
    void setUp();
    void setDown();
    void playSignal();

private:
    QPixmap currentImage;
    QPixmap buttonUp;
    QPixmap buttonDown;
    QMediaPlayer* signal;

};


ImageButton::ImageButton(QWidget* parent)
{
    setParent(parent);
    setToolTip("STOP");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonUp = QPixmap("C:\\Users\\Elena\\Desktop\\ButtonUp.jpg");
    buttonDown = QPixmap("C:\\Users\\Elena\\Desktop\\ButtonDown.jpg");
    currentImage = buttonUp;
    setGeometry(currentImage.rect());
    connect(this, &QPushButton::clicked, this, &ImageButton::setDown);

    //Для звукового сигнала
    signal = new QMediaPlayer(this);
    connect(this, &QPushButton::clicked, this, &ImageButton::playSignal);

}

void ImageButton::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    p.drawPixmap(e->rect(), currentImage);

}

QSize ImageButton::sizeHint() const
{
    return QSize(300, 300);
}


QSize ImageButton::minimumSizeHint() const
{
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent* k)
{
    setDown();
}

void ImageButton::setDown()
{
    currentImage = buttonDown;
    update();
    QTimer::singleShot(100, this, &ImageButton::setUp);
}

void ImageButton::setUp()
{
    currentImage = buttonUp;
    update();
}


void ImageButton::playSignal()
{
    signal->setMedia(QUrl::fromLocalFile("C:\\Users\\Elena\\Desktop\\PressedButton.mp3"));
    signal->setVolume(75);
    signal->play();
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageButton redButton(nullptr);
    redButton.setFixedSize(300, 300);
    redButton.move(800, 200);
    redButton.show();
    return a.exec();
}

#include <main.moc>
