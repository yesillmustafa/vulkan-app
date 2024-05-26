#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Device.h"
#include "Vertex.h"
#include "Buffers.h"

class VertexBuffer {
public:
	VertexBuffer(Device* devicePtr, Buffers* buffersPtr);

	void createVertexBuffer();
	VkBuffer& getVertexBuffer();
	VkDeviceMemory_T*& getVertexBufferMemory();

	void createIndexBuffer();
	VkBuffer& getIndexBuffer();
	VkDeviceMemory_T*& getIndexBufferMemory();

private:

	Device* devicePtr;
	Buffers* buffersPtr;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

};

#endif // !VERTEXBUFFER_HPP
