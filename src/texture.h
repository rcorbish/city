#pragma once

#include <glm/glm.hpp>  

class Texture {
    private:
        GLuint texture ;
        const int textureUnit ;
    public:
        Texture( int textureUnit, const char *image_file ) ;
        ~Texture() ;

        void use() ;
        GLuint getTexture() { return texture ; }
        int getTextureUnit() { return textureUnit ; }
} ; 