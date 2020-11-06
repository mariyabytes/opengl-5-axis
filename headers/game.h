#ifndef OPENGL_5_AXIS_GAME_H
#define OPENGL_5_AXIS_GAME_H

#include "include_libs.h"
#include "camera.h"
#include "objectLoader.h"

//ENUMERATIONS
enum shader_enum {
    SHADER_CORE_PROGRAM = 0
};
enum texture_enum {
    TEX_PUSHEEN = 0, TEX_PUSHEEN_SPECULAR, TEX_CONTAINER, TEX_CONTAINER_SPECULAR
};
enum material_enum {
    MAT_1 = 0
};
enum mesh_enum {
    MESH_QUAD = 0
};

enum currently_visible {
    BEZIER = 0,
    TORUS

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


    GLfloat *smZbuf{};   // depth buffer
    float iv1, iv2, iv3;

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
    long int surfaceArea;
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
 void setWindowShouldClose();

//Functions
    void updateDt();

    void updateMouseInput();

    void updateKeyboardInput();

    void updateInput();

    void update();

    void render();

    void initialRender();

    void saveDepthMap();

    void calculateNearestPixel();

    void swapTorusAndBezier();

    void rotateBezier();

    static GLfloat *calculateActualDepth(GLfloat *);

//Static functions
    static void framebuffer_resize_callback(GLFWwindow *window, int fbW, int fbH);

    static void changeRenderMode(GLFWwindow *window, int key, int scancode, int action, int mods);

    void multpleRenderCalculation();
};


#endif //OPENGL_5_AXIS_GAME_H
