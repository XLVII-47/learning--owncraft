#include "Game.h"
#include <glew.h>
#include "Mesh.h"
#include "Camera.h"
#include "Databases/DB_Blocks.h"

#include <gtx/transform.hpp>
#include <gtc/matrix_transform.hpp>

Game::Game()
	:mWindow(nullptr)
	, mIsRunning(true)
{

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Set OpenGL attributes
	// Use the core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Specify version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_ShowCursor(SDL_DISABLE);
	
	mWindow = SDL_CreateWindow("HazalEngine", 0, 0,
		1200, 600, SDL_WINDOW_OPENGL);
	
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// Create an OpenGL context
	mContext = SDL_GL_CreateContext(mWindow);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	// On some platforms, GLEW will emit a benign error code,
	// so clear it
	glGetError();

	glEnable(GL_DEPTH_TEST);
	DB_Blocks::Start();


	LoadData();
	
	return true;
}


void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
		
	}
}
int lastX, lastY;
bool firstMouse = true;

void Game::ProcessInput()
{	


	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	
	SDL_Event event;
	
	
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	
	//camera->ProcessKeyboard(keyState, (SDL_GetTicks() - mTicksCount) / 100.f);
	int xpos, ypos;
	
	SDL_GetMouseState(&xpos, &ypos);


		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	
	player->input(keyState, xoffset, yoffset);

	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		
		case SDL_MOUSEBUTTONDOWN:

			
		//	lines.push_back(new DrawLine(camera->getPosition(), (camera->getPosition() + camera->front * 10.f)));
		////	/*glm::vec4 ray_clip = glm::vec4(0., 0., -1.0, 1.0);
		////	glm::vec4 ray_eye = glm::inverse(glm::perspective(glm::radians(90.0f), (float)1200 / (float)600, 0.1f, 1500.0f))*ray_clip;
		////	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
		////	glm::vec3 ray_wor = (glm::inverse(camera->GetViewMatrix()) * ray_eye);
		////	ray_wor = glm::normalize(ray_wor);
		//*/
			for (float i = 1; i < 10; i+=0.05) {
				glm::vec3 ray = player->position + player->front();
				
				if(world->chunkUpdate(ray))break;
			}
		break;
		}
		
	}
	
}


void Game::LoadData() {
	world = new World();
	camera = new Camera();
	player = new Player(*camera);
		
	shader = new Shader("./Shaders/vscube.glsl", "./Shaders/fscube.glsl");
	crossShader = new Shader("./Shaders/vscross.glsl", "./Shaders/fscross.glsl");
	cubeShader = new Shader("./Shaders/vssimple.glsl", "./Shaders/fssimple.glsl");
	cross = new Crosshair();
	cube = new Cube();
	
}

void Game::UpdateGame()
{	
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	std::cout << 1.0 / deltaTime << std::endl;
	mTicksCount = SDL_GetTicks();
	
	player->doCollisionTest(*world, deltaTime);
	player->update(deltaTime);
}



void Game::GenerateOutput()
{
	// Set the clear color to grey
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );

	shader->use();
	glm::mat4 proj = camera->getProjMatrix();
	glm::mat4 cam = camera->getViewMatrix();
	shader->setmat4("projection", &proj);
	shader->setmat4("view", &cam);
	glm::mat4 transform(1.f);
	//transform = glm::translate(transform, mesh->transform);
	shader->setmat4("transform", &transform);

	for (auto itr = world->chunkList.begin(); itr != world->chunkList.end(); ++itr) {
		itr->second->ChunkMesh->Draw();
		//printf("%f %f %f\n", itr->second->position.x, itr->second->position.y, itr->second->position.z);
	}
	for (auto itr : lines) {
		itr->Draw();
		//printf("%f %f %f\n", itr->second->position.x, itr->second->position.y, itr->second->position.z);
	}
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
	cubeShader->use();
	cubeShader->setmat4("projection", &proj);
	cubeShader->setmat4("view", &cam);
	transform = glm::translate(transform, player->position);
	cubeShader->setmat4("transform",&transform);
	cube->Draw();


	
	
	
	

	crossShader->use();
	cross->Draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	SDL_GL_SwapWindow(mWindow);
}


void Game::Shutdown()
{
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}