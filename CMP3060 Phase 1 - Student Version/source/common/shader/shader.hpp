#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace our
{

    class ShaderProgram
    {

    private:
        // Shader Program Handle
        GLuint program;

    public:
        void create();
        void destroy();

        ~ShaderProgram() { destroy(); }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use()
        {
            // TODO: call opengl to use the program identified by this->program
            glUseProgram(this->program);
        }

        GLuint getUniformLocation(const std::string &name)
        {
            // TODO: call opengl to get the uniform location for the uniform defined by name from this->program
            const char *nameCStr = name.c_str(); // openGl needs char pointer instead of string
            return glGetUniformLocation(this->program, nameCStr);
        }

        void set(const std::string &uniform, GLfloat value)
        {
            // TODO: call opengl to set the value to the uniform defined by name
            // get the uniform location from the shader program
            GLuint uniformLoc = getUniformLocation(uniform);

            // set the float uniform value with the passed value
            glUniform1f(uniformLoc, value);
        }

        void set(const std::string &uniform, glm::vec2 value)
        {
            // TODO: call opengl to set the value to the uniform defined by name
            // get the uniform location from the shader program
            GLuint uniformLoc = getUniformLocation(uniform);

            // set the vec2 uniform value with the passed value
            // GLsizei (1) is the count of vectors to be modified
            glUniform2fv(uniformLoc, 1, glm::value_ptr(value));
        }

        void set(const std::string &uniform, glm::vec3 value)
        {
            // TODO: call opengl to set the value to the uniform defined by name
            // get the uniform location from the shader program
            GLuint uniformLoc = getUniformLocation(uniform);

            // set the vec3 uniform value with the passed value
            // GLsizei (1) is the count of vectors to be modified
            glUniform3fv(uniformLoc, 1, glm::value_ptr(value));
        }

        void set(const std::string &uniform, glm::vec4 value)
        {
            // TODO: call opengl to set the value to the uniform defined by name
            // get the uniform location from the shader program
            GLuint uniformLoc = getUniformLocation(uniform);

            // set the vec4 uniform value with the passed value
            // GLsizei (1) is the count of vectors to be modified
            glUniform4fv(uniformLoc, 1, glm::value_ptr(value));
        }

        // TODO: Delete the copy constructor and assignment operator
        // Question: Why do we do this? Hint: Look at the deconstructor
    };

}

#endif