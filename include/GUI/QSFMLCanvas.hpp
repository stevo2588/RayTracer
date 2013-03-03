
#ifndef QSFMLCANVAS_HPP
#define QSFMLCANVAS_HPP

#include <include/GUI/renderWindowWrapper.hpp>
#include <Qt/qwidget.h>
#include <Qt/qtimer.h>

class QSFMLCanvas : public QWidget, public RWWrapper
{
   Q_OBJECT
public:
   ////////////////////////////////////////////////////////////
   /// \param Parent :    Parent of the widget
   /// \param Position :  Position of the widget
   /// \param Size :      Size of the widget
   /// \param FrameTime : Frame duration, in milliseconds (0 by default)
   ////////////////////////////////////////////////////////////
   QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, sf::Image* im, unsigned int FrameTime = 0);
   virtual ~QSFMLCanvas();
   sf::Image getImageCopy();
   void resizeSprite();

protected:
   void customEvent(QEvent *event);

private:
   void onInit(); // Notification that moment is good for doing initializations
   void onUpdate(); // Notification that moment is good for doing its update and drawing stuff
   QPaintEngine* paintEngine() const; // Return the paint engine used by the widget to draw itself
   void showEvent(QShowEvent*); // Called when the widget is shown; we use it to initialize our SFML window
   void paintEvent(QPaintEvent*); // Called when the widget needs to be painted; we use it to display a new frame

   //QTimer myTimer;       ///< Timer used to update the view
   bool   myInitialized; ///< Tell whether the SFML window has been initialized or not

   sf::Image *currentImage;  // our image data, kept in memory
   sf::Texture tex;           // image data, kept on gpu
   sf::Sprite sprite;         // drawable representation of our image data
};


#endif // QSFMLCANVAS_HPP
