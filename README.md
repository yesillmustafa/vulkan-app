# VULKAN APP

This project is a Vulkan application that demonstrates the fundamental structures of graphics programming using Object-Oriented Programming (OOP) principles.

For more information about Vulkan and detailed guides, you can visit the [Vulkan Tutorial](https://vulkan-tutorial.com/) website. This site provides step-by-step tutorials and examples for those who want to learn the Vulkan API.

https://github.com/g-truc/glm/assets/74787246/effab9f8-a8e6-464a-bdf4-d6fb9285b0ba
  
## Prerequisites

Before you begin, ensure you have met the following requirements:


- [Vulkan SDK](https://vulkan.lunarg.com/)
- [GLFW 64-bit binaries](https://www.glfw.org/download.html)
- [GLM](https://github.com/g-truc/glm/releases)
- [stb-image.h](https://github.com/nothings/stb)
- [tiny_obj_loader.h](https://github.com/tinyobjloader/tinyobjloader)

(Except Vulkan SDK, others are available in the project directory.)

## Installation and Usage

To get started, follow these steps:
1. You need to install Vulkan SDK.
(The SDK can be downloaded from the [LunarG website](https://vulkan.lunarg.com/))

2. Let's now configure the project to get rid of the errors. Open the project properties dialog and ensure that All Configurations is selected, because most of the settings apply to both Debug and Release mode.
   
![Screenshot_3](https://github.com/g-truc/glm/assets/74787246/8c95ad39-5c88-46ab-a661-b73facc83a1e)
![Screenshot_4](https://github.com/g-truc/glm/assets/74787246/6d0ac86a-43d9-452d-ae7e-5aee9955e745)


4. Go to ``` C++ -> General -> Additional Include Directories and press <Edit...>```in the dropdown box.

![Screenshot_5](https://github.com/g-truc/glm/assets/74787246/50ef87e4-dd16-4906-ad5b-d46597ce24f1)

4. Add the header directories for Vulkan, GLFW, glm, stb and tinyobjloader:,

![Screenshot_6](https://github.com/g-truc/glm/assets/74787246/a2404654-33e9-4bae-bb7a-16e4702f262f)

5. Next, open the editor for library directories under ``` Linker -> General ```:

![Screenshot_7](https://github.com/g-truc/glm/assets/74787246/931b074d-b223-4187-8ddb-5b93c2cac95d)

6. And add the locations of the object files for Vulkan and GLFW:

![Screenshot_8](https://github.com/g-truc/glm/assets/74787246/f204d5ee-114a-4109-be81-05a56bb66f80)

7. Go to ``` Linker -> Input and press <Edit...> ``` in the Additional Dependencies dropdown box.

![Screenshot_9](https://github.com/g-truc/glm/assets/74787246/8a1340f5-670d-4ad7-9d3b-0546ed8929df)

8. Enter the names of the Vulkan and GLFW object files:

![Screenshot_10](https://github.com/g-truc/glm/assets/74787246/de8e754c-cb19-4b02-9fef-167043b6cb6b)

9. And finally change the compiler to support C++17 features:

![Screenshot_11](https://github.com/g-truc/glm/assets/74787246/35505737-7273-4658-bb2f-e058b60470f1)

10. Finally, ensure that you are actually compiling in 64 bit mode:

![Screenshot_12](https://github.com/g-truc/glm/assets/74787246/51180257-053b-468e-abe3-91b7881e55de)
