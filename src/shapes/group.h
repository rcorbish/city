 
#pragma once

#include <vector>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>

#include "shape.h"

extern glm::mat4 matrixCamera ;

class Group {
  private :
    std::vector<std::shared_ptr<Shape>> shapes ;

  protected :
  public :
    Group() ;

    void add( std::shared_ptr<Shape> shape ) ;
    void remove( std::shared_ptr<Shape> shape ) ;

    int size() ;

    std::shared_ptr<Shape> operator[]( const int ix ) ;

    void draw( glm::mat4 &matrixCamera, glm::mat4 &matrixModel ) ;
} ;