// Example gl2_texture
// - Demonstrates how to load raw texture data as input for a shader
// - Texture coordinates are passed using additional vertex buffer object
// - The texture itself is loaded from raw RGB image file directly into OpenGL
// NOTE: For convenience use ppgso::Texture that can load BMP and RAW files

#include <iostream>
#include <vector>
#include <fstream>

#include <ppgso/ppgso.h>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

const unsigned int SIZE = 512;

/*!
 * Custom window to display textured OpenGL quad
 */
class TextureWindow : public ppgso::Window {
private:
  // OpenGL program and Mesh to use
  ppgso::Shader program = {texture_vert_glsl, texture_frag_glsl};
  ppgso::Mesh quad = {"quad.obj"};
  GLuint texture_id = 0;

  /*!
   * Load new image from file and set it up for use in OpenGL
   * @param image_file Name of the file to load (RAW RGB format)
   * @param width Width of the image to load
   * @param height Height of the image to load
   */
  void loadImage(const std::string &image_file, int width, int height) {
    // Create new OpenGL texture object identifier
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Set mipmapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Read raw data
    std::ifstream image_stream(image_file, std::ios::binary);

    // Setup buffer for pixels (r,g,b bytes), since we will not manipulate the image just keep it as char
    std::vector<char> buffer(static_cast<std::size_t>(width * height * 3));
    image_stream.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
    image_stream.close();

    // Send the data to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

    // Generate lower resolution variants of the image
    glGenerateMipmap(GL_TEXTURE_2D);
 }

public:
  /*!
   * Texture window constructor that will initialize the OpenGL texture and pass it to the shader program
   */
  TextureWindow() : Window{"gl2_texture", SIZE, SIZE} {
    // Load the image from file
    loadImage("result.raw", SIZE, SIZE);

    // Set the program uniform input "Texture" to the loaded data
    auto texture_attrib = program.getUniformLocation("Texture");

    glUniform1i(texture_attrib, 0);
    glActiveTexture(GL_TEXTURE0 + 0);

    // Bind the texture for use
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Set Matrices to identity so there are no projections/transformations applied in the vertex shader
    program.setUniform("ModelMatrix", glm::mat4{1.0f});
    program.setUniform("ViewMatrix", glm::mat4{1.0f});
    program.setUniform("ProjectionMatrix", glm::mat4{1.0f});
  }

  /*!
   * Free OpenGL resources
   */
  ~TextureWindow() override {
    glDeleteTextures(1, &texture_id);
  }

  /*!
   * Window refresh implementation that will be called automatically from pollEvents when needed
   */
  void onRefresh() override {
    // Set gray background
    glClearColor(.5f, .5f, .5f, 0);

    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the geometry
    quad.render();
  }
};

int main() {
  // Create our window instance
  TextureWindow window;

  // Main execution loop
  while (window.pollEvents()) {}

  return EXIT_SUCCESS;
}
