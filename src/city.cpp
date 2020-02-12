 

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>     /* srand, rand */

#define GL_GLEXT_PROTOTYPES
#include <GL/freeglut.h>
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

#include "city.h"
#include "shader.h"
#include "setup.h"
#include "texture.h"

#include "sphere.h"
#include "building.h"
#include "plane.h"
#include "group.h"

glm::vec3 eye( 0, 0.5, -2 ) ;

std::shared_ptr<Plane> ground ;
std::shared_ptr<Group> scene ;
std::vector<std::shared_ptr<Texture>> buildingTextures ;

std::shared_ptr<Group> createScene() ;


// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){

  if( !freeze ) { 
 // Rotate scene
    rotate_z = 0.01f ;
    // rotate_y += 0.003f ;
    // rotate_z += 0.005f ;
  }
// update fold - if at either end of fold
// pause fold effects temporarily
  if( !pause_clock ) {
  } 
  
  //  Clear screen ard Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
  // Model rotation
  glm::mat4 matrixModel = glm::rotate( glm::mat4(1.0), -rotate_y, glm::vec3(0.0, 1.0, 0.0) );
  // matrixModel = glm::rotate( matrixModel, -rotate_z, glm::vec3(0.0, 0.0, 1.0) );
  // matrixModel = glm::rotate( matrixModel, -rotate_x, glm::vec3(1.0, 0.0, 0.0) );

  eye = eye + glm::vec3( rotate_x, rotate_y, rotate_z ) ;
  glm::vec3 look = eye + glm::vec3( 0, -0.5, 2 ) ;
  glm::mat4 matrixModelView = glm::lookAt( eye, look, glm::vec3(0, 1, 0) ) ;

  glm::mat4 matrixCamera = matrixModelPerspective * matrixModelView ;

  ground->moveTo( eye ) ;
  scene->draw( matrixCamera, matrixModel ) ;

  glFlush();
  glutSwapBuffers();

  glutPostRedisplay();
}
 

 
// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main( int argc, char* argv[] ) {
  srand48( 21 ) ;
  setup( display, argc, argv ) ;

  scene = createScene() ;

  glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ;
  //  Run display
  glutMainLoop() ;

  // std::cout << "Use of ground " << ground.use_count() << std::endl ;

  //  Return to OS
  return 0 ;
}


std::shared_ptr<Group> createScene() {
  glm::vec3 lightPos( 0.f, 5.f, 5.f ) ;

  std::shared_ptr<Shader> baseShader = std::make_shared<Shader>( "shaders/shader.vs", "shaders/shader.fs" ); 
  baseShader->use() ;
  baseShader->setVec3( "lightPos", glm::value_ptr( lightPos ) ) ;

  std::shared_ptr<Shader> sphereShader = std::make_shared<Shader>( "shaders/sphere.vs", "shaders/sphere.fs" ); 
  sphereShader->use() ;
  sphereShader->setVec3( "lightPos", glm::value_ptr( lightPos ) ) ;

  // Find all textures in this subdir
  std::string path = "textures/buildings/" ;

  struct dirent *entry;
  DIR *dir = opendir( path.c_str() );
  if (dir != NULL) {
    while ((entry = readdir(dir)) != NULL) {
      std::string fullPath = path + entry->d_name ;
      if( entry->d_type == DT_REG ) {
        buildingTextures.emplace_back( std::make_shared<Texture>( fullPath.c_str() ) ) ;
      }
    }
    closedir(dir);
  }

  auto concrete = std::make_shared<Texture>( "textures/ground/TexturesCom_ConcreteNew0063_2_seamless_S.jpg" ) ;
  auto bitumen = std::make_shared<Texture>( "textures/ground/TexturesCom_RooftilesBitumen0031_1_S.jpg" ) ;
  auto sand = std::make_shared<Texture>( "textures/ground/TexturesCom_SoilSand0203_1_seamless_S.jpg" ) ;

  scene = std::make_shared<Group>() ;

  ground = std::make_shared<Plane>( 25.f, baseShader, sand ) ;
  ground->initVertexData() ;
  scene->add( ground ) ;

  // Make some buildings ...
  for( int i=0 ; i<20 ; ++i ) {
    float lon = ( drand48() - 0.5f ) * 18.f ;
    float lat = ( drand48() - 0.5f ) * 18.f ;
    float height = 1.0f + drand48() * 5.f ;

    int texIndex = (int)( drand48() * buildingTextures.size() ) ;
    
    std::shared_ptr<Shape> building = std::make_shared<Building>( lon, lat, height, baseShader, buildingTextures[texIndex] ) ;
    building->initVertexData() ;
    scene->add( building ) ;
    std::shared_ptr<Shape> roof = std::make_shared<Plane>( glm::vec3( lon, height, lat), 0.5, baseShader, (i&1)==0? concrete : bitumen ) ; 
    roof->initVertexData() ;
    scene->add( roof ) ;
  }

  std::shared_ptr<Shape> ball = std::make_shared<Sphere>( glm::vec3(-2, 11, -5), sphereShader, bitumen, 3 ) ;
  ball->initVertexData() ;
  scene->add( ball ) ;

  return scene ;
}