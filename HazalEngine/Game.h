#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Mesh.h"
#include "Camera.h"
#include "World.h"
#include "Crosshair/Crosshair.h"
#include "DrawLine.h"
#include "Cube.h"
#include "Player.h"
class Game
{
public:
	Game();

	bool Initialize(void);
	// Runs the game loop until the game is over

	void RunLoop(void);
	// Shutdown the game
	void Shutdown(void);



private:

	void ProcessInput(void);

	void UpdateGame(void);

	void GenerateOutput(void);

	void LoadData();

	SDL_Window* mWindow;
	SDL_GLContext mContext;


	std::vector<Mesh*> meshes;
	std::vector<DrawLine*> lines;
	Camera *camera;
	World * world;
	Player *player;
	Cube *cube;

	Shader *cubeShader;
	Shader* shader;
	Shader* crossShader;
	Crosshair *cross;
	
	bool mIsRunning;
	Uint32 mTicksCount;
};
