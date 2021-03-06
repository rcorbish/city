#pragma once 

#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <memory>

#include <shader.h>
#include <texture.h>

struct Vertex ;

class Shape {

private:
  std::shared_ptr<Shader> program ;
  std::shared_ptr<Texture> texture ;

protected:
  GLuint  VAO ;

  glm::vec3 centre ;

  glm::vec2 textureOffset ;
  std::vector<Vertex> vertexData ;
  std::vector<unsigned short> indices ;
  
  int addVertex( float x, float y,  float z, float h=0.f, float k=0.f, float l=0.f, float s=0.f, float t=0.f ) ;
  int addVertex( const Vertex & vertex ) ;
  int getNumVertices()  { return vertexData.size() ; } 
  virtual void makeVertexData() = 0 ;

 public:
  Shape( const glm::vec3 &centre, std::shared_ptr<Shader> program, std::shared_ptr<Texture> texture ) ;
  Shape( std::shared_ptr<Shader> program, std::shared_ptr<Texture> texture ) : Shape( glm::vec3(0,0,0), program,texture) {} ;
  virtual void draw( glm::mat4 &matrixCamera, glm::mat4 &matrixModel ) ;

  void initVertexData() ;

  const std::vector<unsigned short> & getIndices() { return indices ; }
  void moveBy( const glm::vec3 & vec ) ;
  void moveTo( const glm::vec3 & vec ) ;
} ;


struct Vertex {
  const float x,y,z ;   // position
  const float h,k,l ;   // normal
  const float s,t ;     // texture address

  Vertex( float x, float y, float z, float h, float k, float l, float s, float t ) :
   x(x), y(y), z(z), h(h), k(k), l(l), s(s), t(t) {}
  Vertex( const Vertex &v ) : Vertex( v.x, v.y, v.z, v.h, v.k, v.l, v.s, v.t ) {}
} ;


struct Point3D {
    const float x ;
    const float y ;
    const float z ;

    Point3D( const float x, const float y, const float z ) : x(x), y(y), z(z) {} 
    Point3D( const Point3D &p ) : Point3D( p.x, p.y, p.z ) {}

    Point3D normalize() {
        float len = (float)std::sqrt( x*x + y*y + z*z ) ;
        return Point3D( x/len, y/len, z/len ) ;
    }
} ;
