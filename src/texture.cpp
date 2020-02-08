
#ifdef DEBUG_LOG
    #include <iostream>
    #define LOG   std::cout << "Here " << __FILE__  << " " << __LINE__ << std::endl ;
#else
    #define LOG
#endif
#define GL_GLEXT_PROTOTYPES

#include <GL/glut.h>
#include <glm/glm.hpp>  

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h" 

#include "texture.h" 

Texture::Texture( const char *image_file ) {

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
  LOG
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  LOG
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char * data = stbi_load( image_file, &width, &height, &nrChannels, 0);
    if (data)
    {
  LOG
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1) ;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  LOG
        glGenerateMipmap(GL_TEXTURE_2D);
  LOG
        stbi_image_free(data);
    }
  LOG
 }

