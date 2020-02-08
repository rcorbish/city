#pragma once

#include <vector>
#include "shape.h"

class Building : public Shape {
private :
    const float height ;
protected:
    void makeVertexData() ;

public:
    Building( float longitude, float latitude, float height, std::shared_ptr<Shader> program, std::shared_ptr<Texture> texture ) :
        Shape( longitude, 0, latitude, program, texture ), height(height) {} ;
} ;