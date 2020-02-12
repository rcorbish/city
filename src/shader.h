
#pragma once


#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <glm/glm.hpp>  
#include <glm/gtc/type_ptr.hpp>
// #include <glm/gtc/matrix_transform.hpp>

class Shader
{
  private:
        GLuint ID;
  protected:
        void checkCompileErrors(unsigned int shader, std::string type) ;
  public:
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath) ;
    // activate the shader
    // ------------------------------------------------------------------------
    void use() 
    { 
        glUseProgram(ID); 
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const ;
    void setInt(const std::string &name, int value) const ;
    void setFloat(const std::string &name, float value) const ;
    void setMatrix(const std::string &name, const GLfloat * value) const ;
    void setVec3(const std::string &name, const GLfloat * value) const ;
    void setVec2(const std::string &name, const GLfloat * value) const ;
};


