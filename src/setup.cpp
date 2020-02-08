 

#include <stdio.h>
#include <stdarg.h>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
// #include <glm/glm.hpp>  
// #include <glm/gtc/type_ptr.hpp>

#include <memory>

#include "setup.h"


// ----------------------------------------------------------
// Initial scene rotations
// ----------------------------------------------------------
float rotate_y=0; 
float rotate_x=0;
float rotate_z=0;

glm::mat4 matrixCamera ;

float tmpx = 0.00001 ;
float tmpy = 0 ;

bool pause_clock = false ;
bool freeze = false ;

// What to do in case of key press
void keypress_func( unsigned char key, int x, int y ) {
  if( key == 'x' ) {
    pause_clock = !pause_clock ;
  }
  if( key == 'f' ) {
    freeze = !freeze ;
  }
  if( key == 'w' ) {
    tmpy += 0.01 ;
    std::cout << tmpx << "," << tmpy << std::endl ;
  }
  if( key == 's' ) {
    tmpy -= 0.01 ;
    std::cout << tmpx << "," << tmpy << std::endl ;
  }
  if( key == 'a' ) {
    tmpx -= 0.01 ;
    std::cout << tmpx << "," << tmpy << std::endl ;
  }
  if( key == 'd' ) {
    tmpx += 0.01 ;
    std::cout << tmpx << "," << tmpy << std::endl ;
  }

  if( key == '1' ) {
    rotate_y=0 ; 
    rotate_x=0 ;
    rotate_z=0 ;
  }
  if( key == '2' ) {
    rotate_y=0 ; 
    rotate_x=M_PI_4 ;
    rotate_z=0 ;
  }
  if( key == '3' ) {
    rotate_y=M_PI_4 ; 
    rotate_x=M_PI_4 ;
    rotate_z=0 ;
  }
  if( key == '4' ) {
    rotate_y=M_PI_4 ; 
    rotate_x=0 ;
    rotate_z=0 ;
  }
  if( key == 'q' ) {
    exit( 0 ) ;
  }
}


 

 
// ----------------------------------------------------------
// Open GL setup function
// ----------------------------------------------------------
void setup( void (*display_func)(), int argc, char* argv[] ) {
 
  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
 
  //  Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  // Create window
  glutCreateWindow("Discus");
  glutReshapeWindow( 400, 400 );

  // Add keypress listener for current window
  glutKeyboardFunc( keypress_func ) ;

  //  Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D) ;
  glEnable(GL_CULL_FACE) ;

  glViewport( 0.f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
  
  glm::mat4 matrixModelPerspective = glm::ortho( -SCREEN_WIDTH/2.f, SCREEN_WIDTH/2.f, -SCREEN_HEIGHT/2.f, SCREEN_HEIGHT/2.f, -SCREEN_DEPTH/2.f, SCREEN_DEPTH/2.f ); // essentially set coordinate system
  glm::mat4 matrixModelView = glm::lookAt( glm::vec3(0, .5, -2 ), glm::vec3(0, 0.0, 0.0), glm::vec3(0, 1, 0) ) ;

  matrixCamera = matrixModelPerspective * matrixModelView ;

  // Callback functions
  glutDisplayFunc( display_func ) ;
 
}
