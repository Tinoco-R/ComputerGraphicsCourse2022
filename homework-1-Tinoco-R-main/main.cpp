#include "BMP.h"
#include <cmath>
#include <iostream>

/* This link was used as a heavy resource for the rasterizeEllipse function
 * https://www.geometrictools.com/Documentation/IntegerBasedEllipseDrawing.pdf
 */

void rasterizeEllipse(int a, int b, BMP &bmpNew) {
  // Rasterize first region and use symmetry for 3 other regions
  int a2 = a * a;
  int b2 = b * b;
  int sigInc1 = 2 * b2;
  int sigInc2 = 4 * a2;
  int x, y, sigma;

  for (x = 0, y = b, sigma = sigInc1 + a2 * (1 - 2 * b); b2 * x <= a2 * y;
       x++) {
    bmpNew.set_pixel(x + 900, y + 450, 255, 255, 255, 0); // x, y, value
    // bmpNew.set_pixel(-x + 900, y + 450, 255, 255, 255, 0);  // -x, y, value
    bmpNew.set_pixel(x + 900, -y + 450, 255, 255, 255, 0); // x, -y, value
    // bmpNew.set_pixel(-x + 900, -y + 450, 255, 255, 255, 0); // -x, -y, value

    if (sigma >= 0) {
      sigma += sigInc2 * (1 - y);
      y--;
    }
    sigma += sigInc1 * (2 * x + 3);
  }

  // Rasterize second region and use symmetry for 3 other regions
  sigInc1 = 2 * a2;
  sigInc2 = 4 * b2;

  for (y = 0, x = a, sigma = sigInc1 + b2 * (1 - 2 * a); a2 * y <= b2 * x;
       y++) {
    bmpNew.set_pixel(x + 900, y + 450, 255, 255, 255, 0); // x, y, value
    // bmpNew.set_pixel(-x + 900, y + 450, 255, 255, 255, 0);  // -x, y, value
    bmpNew.set_pixel(x + 900, -y + 450, 255, 255, 255, 0); // x, -y, value
    // bmpNew.set_pixel(-x + 900, -y + 450, 255, 255, 255, 0); // -x, -y, value

    if (sigma >= 0) {
      sigma += sigInc2 * (1 - x);
      x--;
    }
    sigma += sigInc1 * (2 * y + 3);
  }
}

int main() {
  // You can change the size of canvas
  BMP bmpNew(1800, 900, false);

  // Set the canvas to black
  bmpNew.fill_region(0, 0, 1800, 900, 0, 0, 0, 0);

  // Initialize a, b, R in: F(x,y) = (ax)^2 + (bx)^2 - R^2
  // Homework specifies a = 720, b = 360, R = 1
  int a = 720;
  int b = 360;
  int R = 1;

  // for (int i = 0; i < bmpNew.bmp_info_header.width; i++) {
  //   bmpNew.set_pixel(i, 450, 255, 255, 255, 0);
  // }
  rasterizeEllipse(a, b, bmpNew);
  bmpNew.write("output.bmp");
}
