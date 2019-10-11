// Task 3 - Implement Bresenham drawing alg.
//        - Draw a star using lines
//        - Make use of std::vector to define the shape
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

#include <ppgso/ppgso.h>

// Size of the framebuffer
const unsigned int SIZE = 512;

struct Point {
  int x,y;
};

struct Pixel {
    // TODO: Define correct data type for r, g, b channel
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// Bresenham drawing algorithm
void drawLine(ppgso::Image& framebuffer, Point& from, Point& to) {
  // TODO: Implement Bresenham drawing algorithm
        int x = from.x;
        int y = from.y;
        //int m = 0;
        //if ((to.x-from.x) == 0) {m = 99999999;}
        //else {m = (to.y-from.y)/(to.x-from.x);}
        int dx = abs(to.x-from.x), sx = from.x<to.x ? 1 : -1;
        int dy = -abs(to.y-from.y), sy = from.y<to.y ? 1 : -1;
        int e = dx+dy, e2;

        while(true){
            framebuffer.setPixel(x,y,255,255,255);
            if (x==to.x && y==to.y) break;
            e2 = 2*e;
            if (e2 >= dy) {e += dy; x += sx;}
            if (e2 <= dx) {e += dx; y += sy;}
        }


        /*if (m < -1) {
            int e = -(to.x - from.x);
            while (abs(x - to.x) > 0) {
                framebuffer.setPixel(x, y, 255, 255, 255);
                x += 1;
                e += 2 * (to.y - from.y);
                if (e > 0) {
                    y += 1;
                    e -= 2 * (to.x - from.x);
                }
            }
        }

         if ((m >= -1 ) && (m < 0)) {
             int e = -(to.x - from.x);
             while (abs(x - to.x) > 0) {
                 framebuffer.setPixel(x, y, 255, 255, 255);
                 x += 1;
                 e += 2 * (to.y - from.y);
                 if (e > 0) {
                     y += 1;
                     e -= 2 * (to.x - from.x);
                 }
             }

             if ((m <= 1) && (m >= 0)) {
                 int e = -(to.x - from.x);
                 while (abs(x - to.x) > 0) {
                     framebuffer.setPixel(x, y, 255, 255, 255);
                     x += 1;
                     e += 2 * (to.y - from.y);
                     if (e > 0) {
                         y += 1;
                         e -= 2 * (to.x - from.x);
                     }
                 }
             }
             if (m > 1) {
                 int e = -(to.y - from.y);
                 while (abs(y - to.y) > 0) {
                     framebuffer.setPixel(x, y, 255, 255, 255);
                     y += 1;
                     e += 2 * (to.x - from.x);
                     if (e > 0) {
                         x += 1;
                         e -= 2 * (to.y - from.y);
                     }
                 }
             }
         }*/
        /*while(x<=to.x) {
            framebuffer.setPixel(x,y,255,255,255);
            x += 1;
            e += 2*(to.y - from.y);
            if(e>0) {
                y += 1;
                e -= 2*(to.x-from.x);
            }
        }*/
}

int main()
{
  // Use ppgso::Image as our framebuffer
  ppgso::Image framebuffer(SIZE, SIZE);

  // TODO: Generate star points
  std::vector<Point> points;
  points.insert(points.end(),{SIZE/2,0});
  points.insert(points.end(),{0, SIZE/2});
  points.insert(points.end(),{SIZE/2, SIZE});
  points.insert(points.end(),{SIZE, SIZE/2});
  points.insert(points.end(),{SIZE/2,0});
  //points.insert(points.end(),{SIZE/2,SIZE});

  // Draw lines
  for(unsigned int i = 0; i < points.size() - 1; i++)
    drawLine(framebuffer, points[i], points[i+1]);

  // Save the result
  std::cout << "Generating task2_bresenham.bmp file ..." << std::endl;
  ppgso::image::saveBMP(framebuffer, "task2_bresenham.bmp");

  std::cout << "Done." << std::endl;
  return EXIT_SUCCESS;
}

