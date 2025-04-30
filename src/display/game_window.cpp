#include "display/game_window.hpp"
#include "shaders/shader.hpp"
#include <iostream>
#include <glm.hpp>
#include <gtc/type_ptr.inl>
#include <string>


// Template stuff
Shader s;
unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

// Called whenever the window or framebuffer's size is changed
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// 1. The first thing that is run when starting the window
void GameWindow::Initialize() {
    // Set GLFW stuff before window is created
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

// 2. Run after the window has been created, as well as the OpenGL context
void GameWindow::LoadContent() {
    // Set callback
    glfwSetFramebufferSizeCallback(this->windowHandle, FramebufferSizeCallback);

    // Initialize imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->windowHandle, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    std::cout << "INFO::IMGUI::SUCCESSFULLY_INITIALIZED" << std::endl;

    // Load the template shader
    s = Shader::LoadShader("resources/shaders/testing.vs", "resources/shaders/testing.fs");
    //s = Shader::LoadShader("resources/shaders/lit.vert", "resources/shaders/lit.frag");

    // Vertices needed for a square
    float vertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };

    // Indices for rendering the above square
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Create Vertex Array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // And bind it

    // Create Vertex Buffer object
    glGenBuffers(1, &VBO);
    // And bind it (this also includes it into the VAO)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Fill the VBO with vertex data, simply positions
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // layout = 0 should contain these positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // Enable that shit

    // Create index buffer
    glGenBuffers(1, &EBO);
    // And bind it (also included in VAO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Fill with indices!
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void GameWindow::Update() {
    // Performs hot-reload of shader. Only reloads whenever it has been modified - so not every frame.
    s.ReloadFromFile();
}

void GameWindow::Render() {
    // Bind the VAO
    glBindVertexArray(VAO);

    // Make sure we're using the correct shader program.
    // Must be done per-frame, since the shader program id might change when hot-reloading
    glUseProgram(s.programID);

    // Create new imgui frames
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Clear the window
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);



    // set camera view in shader
    // testin .vs and .fs
    // 
    // set mat4s
    glUniformMatrix4fv(glGetUniformLocation(s.programID, "viewProjection"), 1, GL_FALSE, glm::value_ptr(cam.projectionMatrix() * cam.viewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(s.programID, "model"), 1, GL_FALSE, glm::value_ptr(terrainTrans.getModelMatrix()));


    // set lowest and highest
    glUniform1f(glGetUniformLocation(s.programID, "lowest"), noiseData.lowestCurr);
    glUniform1f(glGetUniformLocation(s.programID, "highest"), noiseData.highestCurr);


    terrainMesh.Draw();

    // Draw imgui
    //ImGui::ShowDemoWindow();
    {
        ImGui::Begin("Noise Generation Variables");
        ImGui::Text("Hold Right Click = Enable Camera Movement + Rotation");
        ImGui::Text("WASD = Move, Space = Up, Shift = Down");

        // render methods
        /*
        if (ImGui::Button("Solid View"))
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
        }
        if (ImGui::Button("Wireframe View"))
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        */

        // seed
        if (ImGui::InputInt("Seed", &noiseData.seed, -2147483646, 2147483646))
        {
            terrainMesh.GenerateMesh(noiseData);
        }
        
        if (ImGui::Button("Random Seed"))
        {
            noiseData.seed = std::rand();
            terrainMesh.GenerateMesh(noiseData);
        }
        
        const char* noiseTypes[] = { "OpenSimplex2", "OpenSimplex2S", "Cellular", "Perlin", "ValueCubic", "Value" };
        //static int currNoise = noiseData.noiseType;
        if (ImGui::ListBox("Noise Type", &noiseData.noiseType, noiseTypes, IM_ARRAYSIZE(noiseTypes), 4))
        {
            terrainMesh.GenerateMesh(noiseData);
        }

        if (ImGui::SliderInt("Width", &noiseData.width, 1, 1000))
        {
            terrainMesh.GenerateMesh(noiseData);
            camController.flySpeed = noiseData.width * 0.18;
        }
        //ImGui::SliderInt("Height", &noiseData.height, 1, 10000);
        if (ImGui::SliderInt("Subdivisions", &noiseData.subdivisions, 1, 500))
        {
            terrainMesh.GenerateMesh(noiseData);
        }

        if (ImGui::SliderFloat("Frequency", &noiseData.frequency, 0, 10))
        {
            terrainMesh.GenerateMesh(noiseData);
        }
        if (ImGui::SliderFloat("Amplitude", &noiseData.amplitude, 0, 50))
        {
            terrainMesh.GenerateMesh(noiseData);
        }
        /*
        if (ImGui::SliderFloat("Redistribution (WIP)", &noiseData.redistribution, 0, 10))
        {
            terrainMesh.GenerateMesh(noiseData);
        }
        */
        if (ImGui::SliderFloat("Lowest Point", &noiseData.lowestPoint, -50, 50))
        {
            terrainMesh.GenerateMesh(noiseData);
        }
        if (ImGui::SliderFloat("Highest Point", &noiseData.highestPoint, -50, 50))
        {
            terrainMesh.GenerateMesh(noiseData);
        }
        /*
        if (ImGui::SliderFloat("Domain Warp", &noiseData.domainWarp, -20, 20))
        {
            terrainMesh.GenerateMesh(noiseData);
        }
        */

        //ImGui::InputInt("Level Of Detail", &noiseData.levelOfDetail, 1, 10);

        
        const char* fractalTypes[] = { "None", "FBm", "Ridged", "PingPong"};
        //static int currFractal = noiseData.noiseType;
        if (ImGui::ListBox("Fractal Type", &noiseData.fractalType, fractalTypes, IM_ARRAYSIZE(fractalTypes), 4))
        {
            terrainMesh.GenerateMesh(noiseData);
        }
        if (ImGui::SliderInt("Fractal Octaves", &noiseData.fractalOctaves, 0, 8))
        {
            terrainMesh.GenerateMesh(noiseData);
        }

        // regenerate Mesh Button
        /*
        if (ImGui::Button("Regenerate Mesh"))
        {
            terrainMesh.GenerateMesh(noiseData);
            std::cout << "Mesh Regenerated" << std::endl;
        }
        */
       
        /*
        std::string buffer;
        if (ImGui::InputText("File Output", &buffer, 50))
        {
            fileLocation = buffer;

        }
        */
        
        if (ImGui::InputText("Filename(Do Not Include File Extension)", fileNameBuffer, IM_ARRAYSIZE(fileNameBuffer)))
        {
            meshFileName = fileNameBuffer;
        }
        

        if (ImGui::Button("Export to OBJ"))
        {
            terrainMesh.SaveToObj(meshFileName + ".obj");
            std::cout << "saved to file" << std::endl;
        }

        ImGui::End();
    }
    
    ImGui::Render();
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    // Swap double buffers and poll OS-events
    glfwSwapBuffers(this->windowHandle);
    glfwPollEvents();
}

void GameWindow::Unload() {
    // Destroy imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}