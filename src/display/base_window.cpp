#include "display/base_window.hpp"
#include <iostream>

#include "terrain_gen/perlin_generator.hpp"

BaseWindow::BaseWindow() {

}

BaseWindow::BaseWindow(int width, int height, std::string title) {
    this->windowWidth = width;
    this->windowHeight = height;
    this->windowTitle = title;
}

int BaseWindow::Run() {
    // Iniialize GLFW
    glfwInit();

    // Run initialisation logic
    Initialize();

    // Create GLFW Window
    windowHandle = glfwCreateWindow(this->windowWidth, this->windowHeight, this->windowTitle.c_str(), NULL, NULL);
    if (windowHandle == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set opengl context
    glfwMakeContextCurrent(windowHandle);

    // Attempt to load using glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "INFO::WINDOW::SUCCESSFULLY_INITIALIZED" << std::endl;

    // Runs load content which might include stuff that requires an opengl context
    LoadContent();


    // setup camera
    cam.position = glm::vec3(0.0f, 30.0f, 0.0f);
    cam.lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
    cam.aspectRatio = (float)this->windowWidth / this->windowHeight;
    cam.FOV = 60.0f;

    // camera controller
    camController.flySpeed = 20;
    camController.sensitivity = 0.05f;

    camController.forwardKey = GLFW_KEY_W;
    camController.leftKey = GLFW_KEY_A;
    camController.backwardKey = GLFW_KEY_S;
    camController.rightKey = GLFW_KEY_D;
    camController.upKey = GLFW_KEY_SPACE;
    camController.downKey = GLFW_KEY_LEFT_SHIFT;
    camController.unlockCamKey = GLFW_KEY_E;


    std::srand(std::time(0));
    terrainMesh = Mesh(noiseData);

    terrainTrans.position = glm::vec3(1.0f, 0.0f, 0.0f);
    terrainTrans.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    terrainTrans.scale = glm::vec3(1.0f, 1.0f, 1.0f);


    NoiseData noiseData;


    // toggle for wireframe view
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Main game loop
    while (!glfwWindowShouldClose(windowHandle)) {
        Update();
        
        float time = (float)glfwGetTime();
        deltaTime = time - prevFrameTime;
        prevFrameTime = time;

        // move camera
        camController.moveCamera(windowHandle, deltaTime, &cam);
        //std::cout << cam.position.x << std::endl;



        Render();
    }

    // Unload and destroy 
    Unload();
    glfwDestroyWindow(windowHandle);
    glfwTerminate();
    return 0;
}