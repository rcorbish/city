#pragma once

#include <vector>
#include "shape.h"

class Plane : public Shape {
private :
    const float extent ;
    
protected:
    void makeVertexData() ;

public:
    Plane( glm::vec3 centre, float extent, std::shared_ptr<Shader> program, std::shared_ptr<Texture> texture ) :
        Shape( centre, program, texture ), extent(extent) {} ;
    Plane( float extent, std::shared_ptr<Shader> program, std::shared_ptr<Texture> texture ) :
        Plane( glm::vec3(0,0,0), extent, program, texture ) {} ;

    void draw( glm::mat4 &matrixCamera, glm::mat4 &matrixModel ) ;
} ;