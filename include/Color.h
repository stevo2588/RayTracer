
#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <sstream>
#include <typeinfo>
#include <limits>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

template <typename T>
struct TColor {
   TColor() : r(0),g(0),b(0), maxC(255) {}
   //TColor() : sf::Color() {}
   TColor(const TColor<T> &c) {r = c.r; g = c.g; b = c.b; }
   TColor(T r, T g, T b) : r(r),g(g),b(b),maxC(255) {}
   TColor(T r, T g, T b, T maxC, T minC) : r(r),g(g),b(b),maxC(maxC) {}

   TColor<T>& operator=(const TColor<T> &c);
   TColor<T>& operator+=(const TColor<T> &c);
   template <typename S>
   friend TColor<S> operator+(const TColor<S> &c0, const TColor<S> &c1);
   template <typename S>
   friend TColor<S> operator-(const TColor<S> &c0, const TColor<S> &c1);
   template <typename S>
   friend TColor<S> operator*(const TColor<S> &c0, const TColor<S> &c1);
   template <typename S>
   friend TColor<S> operator*(const TColor<S> &c, int s);
   template <typename S>
   friend TColor<S> operator*(const TColor<S> &c, double s);
   template <typename S>
   friend TColor<S> operator/(const TColor<S> &c, int s);
   template <typename S>
   friend TColor<S> operator/(const TColor<S> &c, double s);

   static TColor maximum(const TColor &c0, const TColor &c1);
   static TColor minimum(const TColor &c0, const TColor &c1);
   void RGBtoHSV(double &h, double &s, double &v);
   std::string toString();

   operator TColor<double>() {
      return TColor<double>(this->r,this->g,this->b);
   }
   operator TColor<unsigned char>() {
      TColor<T> newColor = checkLimits(TColor<T>(this->r,this->g,this->b));
      return TColor<unsigned char>(newColor.r,newColor.g,newColor.b);
   }
   operator TColor<int>() {
      return TColor<int>(this->r,this->g,this->b);
   }

   T r,g,b,a;
   T maxC;

private:
   TColor<T> checkLimits(TColor<T> c);
};

//------------------------- TColor ------------------------------------
// make sure color is within the limits of its type
template <typename T>
TColor<T> TColor<T>::checkLimits(TColor<T> c) {
   return TColor<T>( (c.r >= maxC) ? maxC : (c.r <= 0) ? 0 : c.r,
                     (c.g >= maxC) ? maxC : (c.g <= 0) ? 0 : c.g,
                     (c.b >= maxC) ? maxC : (c.b <= 0) ? 0 : c.b );
}

template <typename T>
TColor<T> operator+(const TColor<T> &c0, const TColor<T> &c1) {
   return TColor<T>(c0.r + c1.r,c0.g + c1.g,c0.b + c1.b);
}

template <typename T>
TColor<T> operator+(const TColor<T> &c, double n) {
   return TColor<T>(c.r + n,c.g + n,c.b + n);
}

template <typename T>
TColor<T> operator-(const TColor<T> &c0, const TColor<T> &c1) {
   return TColor<T>( abs(c0.r - c1.r),
                  abs(c0.g - c1.g),
                  abs(c0.b - c1.b));
}

template <typename T>
TColor<T> operator*(const TColor<T> &c0, const TColor<T> &c1) {
   int red = c0.r * c1.r;
   int green = c0.g * c1.g;
   int blue = c0.b * c1.b;
   return TColor<T>( red>255 ? 255 : red,
                  green>255 ? 255 : green,
                  blue>255 ? 255 : blue );
}

// TODO: clamp
template <typename T>
TColor<T> operator*(const TColor<T> &c, int s) {
   return TColor<T>(c.r * s, c.g * s, c.b * s);
}

template <typename T>
TColor<T> operator*(const TColor<T> &c, double s) {
   return TColor<T>(c.r * s, c.g * s, c.b * s);
}

template <typename T>
TColor<T> operator/(const TColor<T> &c, int s) {
   return TColor<T>(c.r / s, c.g / s, c.b / s);
}

template <typename T>
TColor<T> operator/(const TColor<T> &c, double s) {
   return TColor<T>(c.r / s, c.g / s, c.b / s);
}

template <typename T>
TColor<T>& TColor<T>::operator+=(const TColor<T> &c) {
   if(this == &c) return *this;

   r += c.r;
   g += c.g;
   b += c.b;

   return *this;
}

template <typename T>
TColor<T>& TColor<T>::operator=(const TColor<T> &c) {
   if(this == &c) return *this;

   r = c.r;
   g = c.g;
   b = c.b;
   a = c.a;
   maxC = c.maxC;

   return *this;
}

template <typename T>
TColor<T> TColor<T>::maximum(const TColor<T> &c0, const TColor<T> &c1) {
   return TColor<T>( c0.r > c1.r ? c0.r : c1.r,
                  c0.g > c1.g ? c0.g : c1.g,
                  c0.b > c1.b ? c0.b : c1.b);
}

template <typename T>
TColor<T> TColor<T>::minimum(const TColor<T> &c0, const TColor<T> &c1) {
   return TColor<T>( c0.r < c1.r ? c0.r : c1.r,
                  c0.g < c1.g ? c0.g : c1.g,
                  c0.b < c1.b ? c0.b : c1.b);
}

#define getMax(x, y, z) ((x) > (y)? ((x) > (z)? (x) : (z)) : ((y) > (z)? (y) : (z)))
#define getMin(x, y, z) ((x) < (y)? ((x) < (z)? (x) : (z)) : ((y) < (z)? (y) : (z)))
template <typename T>
void TColor<T>::RGBtoHSV(double &h, double &s, double &v) {

  double red, green, blue;
  double maxVal, minVal, delta;

  red = r / 255.0; green = g / 255.0; blue = b / 255.0;  /* r, g, b to 0 - 1 scale */

  maxVal = getMax(red, green, blue);
  minVal = getMin(red, green, blue);

  v = maxVal;        /* value is maximum of r, g, b */

  if(maxVal == 0){    /* saturation and hue 0 if value is 0 */
    s = 0;
    h = 0;
  }
  else{
    s = (maxVal - minVal) / maxVal;           /* saturation is color purity on scale 0 - 1 */

    delta = maxVal - minVal;
       if(delta == 0)                    /* hue doesn't matter if saturation is 0 */
      h = 0;
    else{
      if(red == maxVal)                  /* otherwise, determine hue on scale 0 - 360 */
        h = (green - blue) / delta;
      else if(green == maxVal)
        h = 2.0 + (blue - red) / delta;
      else /* (blue == maxVal) */
        h = 4.0 + (red - green) / delta;
      h = h * 60.0;
      if(h < 0)
        h = h + 360.0;
    }
  }
}

template <typename T>
std::string TColor<T>::toString() {
   std::stringstream ss;
   ss << "(" << (T)r << "," << (T)g << "," << (T)b << ")";
   return ss.str();
}

#endif // COLOR_H
