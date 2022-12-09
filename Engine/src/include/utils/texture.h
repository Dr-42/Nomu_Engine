#pragma once
#include "defines.h"
#include <GL/glew.h>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
namespace Nomu
{
    class N_API Texture2D
    {
    public:
        // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
        u32 ID;
        // texture image dimensions
        u32 Width, Height; // width and height of loaded image in pixels
        // texture Format
        u32 Internal_Format; // format of texture object
        u32 Image_Format;    // format of loaded image
        // texture configuration
        u32 Wrap_S;     // wrapping mode on S axis
        u32 Wrap_T;     // wrapping mode on T axis
        u32 Filter_Min; // filtering mode if texture pixels < screen pixels
        u32 Filter_Max; // filtering mode if texture pixels > screen pixels
        // constructor (sets default texture modes)
        Texture2D();
        // generates texture from image data
        void Generate(u32 width, u32 height, u8 *data);
        // binds the texture as the current active GL_TEXTURE_2D texture object
        void Bind() const;
    };
}
