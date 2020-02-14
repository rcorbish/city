
#define GL_GLEXT_PROTOTYPES

#include <GL/glut.h>
#include <glm/glm.hpp>  

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h" 

#include "texture.h" 

Texture::~Texture() {
    glActiveTexture( GL_TEXTURE0 + textureUnit ) ;
    glDeleteTextures( 1, &texture ) ;
}


Texture::Texture( int textureUnit, const char *image_file ) : textureUnit(textureUnit) {

    glGenTextures( 1, &texture );
    this->use() ;

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ) ;	
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT ) ;
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR ) ;
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR ) ;

    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load( true ) ;
    unsigned char * data = stbi_load( image_file, &width, &height, &nrChannels, 0 ) ;
    if( data ) {
        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ) ;
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data ) ;

        glGenerateMipmap( GL_TEXTURE_2D ) ;

        stbi_image_free( data ) ;
    }
 }

void Texture::use() {
    glActiveTexture( GL_TEXTURE0 + textureUnit ) ;
    glBindTexture( GL_TEXTURE_2D, texture ) ;
}
