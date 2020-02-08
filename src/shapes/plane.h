#pragma once

#include <vector>
#include "shape.h"

class Plane : public Shape {
private :
    const float extent ;
    
protected:
    void makeVertexData() ;

public:
    Plane( float cx, float cy, float cz, float extent, std::shared_ptr<Shader> program, std::shared_ptr<Texture> texture ) :
        Shape( cx, cy, cz, program, texture ), extent(extent) {} ;
    Plane( float extent, std::shared_ptr<Shader> program, std::shared_ptr<Texture> texture ) :
        Plane( 0, 0, 0, extent, program, texture ) {} ;
} ;