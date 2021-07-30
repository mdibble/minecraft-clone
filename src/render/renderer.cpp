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

    std::cout << "Initializing renderer" << std::endl;
    shaders.Init();
	vertexArrays.Init();
}

void Renderer::DrawPoly() {
	shaders.basic.Bind();
	vertexArrays.basic.Bind();

	float verticies[] = {
		 0.5f,   0.5f,	 0.0f,       0.0f,   0.0f,
		 0.5f,  -0.5f,	 0.0f,       0.0f,   0.0f,
		-0.5f,  -0.5f,	 0.0f,       0.0f,   0.0f,
		-0.5f,   0.5f,	 0.0f,       0.0f,   0.0f,
	};

	unsigned int indicies[] = {
		0, 1, 3,
		1, 2, 3,
	};

	vertexArrays.basic.SendVerticies(verticies, sizeof(verticies));
	vertexArrays.basic.SendIndicies(indicies, sizeof(indicies));

	vertexArrays.basic.Draw();

	vertexArrays.Unbind();
	shaders.Unbind();
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
