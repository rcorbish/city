 
#include "group.h"
#include <algorithm>

Group::Group() {
}

void Group::add( std::shared_ptr<Shape> shape ) {

  // unsigned short *firstIndex = nullptr ;
  // firstIndex += indices.size() ;
  // shape->setBaseIndex( firstIndex ) ;

  // const std::vector<unsigned short> & newIndices = shape->getIndices() ;
  // indices.insert( std::end(indices), std::begin(newIndices), std::end(newIndices) ) ;

  shapes.push_back( shape ) ;
}

void Group::remove( std::shared_ptr<Shape> shape ) {
  auto it = std::find(shapes.begin(), shapes.end(), shape );
  if(it != shapes.end())
    shapes.erase(it);
}

int Group::size() { return shapes.size() ; }

std::shared_ptr<Shape> Group::operator[]( const int ix ) {
  return shapes[ix] ;
}

void Group::draw( glm::mat4 &matrixCamera, glm::mat4 &matrixModel ) {
  for( auto shape : shapes ) {
    shape->draw( matrixCamera, matrixModel ) ;
  }
}
