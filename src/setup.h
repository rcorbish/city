 
#pragma once

#include <glm/gtc/matrix_transform.hpp>

// ----------------------------------------------------------
// What to do when a key is pressed
// ----------------------------------------------------------
void keypress_func( unsigned char key, int x, int y ) ;
 
// ----------------------------------------------------------
// Open GL setup function
// ----------------------------------------------------------
void setup( void (*display_func)(), int argc, char* argv[] ) ;

extern glm::mat4 matrixModelPerspective ;

extern float rotate_y ; 
extern float rotate_x ;
extern float rotate_z ;

extern bool pause_clock ;
extern bool freeze ;
extern float tmpx  ;
extern float tmpy ;

constexpr float SCREEN_WIDTH = 25.f ;
constexpr float SCREEN_HEIGHT = 25.f ;
constexpr float SCREEN_DEPTH = 25.f ;
