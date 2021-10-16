#include "circle.hpp"

#include <cmath>
#include <cstdlib>
Circle::Circle(Point p, double r) : center(p), radius(r) {
}
void Circle::move(double dx, double dy) {
  center.x += dx;
  center.y += dy;
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double PI = 2 * asin(1.0);
  double a = center.x;
  double b = center.y;
  double c = radius;

  double x = otherCircle.center.x;
  double y = otherCircle.center.y;
  double z = otherCircle.radius;
  double s = 0;
  double l = sqrt((a - x) * (a - x) + (b - y) * (b - y));
  double m, n, q, w = 0;
  if (l >= c + z || !c || !z) {
    s = 0;
  }
  else if (l <= fabs(z - c)) {
    if (z > c) {
      z = c;
    }
    s = z * z * PI;
  }
  else {
    b = acos((l * l + c * c - z * z) / (2 * l * c));
    y = acos((l * l + z * z - c * c) / (2 * l * z));
    m = b * c * c;
    n = y * z * z;
    q = c * c * sin(b) * cos(b);
    w = z * z * sin(y) * cos(y);
    s = m + n - (q + w);
  }
  return s;
}
