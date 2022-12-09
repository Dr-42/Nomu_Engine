#pragma once
#include "defines.h"
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility
// functions for easy management.
namespace Nomu
{
    class N_API Shader
    {
    public:
        // state
        u32 ID;
        // constructor
        Shader() {}
        // sets the current shader as active
        Shader &Use();
        // compiles the shader from given source code
        void Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr); // note: geometry source code is optional
        // utility functions
        void SetFloat(const char *name, f32 value, bl useShader = false);
        void SetInteger(const char *name, i32 value, bl useShader = false);
        void SetVector2f(const char *name, f32 x, f32 y, bl useShader = false);
        void SetVector2f(const char *name, const glm::vec2 &value, bl useShader = false);
        void SetVector3f(const char *name, f32 x, f32 y, f32 z, bl useShader = false);
        void SetVector3f(const char *name, const glm::vec3 &value, bl useShader = false);
        void SetVector4f(const char *name, f32 x, f32 y, f32 z, f32 w, bl useShader = false);
        void SetVector4f(const char *name, const glm::vec4 &value, bl useShader = false);
        void SetMatrix4(const char *name, const glm::mat4 &matrix, bl useShader = false);

    private:
        // checks if compilation or linking failed and if so, print the error logs
        void checkCompileErrors(u32 object, std::string type);
    };
}
