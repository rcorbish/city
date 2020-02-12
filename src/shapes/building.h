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
        Shape( glm::vec3( longitude, 0.f, latitude), program, texture ), height(height) {} ;
} ;