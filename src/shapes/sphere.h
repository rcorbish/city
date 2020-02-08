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
    std::vector<int> indices ;
    const int recursionLevel ;
    int getMiddlePoint(int p1, int p2, std::map<long,int> &cache, std::vector<Point3D> positions ) ;

protected:
    void makeVertexData() ;

public:
    Sphere( std::shared_ptr<Shader> program, int recursionLevel, std::shared_ptr<Texture> texture ) :
        Shape( program, texture ) , recursionLevel(recursionLevel) {} ;

} ;