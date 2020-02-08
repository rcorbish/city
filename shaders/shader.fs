#version 320 es

precision mediump float ;

uniform vec3 lightPos ;  
uniform sampler2D shaderTexture ;

in vec3 Normal ;
in vec3 FragPos ;
in vec2 TexCoord ;

layout(location = 0) out vec4 fragColor ;

void main()
{    
    vec3 norm = normalize( Normal ) ;
    vec3 lightDir = normalize( lightPos - FragPos ) ;

    float diff = max( dot( norm, lightDir ), 0.0 ) ;

	vec4 textureColor = texture(shaderTexture, TexCoord) ;
    fragColor = min( (diff + .3), 1.0 ) * textureColor ;
    fragColor = textureColor ;
    //fragColor = vec4( 1, 0, 0, 1 ) ;
}
