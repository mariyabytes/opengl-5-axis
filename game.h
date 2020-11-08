#ifndef OPENGL_5_AXIS_GAME_H
#define OPENGL_5_AXIS_GAME_H

#include "headers/include_libs.h"
#include "headers/camera.h"
#include "headers/objectLoader.h"

//ENUMERATIONS
enum shader_enum {
    SHADER_CORE_PROGRAM = 0
};
enum texture_enum {
    TEX_PUSHEEN [[maybe_unused]] = 0,
    TEX_PUSHEEN_SPECULAR [[maybe_unused]],
    TEX_CONTAINER [[maybe_unused]],
    TEX_CONTAINER_SPECULAR [[maybe_unused]]
};
enum material_enum {
    MAT_1 [[maybe_unused]] = 0
};
enum mesh_enum {
    MESH_QUAD [[maybe_unused]] = 0
};

enum currently_visible {
    BEZIER = 0,
    TORUS

};

class Pixel {
public:
    long int index;
    float x_cord;
    float y_cord;
    float depth;
};

class Game {
private:
//Variables
    //Window
    GLFWwindow *window;
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    int framebufferWidth;
    int framebufferHeight;

    //OpenGL Context
    const int GL_VERSION_MAJOR;
    const int GL_VERSION_MINOR;

    //Delta time
    float dt;
    float curTime;
    float lastTime;

    //Mouse Input
    double lastMouseX;
    double lastMouseY;
    double mouseX;
    double mouseY;
    double mouseOffsetX;
    double mouseOffsetY;
    bool firstMouse;

    //Camera
    Camera camera;

    //Matrices
    glm::mat4 ViewMatrix{};
    glm::vec3 camPosition{};
    glm::vec3 worldUp{};
    glm::vec3 camFront{};

    glm::mat4 ProjectionMatrix{};
    float fov;
    float nearPlane;
    float farPlane;

    //Shaders
    std::vector<Shader *> shaders;

    //Materials
    std::vector<Material *> materials;

    //Models
    std::vector<Model *> models;

    //Lights
    std::vector<glm::vec3 *> lights;

    GLfloat *depthPixels;

//    Ortho matrix stuff

    float mat_left;
    float mat_right;
    float mat_top;
    float mat_bottom;

    bool currently_visible;

    Model *bezierModel{};
    Model *torusModel{};

//Private functions
    static void initGLFW();

    void initWindow(
            const char *title,
            bool resizable
    );

    static void initGLEW(); //AFTER CONTEXT CREATION!!!
    void initOpenGLOptions();

    void initMatrices();

    void initShaders();

    void initMaterials();

    void initModels();

    void initLights();

    void initUniforms();

    void updateUniforms();



//Static variables

public:
    long int closestPixel;
    float scaleFactor{};


//Constructors / Destructors
    Game(
            const char *title,
            int WINDOW_WIDTH, int WINDOW_HEIGHT,
            int GL_VERSION_MAJOR, int GL_VERSION_MINOR,
            bool resizable
    );

    virtual ~Game();

//Accessors
    int getWindowShouldClose();

//Modifiers

    void setOrthoMatrixBounds(float left, float right, float bottom, float top);

//Functions
    void updateDt();

    [[maybe_unused]] void updateMouseInput();

    void updateKeyboardInput();

    void updateInput();

    void update();

    void render();

    void initialRender();

    void saveDepthMap();

    Pixel *calculateNearestPixel();

    void swapTorusAndBezier();

    [[maybe_unused]] void rotateBezier();

    [[maybe_unused]] static GLfloat *reCalculateClosestPoint(GLfloat *);

//Static functions
    static void framebuffer_resize_callback([[maybe_unused]] GLFWwindow *window, int fbW, int fbH);

    static void
    changeRenderMode([[maybe_unused]] GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action,
                     [[maybe_unused]] int mods);

    void recalculateDepthMap();

    Pixel * reCalculateNearestPixel();

    void setNewScaleFactor(float tolerance);

};


#endif //OPENGL_5_AXIS_GAME_H
