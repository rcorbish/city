
#include "plane.h"


// ----------------------------------------------------------
// makeVertexData() function
// 
// each point is 3 floats (x,y,z)
//
// e.g.
//  float vertices [ 3*num_triangles ] ;
//
// ----------------------------------------------------------
void Plane::makeVertexData() {
  
  vertexData.reserve( 4 ) ;   // 4 corners in a plane
  /*
        2 -- 3
       /    /
      0 -- 1
  */
  int texMin = (int)( -extent / 6 ) ;
  if( texMin == 0 ) texMin = -1 ;
  int texMax = -texMin ;
  
  addVertex( -extent, 0.f, -extent, 0, 1, 0, texMin, texMin ) ;     // 0
  addVertex(  extent, 0.f, -extent, 0, 1, 0, texMax, texMin ) ;     // 1
  addVertex( -extent, 0.f,  extent, 0, 1, 0, texMin, texMax ) ;     // 2
  addVertex(  extent, 0.f,  extent, 0, 1, 0, texMax, texMax ) ;     // 3

  indices.reserve( 6 ) ;

  indices.push_back( 2 ) ;
  indices.push_back( 1 ) ;
  indices.push_back( 0 ) ;
  indices.push_back( 3 ) ;
  indices.push_back( 1 ) ;
  indices.push_back( 2 ) ;
} 
