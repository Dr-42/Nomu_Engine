#pragma once
#include "defines.h"
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "utils/texture.h"
#include "utils/shader.h"

namespace Nomu
{
    /// Holds all state information relevant to a character as loaded using FreeType
    struct Character
    {
        u32 TextureID; // ID handle of the glyph texture
        glm::ivec2 Size;        // size of glyph
        glm::ivec2 Bearing;     // offset from baseline to left/top of glyph
        u32 Advance;   // horizontal offset to advance to next glyph
    };

    // A renderer class for rendering text displayed by a font loaded using the
    // FreeType library. A single font is loaded, processed into a list of Character
    // items for later rendering.
    class N_API TextRenderer
    {
    public:
        // holds a list of pre-compiled Characters
        std::map<ch, Character> Characters;
        // shader used for text rendering
        Shader *TextShader;
        // constructor
        TextRenderer(u32 width, u32 height, Shader *shader);
        // pre-compiles a list of characters from the given font
        void Load(std::string font, u32 fontSize);
        // renders a string of text using the precompiled list of characters
        void RenderText(std::string text, f32 x, f32 y, f32 scale, glm::vec3 color = glm::vec3(1.0f));

        Shader *GetShader();

    private:
        // render state
        u32 VAO, VBO;
    };
}