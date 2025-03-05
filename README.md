# Assignment: Solo Centerpiece Project Proposal

## This project was made from this OpenGL + imgui cmake template by dcronqvist: https://github.com/dcronqvist/opengl-imgui-cmake-template

## Samuel Barnett | Procedural 3D Terrain Generation

### 1. **Project Objectives**
- The goal of this project is to create a program in c++ that can generate a 3D mesh of world terrain based on user inputs and save it in a usable file format for popular game engines like Unity or Unreal Engine.
- This project is significant to my portfolio and career for two primary reasons. The first reason is that this project is highly visual and interactive for the user. This allows anyone viewing my portfolio to be able to get their hands on it and play with it. The second reason is that this project would prove that I am capable of handling complex problems and creating tools that can be used by others. Both of these reasons will contribute to my ability to succeed in the process of getting a job.

### 2. **Tools and Technologies**
- I am making this project in C++ using visual studio. C++ is the language I am most familiar with. Additionally, it has access to some libraries and toolkits that I think will be helpful for this project.
- OpenGL is used as the graphics library for this project. I have experience using OpenGL to render geometry and I believe it is suitable for rendering the terrain I generate.
- ImGui is used to make the user interface. I have experience setting up usable menus in ImGui and allowing for the user to interact with the program.
- FastNoiseLite by Jordan Peck is used to generate noise values based on a seed and various inputs. This library offers several noise generation options.
- Autodesk FBX Software Developer Kit will be used for exporting the generated geometry into a usable format. I have not used this toolkit before so it may become a large time investment as I continue to research its usage.

### 3. **Scope**
- The user will be able to generate procedural 3D terrain using perlin noise based on several exposed variables. These variables will include a seed, minimum and maximum height values, erosion modifiers, and potentially more. An ImGui interface will be used to display and edit these variables. Once this mesh is generated, it will be exportable in a FBX file format. This FBX file can then be imported into popular game engines like Unity or Unreal Engine.
- I anticipate that I will experience difficulty with the exporting of FBX files and the generation of terrain based on erosion.

### 4. **Deliverables**
- By the end of the project I intend to deliver a playable demo on the git repository. On my portfolio page there will be technical information explaining specific systems and how to use the tool as well as a video of the program working.




## Progress So Far
- Mesh drawing is functional.
  - Requires lighting so that mesh is not one flat color, currently the mesh is wireframe to allow player to see.
- User camera control is functional.
  - User should be able to change movement speed and turning sensitivity in application.
- Noise application to mesh is functonal, some variables need tinkering with to be usable by user.
  - Level of detail options are in progress.
  - Some Fractal Options need to be given to user.
  - Erosion is incomplete.
- Saving mesh data to fbx file is incomplete.
  - Havent started yet.


## Plan To Complete
- Saving mesh data to fbx file format is next on my to-do list.
  - Will begin over spring break. I expect this to take the most time out of anything in the project so I will not going to delay work on it until after break.
- Level of Detail options are in progress but are second on my to-do list.
- Applying erosion to terrain is low priority. If I have time I will give it a shot.
- Other issues are low risk and shouldn't take much effort.
