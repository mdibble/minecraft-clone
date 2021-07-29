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
}

void Renderer::DrawTri() {
	shaders.basic.Bind();

	float verticies[] = {
		 0.5f,   0.5f,	0.0f,
		 0.5f,  -0.5f,	0.0f,
		-0.5f,  -0.5f,	0.0f,
		-0.5f,   0.5f,	0.0f,
	};
	unsigned int indicies[] = {
		0, 1, 3,
		1, 2, 3,
	};

	unsigned int arrayBuffer, elementBuffer, vertexArray;

	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &arrayBuffer);
	glGenBuffers(1, &elementBuffer);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &arrayBuffer);
	glDeleteBuffers(1, &elementBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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
