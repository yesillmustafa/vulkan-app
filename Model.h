#ifndef MODEL_HPP
#define MODEL_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Vertex.h"
#include <unordered_map>
#include <string>


const std::string MODEL_PATH = "models/viking_room.obj";
const std::string TEXTURE_PATH = "textures/viking_room.png";

class Model {
public:
	void loadModel();
private:

};

#endif // !MODEL_HPP
