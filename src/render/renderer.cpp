#include "renderer.h"

Renderer::Renderer() {
	window = nullptr;
	inputHandler = nullptr;
	player = nullptr;
	dt = nullptr;
	lastFrameTime = nullptr;
	viewportW = 1920;
	viewportH = 1080;
}

void Renderer::Init(InputHandler* inputHandlerPointer, Player* playerPointer, float* dtPointer, float* lastFrameTimePointer) {
	std::cout << "Initializing renderer" << std::endl;

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
	player = playerPointer;
	dt = dtPointer;
	lastFrameTime = lastFrameTimePointer;

	gladLoadGL();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// VSync
	// glfwSwapInterval(0);

	glEnable(GL_DEPTH_TEST);

	std::vector<float> verticies = {
		// Bottom
		-0.5f,  -0.5f,	-0.5f,       1.0f,   1.0f,       0.0f,  -1.0f,   0.0f,
		-0.5f,  -0.5f,	 0.5f,       1.0f,   0.0f,       0.0f,  -1.0f,   0.0f,
		 0.5f,  -0.5f,	 0.5f,       0.0f,   0.0f,       0.0f,  -1.0f,   0.0f,
		 0.5f,  -0.5f,	-0.5f,       1.0f,   0.0f,       0.0f,  -1.0f,   0.0f,

		// Top
		-0.5f,   0.5f,	-0.5f,       1.0f,   1.0f,       0.0f,   1.0f,   0.0f,
		-0.5f,   0.5f,	 0.5f,       1.0f,   0.0f,       0.0f,   1.0f,   0.0f,
		 0.5f,   0.5f,	 0.5f,       0.0f,   0.0f,       0.0f,   1.0f,   0.0f,
		 0.5f,   0.5f,	-0.5f,       1.0f,   0.0f,       0.0f,   1.0f,   0.0f,

		// Left side
		-0.5f,  -0.5f,	-0.5f,       1.0f,   1.0f,      -1.0f,   0.0f,   0.0f,
		-0.5f,   0.5f,	-0.5f,       1.0f,   0.0f,      -1.0f,   0.0f,   0.0f,
		-0.5f,   0.5f,	 0.5f,       0.0f,   0.0f,      -1.0f,   0.0f,   0.0f,
		-0.5f,  -0.5f,	 0.5f,       1.0f,   0.0f,      -1.0f,   0.0f,   0.0f,

		// Right side
		 0.5f,  -0.5f,	 0.5f,       1.0f,   1.0f,       1.0f,   0.0f,   0.0f,
		 0.5f,   0.5f,	 0.5f,       1.0f,   0.0f,       1.0f,   0.0f,   0.0f,
		 0.5f,   0.5f,	-0.5f,       0.0f,   0.0f,       1.0f,   0.0f,   0.0f,
		 0.5f,  -0.5f,	-0.5f,       1.0f,   0.0f,       1.0f,   0.0f,   0.0f,

		// Back side
		 0.5f,  -0.5f,	-0.5f,       1.0f,   1.0f,       0.0f,   0.0f,  -1.0f,
		 0.5f,   0.5f,	-0.5f,       1.0f,   0.0f,       0.0f,   0.0f,  -1.0f,
		-0.5f,   0.5f,	-0.5f,       0.0f,   0.0f,       0.0f,   0.0f,  -1.0f,
		-0.5f,  -0.5f,	-0.5f,       1.0f,   0.0f,       0.0f,   0.0f,  -1.0f,

		// Front side
		-0.5f,  -0.5f,	 0.5f,       1.0f,   1.0f,       0.0f,   0.0f,   1.0f,
		-0.5f,   0.5f,	 0.5f,       1.0f,   0.0f,       0.0f,   0.0f,   1.0f,
		 0.5f,   0.5f,	 0.5f,       0.0f,   0.0f,       0.0f,   0.0f,   1.0f,
		 0.5f,  -0.5f,	 0.5f,       1.0f,   0.0f,       0.0f,   0.0f,   1.0f,
	};

	std::vector<unsigned int> indicies = {
		// Bottom
		0, 1, 2,
		0, 2, 3,

		// Top
		4, 5, 6,
		4, 6, 7,

		// Left
		8, 9, 10,
		8, 10, 11,

		// Right
		12, 13, 14,
		12, 14, 15,

		// Back
		16, 17, 18,
		16, 18, 19,

		// Front
		20, 21, 22,
		20, 22, 23,
	};

	skyVertexArray.Init();
	skyVertexArray.Bind();
	skyVertexArray.SendVerticies(&verticies[0], (int)verticies.size() * sizeof(float));
	skyVertexArray.SendIndicies(&indicies[0], (int)indicies.size() * sizeof(unsigned int));
	skyVertexArray.Unbind();

	basicTexture.Init("texture/basic.jpg");
	skyTexture.Init("texture/sky.jpg");

	basicShader.Init("shader/basic.vert", "shader/basic.frag");
	skyShader.Init("shader/sky.vert", "shader/sky.frag");
}

void Renderer::PrepareMesh() {
	basicTexture.Bind();
	basicShader.Bind();

	glm::mat4 view = camera.GenViewMat();

	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), (float)viewportW / (float)viewportH, 0.1f, 100.0f);

	basicShader.SetMat4("view", glm::value_ptr(view));
	basicShader.SetMat4("proj", glm::value_ptr(proj));

	glm::vec3 lightPos = glm::vec3(sin(*lastFrameTime) * 1.0f, 1.0f, cos(*lastFrameTime) * 1.0f);

	basicShader.SetVec3("lightPos", glm::value_ptr(lightPos));
}

void Renderer::DrawChunk(Chunk* chunk) {
	if (chunk->IsLoaded() == false) {
		return;
	}

	VertexBuffer* buffer = chunk->GetChunkBuffer();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	model = glm::translate(model, glm::vec3(chunk->GetXCoord() * 16, 0.0, chunk->GetZCoord() * 16));

	basicShader.SetMat4("model", glm::value_ptr(model));

	buffer->Bind();
	buffer->Draw();
}

void Renderer::DrawSky() {
	skyVertexArray.Bind();
	skyTexture.Bind();
	skyShader.Bind();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(80.0f, 80.0f, 80.0f));
	
	camera.SetCameraFromPlayerData(player);
	glm::mat4 view = camera.GenViewMat();
	view = glm::translate(view, camera.GetPos());

	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), (float)viewportW / (float)viewportH, 0.1f, 100.0f);

	skyShader.SetMat4("model", glm::value_ptr(model));
	skyShader.SetMat4("view", glm::value_ptr(view));
	skyShader.SetMat4("proj", glm::value_ptr(proj));

	skyVertexArray.Draw();
}

void Renderer::BeginFrame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float camSpeed = 0.5f * *dt;
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
	float camSpeed = 0.05f;

	if (xOffset != 0.0f) {
		player->UpdateLookDir(xOffset * camSpeed);
	}
	if (yOffset != 0.0f) {
		player->UpdatePitch(yOffset * -camSpeed);
	}
}
