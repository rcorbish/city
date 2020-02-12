 
#include "shape.h"


constexpr int FloatsPerVertex = 3 + 3 + 2 ;   // position + normal + texture coord
constexpr size_t BytesPerVertex = sizeof(float) * FloatsPerVertex ;

float* PositionOffset = nullptr ;
float* NormalOffset = PositionOffset + 3 ;
float* TextureOffset = NormalOffset + 3 ;


Shape::Shape( const glm::vec3 &centre, 
                std::shared_ptr<Shader> program, 
                std::shared_ptr <Texture> texture ) 
                : centre(centre) {
    this->program = program ;
    this->texture = texture ;
    textureOffset.x = 0 ;
    textureOffset.y = 0 ;
}


void Shape::draw( glm::mat4 &matrixCamera, glm::mat4 &matrixModel ) {

    glm::mat4 translate = glm::translate( glm::mat4(1.f), centre ) ;
    glm::mat4 finalModel = matrixModel * translate ;

    this->program->use() ;
    this->program->setMatrix( "CAMERA", glm::value_ptr(matrixCamera) ) ;
    this->program->setMatrix( "MODEL", glm::value_ptr(finalModel) ) ;
    this->program->setVec2( "textureOffset", glm::value_ptr(textureOffset) ) ;

    glActiveTexture( GL_TEXTURE0 ) ; 
    glBindTexture(GL_TEXTURE_2D, *texture ) ;

    glBindVertexArray( VAO ) ;
    glDrawElements( GL_TRIANGLES, indices.size(),  GL_UNSIGNED_SHORT, nullptr ) ;
}

int Shape::addVertex(  float x,  float y,  float z,  float h,  float k,  float l,  float s,  float t ) {
    vertexData.emplace_back( x, y, z, h, k, l, s, t ) ;
    return vertexData.size() - 1 ;
}

int Shape::addVertex( const Vertex & vertex ) {
    vertexData.emplace_back( vertex ) ;
    return vertexData.size() - 1 ;
}

void Shape::initVertexData() {
    makeVertexData() ;

    size_t verticesSize = getNumVertices() * BytesPerVertex ;
    
    // vertex arrays
    glGenVertexArrays( 1, &VAO ) ;
    glBindVertexArray( VAO ) ;

    // vertex buffer object
    GLuint  VBO ;
    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO ) ;
    glBufferData( GL_ARRAY_BUFFER, verticesSize, &vertexData[0], GL_STATIC_DRAW ) ;

    glEnableVertexAttribArray( 0 ) ;  // location(0) = aPos
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, BytesPerVertex, PositionOffset ) ;

    glEnableVertexAttribArray( 1 ) ;  // location(1) = normal
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, BytesPerVertex, NormalOffset ) ;

    glEnableVertexAttribArray( 2 ) ;  // location(2) = texture
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, BytesPerVertex, TextureOffset ) ;

    // index buffer object
    GLuint  IBO ;
    glGenBuffers(1, &IBO );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO ) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW );

    glBindVertexArray( 0 ) ;
    glDeleteBuffers( 1, &IBO ) ; 
    glDeleteBuffers( 1, &VBO ) ; 
}

void Shape::moveBy( const glm::vec3 &vec ) {
    centre += vec ;
}
void Shape::moveTo( const glm::vec3 &vec ) {
    centre = vec ;
}
