
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <include/GUI/QSFMLCanvas.hpp>
#include <include/GUI/renderWindowWrapper.hpp>
#include <QApplication>
#include <include/RayTracer.h>
#include <include/Events.h>
#include <iostream> // remove me

// Platform-specific headers
#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

QSFMLCanvas::QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, sf::Image* im, unsigned int FrameTime)
   : QWidget(Parent), myInitialized (false), currentImage(im)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);

    // Setup the widget geometry
    move(Position);
    resize(Size);

    // Setup the timer (only necessary if you want the widget to automatically and continuously repaint itself)
    //myTimer.setInterval(FrameTime);
}

QSFMLCanvas::~QSFMLCanvas() {}

sf::Image QSFMLCanvas::getImageCopy() {
   return *currentImage;
}

void QSFMLCanvas::onInit() {
   // Setup the texture and sprite
   int imWidth = currentImage->getSize().x;
   int imHeight = currentImage->getSize().y;
   tex.create(imWidth,imHeight);
   tex.loadFromImage(*currentImage);
   sprite.setTexture(tex,true);
   int xPos = getSize().x/2;
   int yPos = getSize().y/2;
   sprite.setOrigin(imWidth/2, imHeight/2);
   sprite.setPosition(xPos, yPos);
}

void QSFMLCanvas::resizeSprite() {
   int imWidth = currentImage->getSize().x;
   int imHeight = currentImage->getSize().y;

   tex = sf::Texture();
   tex.create(imWidth,imHeight);
   tex.loadFromImage(*currentImage);
   sprite.setTexture(tex,true); // possibly???
   int xPos = getSize().x/2;
   int yPos = getSize().y/2;
   sprite.setOrigin(imWidth/2, imHeight/2);
   sprite.setPosition(xPos, yPos);
}

void QSFMLCanvas::onUpdate() {
   clear(sf::Color(0, 0, 0)); // Clear screen
   tex.update(*currentImage);
   draw(sprite); // Draw it
}

QPaintEngine* QSFMLCanvas::paintEngine() const {
    return 0;
}

void QSFMLCanvas::showEvent(QShowEvent*) {
    if (!myInitialized)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        // Create the SFML window with the widget handle
        createRenderWindow(winId()); // creates sfml window from the existing Qt window

        onInit(); // initialize

        // Setup the timer to trigger a refresh at specified framerate (only necessary if you want the widget to automatically and continuously repaint itself)
        //connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        //myTimer.start();

        myInitialized = true;
    }
}

void QSFMLCanvas::paintEvent(QPaintEvent*) {
    onUpdate(); // update
    display(); // Display on screen
}

void QSFMLCanvas::customEvent(QEvent *event) {
   if(event->type() == RayTraceEvent::tracePixelFilled) {
      update();
   }
   if(event->type() == RayTraceEvent::traceStart) {
      //resizeSprite(rp.getResolutionX(),rp.getResolutionY()); // possibly cause a race condition if a paint event is sent before the sf::Image actually changes?
   }
   else {
      QWidget::customEvent(event);
   }
}
