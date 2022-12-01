# VulkanEngine
 C++ Vulkan Game Engine


This is my most recent one of my personal projects aimed to get me familiar with both C++ and Vulkan, as I have had yet to make use of them.

Changelog & Plans:

IMPLEMENTED:
- Vulkan initial setup
- Rendering arbitrary amounts of unique 3D Meshes


NEXT STEPS:
- Setup scalable data structure for a 'Scene' containing an object hierarchy of Meshes
- Import Dear ImGui 
- Push Vulkan Renderer in its own 'Sub-Window'
- establish basic UI Parts, e.g. Viewport, Console, Scene-Hierarchy



#EXTERNAL DEPENDENCIES:

VULKAN
- VULKAN SDK 1.3.231.1

WINDOWING
- GLFW https://www.glfw.org/

3D MATHS
- GLM https://github.com/g-truc/glm

MESH IMPORT
- tinyobjloader https://github.com/tinyobjloader/tinyobjloader

IMAGE IMPORT
- https://github.com/nothings/stb
