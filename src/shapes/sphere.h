#pragma once

#include <map>
#include <vector>

#include "shape.h"

/**
 * Create a sphere mesh, using icosphere rules
 *
 * @link http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
 *
 */
class Sphere : public Shape {
private:
    const int recursionLevel ;
    int getMiddlePoint(int p1, int p2, std::map<long,int> &cache ) ;

protected:
    void makeVertexData() ;
    int  addVertex(  float x,  float y,  float z ) ;

public:
    Sphere( const glm::vec3 &centre, std::shared_ptr<Shader> program, std::shared_ptr<Texture> texture, int recursionLevel=2 ) :
        Shape( centre, program, texture ) , recursionLevel(recursionLevel) {} ;

} ;