#version 300 es

precision mediump float ;

uniform vec3 lightPos ;  
uniform sampler2D shaderTexture ;

layout(location = 0) out vec4 fragColor ;

precision mediump float;
in vec3 FragPos ;
in vec3 RawPos ;

void main()
{ 
  vec3 normal = normalize( FragPos );
  vec3 lightDir = normalize( vec3(1,3,6) - FragPos ) ;
  float diff = max( dot( normal, lightDir ), 0.0 ) ;
  float lat = acos( RawPos.y ) / 3.14159265358979  ;
  float lon = ( atan( RawPos.x, RawPos.z ) + 3.14159265358979 ) / 6.28318530717959;
  vec2 TexCoord = vec2( lon, lat ) ;
  fragColor = texture(shaderTexture, TexCoord);
  // fragColor = min( (diff + .1), 1.0 ) * fragColor  ;
}             