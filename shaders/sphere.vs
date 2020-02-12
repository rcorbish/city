#version 300 es

layout (location = 0) in vec3 aPos ; 
layout (location = 1) in vec3 aNormal ;
layout (location = 2) in vec2 inputTexCoord ;

uniform mat4 CAMERA ;  
uniform mat4 MODEL ;  
uniform vec2 textureOffset ;  

out vec3 FragPos ;
out vec3 RawPos ;

void main() 
{
   gl_Position = CAMERA * MODEL * vec4(aPos, 1.0f) ;
   FragPos = vec3( gl_Position ) ;
   RawPos = normalize( vec3( aPos ) ) ;
}  