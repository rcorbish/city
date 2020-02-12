#version 320 es

precision highp float ;

layout (location = 0) in vec3 aPos ; 
layout (location = 1) in vec3 aNormal ;
layout (location = 2) in vec2 inputTexCoord ;

uniform mat4 CAMERA ;  
uniform mat4 MODEL ;  
uniform vec2 textureOffset ;  

out vec3 Normal ;
out vec3 FragPos ; 
out vec2 TexCoord ;

void main()
{
    gl_Position = CAMERA * MODEL * vec4(aPos, 1.0f) ;
    FragPos = vec3( gl_Position ) ;
    Normal = vec3( MODEL * vec4( normalize(aNormal) , 1.0f) ) ;
    TexCoord = inputTexCoord + textureOffset ;
}
