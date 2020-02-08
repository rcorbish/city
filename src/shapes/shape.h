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
  float centrex ;
  float centrey ;
  float centrez ;

protected:
  GLuint  VBO ;
  GLuint  VAO ;
  GLuint  IBO ;

  std::vector<Vertex> vertexData ;
  std::vector<unsigned short> indices ;
  
  int addVertex(  float x,  float y,  float z,  float h=0.f,  float k=0.f,  float l=0.f,  float s=0.f,  float t=0.f ) ;
  int getNumVertices()  { return vertexData.size() ; } 
  virtual void makeVertexData() = 0 ;

 public:
  virtual ~Shape() ;
  Shape( float cx, float cy, float cz, std::shared_ptr<Shader> program, std::shared_ptr<Texture> texture ) ;
  Shape( std::shared_ptr<Shader> program, std::shared_ptr<Texture> texture ) : Shape(0.f,0.f,0.f,program,texture) {} ;
  void draw( glm::mat4 &matrixCamera, glm::mat4 &matrixModel ) ;

  void initVertexData() ;

  const std::vector<unsigned short> & getIndices() { return indices ; }

  static constexpr int FloatsPerVertex = 3 + 3 + 2 ;   // position + normal + texture coord
  static constexpr size_t BytesPerVertex = sizeof(float) * FloatsPerVertex ;

  static const float* PositionOffset ;
  static const float* NormalOffset ;
  static const float* TextureOffset ;
} ;


struct Vertex {
  const float x,y,z ;   // position
  const float h,k,l ;   // normal
  const float s,t ;     // texture address

  Vertex( float x, float y, float z, float h, float k, float l, float s, float t ) :
   x(x), y(y), z(z), h(h), k(k), l(l), s(s), t(t) {}
} ;

struct Point3D {
    const float x ;
    const float y ;
    const float z ;

    Point3D( const float x, const float y, const float z ) :
        x(x) ,
        y(y) ,
        z(z) {} 

    Point3D normalize() {
        float len = (float)std::sqrt( x*x + y*y + z*z ) ;
        return Point3D( x/len, y/len, z/len ) ;
    }
} ;
