
#include "building.h"


// ----------------------------------------------------------
// makeBase() function
// 
// vertices should hold ( num_triangles + 2 ) points
// each point is 3 floats (x,y,z)
//
// e.g.
//  float vertices [ 3*num_triangles ] ;
//
// ----------------------------------------------------------
void Building::makeVertexData() {
  
  vertexData.reserve( 8*8 ) ;   // 8 vertices in a cube

  /*
        6 -- 7
       /|   /|
      4 -- 5 |
      | |  | |
      | 2 -| 3
      |/   | /
      0 -- 1
  */
  addVertex( -0.5, 0,  0.5, 0, 0, 0, 0, 0 ) ;     // 0
  addVertex(  0.5, 0,  0.5, 0, 0, 0, 1, 0 ) ;     // 1
  addVertex( -0.5, 0, -0.5, 0, 0, 0, 1, 0 ) ;     // 2
  addVertex(  0.5, 0, -0.5, 0, 0, 0, 0, 0 ) ;     // 3
  float h = int(height+1.f) ;
  addVertex( -0.5, height,  0.5, 0, 0, 0, 0, h ) ;     // 4
  addVertex(  0.5, height,  0.5, 0, 0, 0, 1, h ) ;     // 5 
  addVertex( -0.5, height, -0.5, 0, 0, 0, 1, h ) ;     // 6
  addVertex(  0.5, height, -0.5, 0, 0, 0, 0, h ) ;     // 7

  indices.reserve( 30 ) ;
  // front
  indices.push_back( 1 ) ;
  indices.push_back( 4 ) ;
  indices.push_back( 0 ) ;
  indices.push_back( 5 ) ;
  indices.push_back( 4 ) ;
  indices.push_back( 1 ) ;
  // left
  indices.push_back( 0 ) ; 
  indices.push_back( 6 ) ; 
  indices.push_back( 2 ) ; 
  indices.push_back( 4 ) ; 
  indices.push_back( 6 ) ; 
  indices.push_back( 0 ) ; 
  // right
  indices.push_back( 3 ) ; 
  indices.push_back( 5 ) ; 
  indices.push_back( 1 ) ; 
  indices.push_back( 3 ) ; 
  indices.push_back( 7 ) ; 
  indices.push_back( 5 ) ; 
  // back
  indices.push_back( 2 ) ; 
  indices.push_back( 6 ) ; 
  indices.push_back( 3 ) ; 
  indices.push_back( 3 ) ; 
  indices.push_back( 6 ) ; 
  indices.push_back( 7 ) ; 
  // top
  // indices.push_back( 4 ) ; 
  // indices.push_back( 6 ) ; 
  // indices.push_back( 5 ) ; 
  // indices.push_back( 6 ) ; 
  // indices.push_back( 7 ) ; 
  // indices.push_back( 5 ) ; 
  // no bottom needed !  

} 
