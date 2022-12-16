# VulkanEngine
 C++ Vulkan Game Engine

This is my most recent one of my personal projects aimed to get me familiar with both C++ and Vulkan, as I have had yet to make use of them.

## CURRENTLY WORKING ON 
- Integrating Dear ImGui

## NEXT STEPS:
- Push Vulkan Renderer in its own 'Sub-Window'
- establish basic UI Parts, e.g. Viewport, Console, Scene-Hierarchy
- Setup scalable data structure for a 'Scene' containing an object hierarchy of Nodes containing Meshes

## IMPLEMENTED:
- Vulkan initial setup
- Rendering arbitrary amounts of unique 3D Meshes
- Scene Camera Controller (Panning, FreeLook, Orbiting, Zoom)
- Scene World Grid with indicated XZ Axis

## CURRENT STATE

![VulkanEngine](https://github.com/LeonPapadopoulos/VulkanEngine/blob/main/VulkanEngine/images/VulkanEngine_Viewport_01Dec22.PNG)

## DISCLAIMER:
Won't build as is! Needs the list of external dependencies referenced in its project settings. Also make sure to swap the filepaths to test meshes in scene.cpp for your own, while providing the appropriate .obj files in the meshes folder. [-> Meshes using only 1 Material!]

This project is still very much in its earliest stages of development. As such, many elements and systems have yet to be properly refined to make them usable in a more general sense.
Once an initial User Interface is established, actually working with the engine during execution, meaning dynamically loading in meshes and moving them around the scene shall be possible. Until then, most things may have to be hardcoded for testing purposes.

### EXTERNAL DEPENDENCIES:
###### VULKAN - VULKAN SDK 1.3.231.1
###### WINDOWING - GLFW https://www.glfw.org/
###### 3D MATHS - GLM https://github.com/g-truc/glm
###### MESH IMPORT - tinyobjloader https://github.com/tinyobjloader/tinyobjloader
###### IMAGE IMPORT - https://github.com/nothings/stb

### LEARNING RESSOURCES
###### Vulkan Tutorial 1 https://vulkan-tutorial.com/
###### Vulkan Tutorial 2 https://vkguide.dev/
###### Cherno C++ Series https://www.youtube.com/watch?v=18c3MTX0PK0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb
