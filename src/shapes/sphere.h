#pragma once

#include "shape.h"

class Sphere : public Shape {
protected:
    void makeVertexData( float *vertices ) ;
    const int recirsionLevel ;

public:
    Sphere( std::shared_ptr<Shader> program, int recursionLevel, std::shared_ptr<Texture> texture ) :
        Shape( program, 20+4*recursionLevel, texture ) : recursionLevel(recursionLevel) {} ;

    void initVertexData() ;
} ;