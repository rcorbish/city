#pragma once

#include <glm/glm.hpp>  

class Texture {
    private:
        GLuint texture ;
    public:
        Texture( const char *image_file ) ;
        operator GLuint() { return texture ; }
} ;