#include <QEvent>

class RayTraceEvent : QEvent {
public:
   static const QEvent::Type traceStart = static_cast<QEvent::Type>(1234);
   static const QEvent::Type traceEnd = static_cast<QEvent::Type>(1235);
   static const QEvent::Type tracePixelFilled = static_cast<QEvent::Type>(1236);
};

