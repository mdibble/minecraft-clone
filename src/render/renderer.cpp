#include "renderer.h"

Renderer::Renderer() {
	window = nullptr;
	viewportW = 1920;
	viewportH = 1080;
}

void Renderer::Init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(viewportW, viewportH, "Lightning", NULL, NULL);
	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
		Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
		renderer->ViewportResizeCallback(w, h);
	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
		renderer->KeyCallback(key, scancode, action, mods);
	});

	glfwMakeContextCurrent(window);

	gladLoadGL();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// VSync
	// glfwSwapInterval(0);

    std::cout << "Initializing renderer" << std::endl;
	vertexArrays.Init();
}

void Renderer::DrawMesh(float vert[], int vertCount, unsigned int ind[], int indCount) {
	vertexArrays.basic.Bind();

	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, (float)sin(glfwGetTime()) * glm::vec3(0.5f, 0.0f, 0.0f));
	trans = glm::translate(trans, (float)cos(glfwGetTime()) * glm::vec3(0.0f, 0.5f, 0.0f));

	vertexArrays.basic.shader.SetMat4("transform", glm::value_ptr(trans));

	vertexArrays.basic.SendVerticies(vert, vertCount);
	vertexArrays.basic.SendIndicies(ind, indCount);

	vertexArrays.basic.Draw();

	vertexArrays.basic.Unbind();
}

void Renderer::DrawSky() {
	static float vert[] = {
		-1.0f,  -1.0f,	 0.0f,       0.0f,   0.0f,
		-1.0f,   1.0f,	 0.0f,       0.0f,   1.0f,
		 1.0f,   1.0f,	 0.0f,       1.0f,   1.0f,
		 1.0f,  -1.0f,	 0.0f,       1.0f,   0.0f,
	};

	static unsigned int ind[] = {
		0, 1, 2,
		0, 2, 3,
	};

	vertexArrays.sky.Bind();

	vertexArrays.sky.SendVerticies(vert, sizeof(vert));
	vertexArrays.sky.SendIndicies(ind, sizeof(ind));

	vertexArrays.sky.Draw();

	vertexArrays.sky.Unbind();
}

void Renderer::BeginFrame() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::EndFrame() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Renderer::ViewportResizeCallback(int w, int h) {
	viewportW = w;
	viewportH = h;
	glViewport(0, 0, viewportW, viewportH);
	std::cout << "Resize callback" << std::endl;
}

void Renderer::KeyCallback(int key, int scancode, int action, int mods) {
	std::cout << "Key callback" << std::endl;
}
