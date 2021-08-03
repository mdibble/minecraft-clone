#include "renderer.h"

Renderer::Renderer() {
	window = nullptr;
	inputHandler = nullptr;
	dt = nullptr;
	viewportW = 1920;
	viewportH = 1080;
}

void Renderer::Init(InputHandler* inputHandlerPointer, float* dtPointer) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(viewportW, viewportH, "Lightning", NULL, NULL);
	glfwSetWindowUserPointer(window, this);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
		Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
		renderer->ViewportResizeCallback(w, h);
	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
		renderer->KeyCallback(key, scancode, action, mods);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
		renderer->MouseCallback(xpos, ypos);
	});

	glfwMakeContextCurrent(window);

	inputHandler = inputHandlerPointer;
	dt = dtPointer;

	gladLoadGL();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// VSync
	// glfwSwapInterval(0);

	glEnable(GL_DEPTH_TEST);

    std::cout << "Initializing renderer" << std::endl;
	vertexArrays.Init();
}

void Renderer::DrawMesh(float vert[], int vertCount, unsigned int ind[], int indCount) {
	vertexArrays.basic.Bind();

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 view = camera.GenViewMat();

	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), (float)viewportW / (float)viewportH, 0.1f, 100.0f);

	vertexArrays.basic.shader.SetMat4("model", glm::value_ptr(model));
	vertexArrays.basic.shader.SetMat4("view", glm::value_ptr(view));
	vertexArrays.basic.shader.SetMat4("proj", glm::value_ptr(proj));

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float camSpeed = 2.0f * *dt;

	if (inputHandler->IsKeyPressed(GLFW_KEY_W)) {
		camera.MoveAlongFront(camSpeed);
	}
	if (inputHandler->IsKeyPressed(GLFW_KEY_S)) {
		camera.MoveAlongFront(-camSpeed);
	}
	if (inputHandler->IsKeyPressed(GLFW_KEY_A)) {
		camera.MovePerpFromFront(-camSpeed);
	}
	if (inputHandler->IsKeyPressed(GLFW_KEY_D)) {
		camera.MovePerpFromFront(camSpeed);
	}
}

void Renderer::EndFrame() {
	inputHandler->NeutralizeMouseOffset();
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Renderer::IsActive() {
	return !glfwWindowShouldClose(window);
}

void Renderer::ViewportResizeCallback(int w, int h) {
	viewportW = w;
	viewportH = h;
	glViewport(0, 0, viewportW, viewportH);
	// std::cout << "Resize callback" << std::endl;
}

void Renderer::KeyCallback(int key, int scancode, int action, int mods) {
	// std::cout << "Key callback" << std::endl;
	inputHandler->HandleKeyInput(key, scancode, action, mods);
}

void Renderer::MouseCallback(double xpos, double ypos) {
	// std::cout << "Mouse callback " << xpos << " " << ypos << std::endl;
	inputHandler->HandleMouseInput(xpos, ypos);

	float xOffset = inputHandler->GetMouseOffsetX();
	float yOffset = inputHandler->GetMouseOffsetY();
	float camSpeed = 10.0f * *dt;

	if (xOffset != 0.0f) {
		camera.UpdateYaw(xOffset * camSpeed);
	}
	if (yOffset != 0.0f) {
		camera.UpdatePitch(yOffset * -camSpeed);
	}
}
