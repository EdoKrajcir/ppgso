// Task 1 - Load a 512x512 image lena.raw
//        - Apply specified per-pixel transformation to each pixel
//        - Save as result.raw
#include <fstream>
#include <iostream>

// Size of the framebuffer
const unsigned int SIZE = 512;

// A simple RGB struct will represent a pixel in the framebuffer
struct Pixel {
  // TODO: Define correct data type for r, g, b channel
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

int main()
{
  // Initialize a framebuffer
  auto framebuffer = new Pixel[SIZE][SIZE];

  // TODO: Open file lena.raw (this is 512x512 RAW GRB format)

    FILE *file;
    file = fopen("lena.raw","rb");
    if (file == NULL) {printf("neny obrazok!!!\n");}


    // TODO: Read data to framebuffer and close the file

    fread( framebuffer, sizeof(Pixel), SIZE * SIZE, file );
    fclose( file );



  // Traverse the framebuffer
  for (unsigned int y = 0; y < SIZE; y++) {
    for (unsigned int x = 0; x < SIZE; x++) {
      // TODO: Apply pixel operation


      /*
       * GREYSCALE
      auto greyscale = static_cast<uint8_t >(0.3 * framebuffer[y][x].r + 0.59 * framebuffer[y][x].g + 0.11 * framebuffer[y][x].b);
      framebuffer[y][x].r = greyscale;
      framebuffer[y][x].g = greyscale;
      framebuffer[y][x].b = greyscale;
      */

      /*
       * INVERT
      framebuffer[y][x].r = 255 - framebuffer[y][x].r;
      framebuffer[y][x].g = 255 - framebuffer[y][x].g;
      framebuffer[y][x].b = 255 - framebuffer[y][x].b;
      */
      framebuffer[y][x].r = static_cast<uint8_t>(framebuffer[y][x].r + 0.2 * (rand() % 255));
      framebuffer[y][x].g = static_cast<uint8_t>(framebuffer[y][x].g + 0.2 * (rand() % 255));
      framebuffer[y][x].b = static_cast<uint8_t>(framebuffer[y][x].b + 0.2 * (rand() % 255));

      if (framebuffer[y][x].r > 255) {framebuffer[y][x].r = 255;}
      if (framebuffer[y][x].g > 255) {framebuffer[y][x].g = 255;}
      if (framebuffer[y][x].b > 255) {framebuffer[y][x].b = 255;}
    }
  }

  // TODO: Open file result.raw
  std::cout << "Generating result.raw file ..." << std::endl;

    FILE *file2 = fopen("result.raw","wb");
    if (file2 == NULL) {printf("neny obrazok!!!\n");}

    // TODO: Write the framebuffer to the file and close it

    fwrite( framebuffer, sizeof(Pixel), SIZE * SIZE, file2);
    fclose(file2);


  std::cout << "Done." << std::endl;
  delete[] framebuffer;
  return EXIT_SUCCESS;
}
