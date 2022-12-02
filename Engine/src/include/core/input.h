#pragma once
#include "defines.h"
#include "core/app.h"

namespace Nomu
{
    class N_API Input
    {
    public:
        static Input &getInstance();
        static void SetApp(App* app);

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

        static void framebufferSizeCallbackImpl(GLFWwindow* window, int width, int height);
        static void keyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void cursorPositionCallbackImpl(GLFWwindow* window, double xpos, double ypos);
        static void mouseButtonCallbackImpl(GLFWwindow* window, int button, int action, int mods);

        static glm::vec2 GetMousePos();
    private:
        Input(void) = default;
        Input(Input const &);
        void operator=(Input const &);

        static App *mApp;
    };
}

#define NOMU_KEY_SPACE              32
#define NOMU_KEY_APOSTROPHE         39  
#define NOMU_KEY_COMMA              44  
#define NOMU_KEY_MINUS              45  
#define NOMU_KEY_PERIOD             46  
#define NOMU_KEY_SLASH              47  
#define NOMU_KEY_0                  48
#define NOMU_KEY_1                  49
#define NOMU_KEY_2                  50
#define NOMU_KEY_3                  51
#define NOMU_KEY_4                  52
#define NOMU_KEY_5                  53
#define NOMU_KEY_6                  54
#define NOMU_KEY_7                  55
#define NOMU_KEY_8                  56
#define NOMU_KEY_9                  57
#define NOMU_KEY_SEMICOLON          59  
#define NOMU_KEY_EQUAL              61  
#define NOMU_KEY_A                  65
#define NOMU_KEY_B                  66
#define NOMU_KEY_C                  67
#define NOMU_KEY_D                  68
#define NOMU_KEY_E                  69
#define NOMU_KEY_F                  70
#define NOMU_KEY_G                  71
#define NOMU_KEY_H                  72
#define NOMU_KEY_I                  73
#define NOMU_KEY_J                  74
#define NOMU_KEY_K                  75
#define NOMU_KEY_L                  76
#define NOMU_KEY_M                  77
#define NOMU_KEY_N                  78
#define NOMU_KEY_O                  79
#define NOMU_KEY_P                  80
#define NOMU_KEY_Q                  81
#define NOMU_KEY_R                  82
#define NOMU_KEY_S                  83
#define NOMU_KEY_T                  84
#define NOMU_KEY_U                  85
#define NOMU_KEY_V                  86
#define NOMU_KEY_W                  87
#define NOMU_KEY_X                  88
#define NOMU_KEY_Y                  89
#define NOMU_KEY_Z                  90
#define NOMU_KEY_LEFT_BRACKET       91  
#define NOMU_KEY_BACKSLASH          92  
#define NOMU_KEY_RIGHT_BRACKET      93  
#define NOMU_KEY_GRAVE_ACCENT       96  
#define NOMU_KEY_WORLD_1            161 
#define NOMU_KEY_WORLD_2            162 

/* Function keys */
#define NOMU_KEY_ESCAPE             256
#define NOMU_KEY_ENTER              257
#define NOMU_KEY_TAB                258
#define NOMU_KEY_BACKSPACE          259
#define NOMU_KEY_INSERT             260
#define NOMU_KEY_DELETE             261
#define NOMU_KEY_RIGHT              262
#define NOMU_KEY_LEFT               263
#define NOMU_KEY_DOWN               264
#define NOMU_KEY_UP                 265
#define NOMU_KEY_PAGE_UP            266
#define NOMU_KEY_PAGE_DOWN          267
#define NOMU_KEY_HOME               268
#define NOMU_KEY_END                269
#define NOMU_KEY_CAPS_LOCK          280
#define NOMU_KEY_SCROLL_LOCK        281
#define NOMU_KEY_NUM_LOCK           282
#define NOMU_KEY_PRINT_SCREEN       283
#define NOMU_KEY_PAUSE              284
#define NOMU_KEY_F1                 290
#define NOMU_KEY_F2                 291
#define NOMU_KEY_F3                 292
#define NOMU_KEY_F4                 293
#define NOMU_KEY_F5                 294
#define NOMU_KEY_F6                 295
#define NOMU_KEY_F7                 296
#define NOMU_KEY_F8                 297
#define NOMU_KEY_F9                 298
#define NOMU_KEY_F10                299
#define NOMU_KEY_F11                300
#define NOMU_KEY_F12                301
#define NOMU_KEY_F13                302
#define NOMU_KEY_F14                303
#define NOMU_KEY_F15                304
#define NOMU_KEY_F16                305
#define NOMU_KEY_F17                306
#define NOMU_KEY_F18                307
#define NOMU_KEY_F19                308
#define NOMU_KEY_F20                309
#define NOMU_KEY_F21                310
#define NOMU_KEY_F22                311
#define NOMU_KEY_F23                312
#define NOMU_KEY_F24                313
#define NOMU_KEY_F25                314
#define NOMU_KEY_KP_0               320
#define NOMU_KEY_KP_1               321
#define NOMU_KEY_KP_2               322
#define NOMU_KEY_KP_3               323
#define NOMU_KEY_KP_4               324
#define NOMU_KEY_KP_5               325
#define NOMU_KEY_KP_6               326
#define NOMU_KEY_KP_7               327
#define NOMU_KEY_KP_8               328
#define NOMU_KEY_KP_9               329
#define NOMU_KEY_KP_DECIMAL         330
#define NOMU_KEY_KP_DIVIDE          331
#define NOMU_KEY_KP_MULTIPLY        332
#define NOMU_KEY_KP_SUBTRACT        333
#define NOMU_KEY_KP_ADD             334
#define NOMU_KEY_KP_ENTER           335
#define NOMU_KEY_KP_EQUAL           336
#define NOMU_KEY_LEFT_SHIFT         340
#define NOMU_KEY_LEFT_CONTROL       341
#define NOMU_KEY_LEFT_ALT           342
#define NOMU_KEY_LEFT_SUPER         343
#define NOMU_KEY_RIGHT_SHIFT        344
#define NOMU_KEY_RIGHT_CONTROL      345
#define NOMU_KEY_RIGHT_ALT          346
#define NOMU_KEY_RIGHT_SUPER        347
#define NOMU_KEY_MENU               348

#define NOMU_KEY_LAST               GLFW_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for 
 *
 *  @ingroup input
 *  @{ */

/*! @brief If this bit is set one or mor
 *
 *  If this bit is set one or more Shift
 */
#define NOMU_MOD_SHIFT           0x0001
/*! @brief If this bit is set one or mor
 *
 *  If this bit is set one or more Contr
 */
#define NOMU_MOD_CONTROL         0x0002
/*! @brief If this bit is set one or mor
 *
 *  If this bit is set one or more Alt k
 */
#define NOMU_MOD_ALT             0x0004
/*! @brief If this bit is set one or mor
 *
 *  If this bit is set one or more Super
 */
#define NOMU_MOD_SUPER           0x0008
/*! @brief If this bit is set the Caps L
 *
 *  If this bit is set the Caps Lock key
 *  NOMU_LOCK_KEY_MODS input mode is set
 */
#define NOMU_MOD_CAPS_LOCK       0x0010
/*! @brief If this bit is set the Num Lo
 *
 *  If this bit is set the Num Lock key 
 *  NOMU_LOCK_KEY_MODS input mode is set
 */
#define NOMU_MOD_NUM_LOCK        0x0020