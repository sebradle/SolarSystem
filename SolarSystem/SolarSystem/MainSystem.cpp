#include "MainSystem.h"

#include <Engine/Errors.h>
#include <iostream>



MainSystem::MainSystem() :
	mScreenWidth(1024),
	mScreenHeight(768),
	mTime(0.0f),
	mCurrentState(State::PLAY),
	mMaxFPS(60.0f),
	mPause(false)
{
}


MainSystem::~MainSystem()
{
	for (int i = 0; i < mPlanets.size(); i++) {
		delete mPlanets[i];
	}
}

void MainSystem::run() {
	initSystems();
	mainLoop();
}

void MainSystem::initSystems() {
	Engine::init();
	mWindow.create("Solar System", mScreenWidth, mScreenHeight, Engine::FULLSCREEN);
	initShaders();
	mBatch.init();
	initPlanets();
}

void MainSystem::initShaders() {
	mColorProgram.compileShaders("Shaders/vshader.glsl", "Shaders/fshader.glsl");
	mColorProgram.addAttribute("vertexPosition");
	mColorProgram.addAttribute("vertexUV");
	mColorProgram.addAttribute("vertexNormal");
	mColorProgram.linkShaders();
}


void MainSystem::initPlanets() {
	// Sun 2.0f * SWEET_SPOT
	static Engine::GLTexture sun = Engine::ResourceManager::getTexture("Textures/sun2.png");
	mPlanets.push_back(new Planet("Sun", 25.0f, 25.0f, 0.0f, SUN, sun.id));

	// Mercury 0.2f * SWEET_SPOT
	static Engine::GLTexture mercury = Engine::ResourceManager::getTexture("Textures/Planets/mercury.png");
	mPlanets.push_back(new Planet("Mercury", 58.6f, 87.97f, STEP, MERCURY, mercury.id));

	// Venus 0.40f * SWEET_SPOT
	static Engine::GLTexture venus = Engine::ResourceManager::getTexture("Textures/Planets/venus.png");
	mPlanets.push_back(new Planet("Venus", 243.0f, 224.7f, STEP * 2.0f, VENUS, venus.id));

	// Earth 0.44f * SWEET_SPOT
	static Engine::GLTexture earth = Engine::ResourceManager::getTexture("Textures/Planets/earth.png");
	mPlanets.push_back(new Planet("Earth", 1.0f, 365.0f, STEP * 2.5f, EARTH, earth.id));
		// Moon 0.20f * SWEET_SPOT
		static Engine::GLTexture moon = Engine::ResourceManager::getTexture("Textures/Moons/moon.png");
		mPlanets.back()->addMoon(365.0f, STEP * 2.5f, EARTH * 32.0f, 250.0f, 27.0f, MOON, moon.id);

	// Mars 0.37f * SWEET_SPOT
	static Engine::GLTexture mars = Engine::ResourceManager::getTexture("Textures/Planets/mars.png");
	mPlanets.push_back(new Planet("Mars", 1.03f, 686.98f, STEP * 4.0f, MARS, mars.id));

	// Jupiter 1.4f * SWEET_SPOT
	static Engine::GLTexture jupiter = Engine::ResourceManager::getTexture("Textures/Planets/jupiter.png");
	mPlanets.push_back(new Planet("Jupiter", 0.42f, 4332.82f, STEP * 13.0f, JUPITER, jupiter.id));
		//Io
		static Engine::GLTexture io = Engine::ResourceManager::getTexture("Textures/Moons/io.png");
		mPlanets.back()->addMoon(4332.82f, STEP * 13.0f, JUPITER * 4.0f, 40.779f, 27.0f, IO, io.id);
		//Europa
		static Engine::GLTexture europa = Engine::ResourceManager::getTexture("Textures/Moons/europa.png");
		mPlanets.back()->addMoon(4332.82f, STEP * 13.0f, JUPITER * 6.0f, 130.55f, 27.0f, EUROPA, europa.id);
		//Ganymede
		static Engine::GLTexture ganymede = Engine::ResourceManager::getTexture("Textures/Moons/ganymede.png");
		mPlanets.back()->addMoon(4332.82f, STEP * 13.0f, JUPITER * 10.0f, 270.1f, 27.0f, GANYMEDE, ganymede.id);
		//Callisto
		static Engine::GLTexture callisto = Engine::ResourceManager::getTexture("Textures/Moons/callisto.png");
		mPlanets.back()->addMoon(4332.82f, STEP * 13.0f, JUPITER * 18.0f, 460.689f, 27.0f, CALLISTO, callisto.id);

	// Saturn 1.15f * SWEET_SPOT
	static Engine::GLTexture saturn = Engine::ResourceManager::getTexture("Textures/Planets/saturn.png");
	mPlanets.push_back(new Planet("Saturn", 0.426f, 10755.7f, STEP * 24.0f, SATURN, saturn.id));
	// Saturn Ring
	static Engine::GLTexture saturnring = Engine::ResourceManager::getTexture("Textures/saturnring.png");
	mPlanets.back()->addRings(0.426f, 10755.7f, STEP * 24.0f, SATURN * 0.275, saturnring.id);
		//Tethys
		static Engine::GLTexture tethys = Engine::ResourceManager::getTexture("Textures/Moons/tethys.png");
		mPlanets.back()->addMoon(10755.7f, STEP * 24.0f, SATURN * 3.0f, 30.89f, 27.0f, TETHYS, tethys.id);
		//Dione
		static Engine::GLTexture dione = Engine::ResourceManager::getTexture("Textures/Moons/dione.png");
		mPlanets.back()->addMoon(10755.7f, STEP * 24.0f, SATURN * 3.77f, 50.74f, 27.0f, DIONE, dione.id);
		//Rhea
		static Engine::GLTexture rhea = Engine::ResourceManager::getTexture("Textures/Moons/rhea.png");
		mPlanets.back()->addMoon(10755.7f, STEP * 24.0f, SATURN * 5.27f, 80.52f, 27.0f, RHEA, rhea.id);
		//Titan
		static Engine::GLTexture titan = Engine::ResourceManager::getTexture("Textures/Moons/titan.png");
		mPlanets.back()->addMoon(10755.7f, STEP * 24.0f, SATURN * 12.21f, 250.9f, 27.0f, TITAN, titan.id);
		//Iapetus
		static Engine::GLTexture iapetus = Engine::ResourceManager::getTexture("Textures/Moons/iapetus.png");
		mPlanets.back()->addMoon(10755.7f, STEP * 24.0f, SATURN * 35.00f, 790.33f, 27.0f, IAPETUS, iapetus.id);
		

	// Uranus 0.80f * SWEET_SPOT
	static Engine::GLTexture uranus = Engine::ResourceManager::getTexture("Textures/Planets/uranus.png");
	mPlanets.push_back(new Planet("Uranus", 0.718f, 30687.15f, STEP * 49.0f, URANUS, uranus.id));
	//static Engine::GLTexture uranusring = Engine::ResourceManager::getTexture("Textures/uranusring.png");
	//mPlanets.back()->addRings(0.718f, 30687.15f, STEP * 49.0f * SWEET_SPOT, 1.075f * SWEET_SPOT, uranusring.id);
		//Ariel 
		static Engine::GLTexture ariel = Engine::ResourceManager::getTexture("Textures/Moons/ariel.png");
		mPlanets.back()->addMoon(30687.15f, STEP * 49.0f, URANUS * 4.0f, 50.5f, 27.0f, ARIEL, ariel.id);
		//Umbriel 
		static Engine::GLTexture umbriel = Engine::ResourceManager::getTexture("Textures/Moons/umbriel.png");
		mPlanets.back()->addMoon(30687.15f, STEP * 49.0f, URANUS * 5.0f, 60.1f, 27.0f, UMBRIEL, umbriel.id);
		//Titania 0.20f * SWEET_SPOT
		static Engine::GLTexture titania = Engine::ResourceManager::getTexture("Textures/Moons/titania.png");
		mPlanets.back()->addMoon(30687.15f, STEP * 49.0f, URANUS * 9.0f, 90.7f, 27.0f, TITANIA, titania.id);
		//Oberon 
		static Engine::GLTexture oberon = Engine::ResourceManager::getTexture("Textures/Moons/oberon.png");
		mPlanets.back()->addMoon(30687.15f, STEP * 49.0f, URANUS * 12.0f, 180.4f, 27.0f, OBERON, oberon.id);
		
		
	
	// Neptune  0.75f * SWEET_SPOT
	static Engine::GLTexture neptune = Engine::ResourceManager::getTexture("Textures/Planets/neptune.png");
	mPlanets.push_back(new Planet("Neptune", 0.68f, 60190.03f, STEP * 76.0f, NEPTUNE, neptune.id));
		//Triton  0.20f * SWEET_SPOT
		static Engine::GLTexture triton = Engine::ResourceManager::getTexture("Textures/Moons/triton.png");
		mPlanets.back()->addMoon(60190.03f, STEP * 76.0f, NEPTUNE * 7.0f, 100.3f, 27.0f, TRITON, triton.id);

	// Pluto
	static Engine::GLTexture pluto = Engine::ResourceManager::getTexture("Textures/Planets/pluto.png");
	mPlanets.push_back(new Planet("Pluto", 6.39f, 90553.0f, STEP * 100.0f, 0.17f * SWEET_SPOT, pluto.id));
		//Charon 0.20f * SWEET_SPOT
		static Engine::GLTexture charon = Engine::ResourceManager::getTexture("Textures/Moons/charon.png");
		mPlanets.back()->addMoon(90553.0, STEP * 100.0f, PLUTO * 8.0f, 60.3f, 27.0f, CHARON, charon.id);

	// Stars
	static Engine::GLTexture stars = Engine::ResourceManager::getTexture("Textures/stars.png");
	mPlanets.push_back(new Planet("Cosmos", 1000000.0f, 1000000.0f, 0.0f, STEP * 500.0f, stars.id));
}

void MainSystem::mainLoop() {
	while(mCurrentState != State::EXIT) {
		float start = SDL_GetTicks();

		processInput();
		mTime += 0.01;

		draw();
		fps();

		if (!mPause) {
			for (int i = 0; i < mPlanets.size(); i++) {
				mPlanets[i]->update();
			}
		}
		
		static int frameCount = 0;
		frameCount++;
		//if (frameCount % 10 == 0) std::cout << mFPS << std::endl;

		float frameTicks = SDL_GetTicks() - start;
		if (1000.0f / mMaxFPS > frameTicks) {
			SDL_Delay(1000.0f / mMaxFPS - frameTicks);
		}
	}
}

void MainSystem::processInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
			case SDL_QUIT:
				mCurrentState = State::EXIT;
				break;
			case SDL_MOUSEMOTION:
				mInputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
				break;
			case SDL_KEYDOWN:
				mInputManager.pressKey(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				mInputManager.releaseKey(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mInputManager.pressKey(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				mInputManager.releaseKey(evnt.button.button);
				break;
		}
	}

	if (mInputManager.isKeyPressed(SDLK_ESCAPE)) {
		mCurrentState = State::EXIT;
	}
	if (mInputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		mCamera.update(mInputManager.getMouseCoords());
	}
	if (mInputManager.isKeyPressed(SDLK_1)){
		mCamera.updatePos(glm::vec3(1.009f * mPlanets[1]->getOrbit() * sin(mPlanets[1]->getYr() - (29.6f / (2.0f * M_PI))), 
									0.1f, 
									1.009f * mPlanets[1]->getOrbit() * cos(mPlanets[1]->getYr() - (29.6f / (2.0f * M_PI)))));
	}
	if (mInputManager.isKeyPressed(SDLK_2)){
		mCamera.updatePos(glm::vec3(1.009f * mPlanets[2]->getOrbit() * sin(mPlanets[2]->getYr() - (29.6f / (2.0f * M_PI))), 
									0.1f, 
									1.009f * mPlanets[2]->getOrbit() * cos(mPlanets[2]->getYr() - (29.6f / (2.0f * M_PI)))));
	}
	if (mInputManager.isKeyPressed(SDLK_3)) {
		mCamera.updatePos(glm::vec3(1.009f * mPlanets[3]->getOrbit() * sin(mPlanets[3]->getYr() - (29.6f / (2.0f * M_PI))), 
									0.1f, 
									1.009f * mPlanets[3]->getOrbit() * cos(mPlanets[3]->getYr() - (29.6f / (2.0f * M_PI)))));
	}
	if (mInputManager.isKeyPressed(SDLK_m)) {
		mCamera.updatePos(glm::vec3((1.009f * mPlanets[3]->getOrbit() * sin(mPlanets[3]->getYr() - (29.6f / (2.0f * M_PI))))
									* (1.009f * mPlanets[3]->getMoons()->getDistance() * sin(mPlanets[3]->getMoons()->getMYr() - (29.6f / (2.0f * M_PI)))),
			0.1f,
			(1.009f * mPlanets[3]->getOrbit() * cos(mPlanets[3]->getYr() - (29.6f / (2.0f * M_PI))))
			* (1.009f * mPlanets[3]->getMoons()->getDistance() * cos(mPlanets[3]->getMoons()->getMYr() - (29.6f / (2.0f * M_PI))))));
	}
	if (mInputManager.isKeyPressed(SDLK_4)) {
		mCamera.updatePos(glm::vec3(1.009f * mPlanets[4]->getOrbit() * sin(mPlanets[4]->getYr() - (29.6f / (2.0f * M_PI))), 
									0.1f,
									1.009f * mPlanets[4]->getOrbit() * cos(mPlanets[4]->getYr() - (29.6f / (2.0f * M_PI)))));
	}
	if (mInputManager.isKeyPressed(SDLK_5)) {
		mCamera.updatePos(glm::vec3(1.009f * mPlanets[5]->getOrbit() * sin(mPlanets[5]->getYr() - (29.65f / (2.0f * M_PI))), 
									-1.8f,
									1.009f * mPlanets[5]->getOrbit() * cos(mPlanets[5]->getYr() - (29.65f / (2.0f * M_PI)))));
	}
	if (mInputManager.isKeyPressed(SDLK_6)) {
		mCamera.updatePos(glm::vec3(1.0075f * mPlanets[6]->getOrbit() * sin(mPlanets[6]->getYr() - (29.65f / (2.0f * M_PI))), 
									1.8f,
									1.0075f * mPlanets[6]->getOrbit() * cos(mPlanets[6]->getYr() - (29.65f / (2.0f * M_PI)))));
							}
	if (mInputManager.isKeyPressed(SDLK_7)) {
		mCamera.updatePos(glm::vec3(1.003f * mPlanets[7]->getOrbit() * sin(mPlanets[7]->getYr() - (29.6f / (2.0f * M_PI))), 
									0.1f,
									1.003f * mPlanets[7]->getOrbit() * cos(mPlanets[7]->getYr() - (29.6f / (2.0f * M_PI)))));
	}
	if (mInputManager.isKeyPressed(SDLK_8)) {
		mCamera.updatePos(glm::vec3(1.003f * mPlanets[8]->getOrbit() * sin(mPlanets[8]->getYr() - (29.6f / (2.0f * M_PI))), 
									0.1f,
									1.003f * mPlanets[8]->getOrbit() * cos(mPlanets[8]->getYr() - (29.6f / (2.0f * M_PI)))));
	}
	if (mInputManager.isKeyPressed(SDLK_9)) {
		mCamera.updatePos(glm::vec3(1.000125 * mPlanets[9]->getOrbit() * sin(mPlanets[9]->getYr() - (29.60845f / (2.0f * M_PI))), 
									0.1f,
									1.000125 * mPlanets[9]->getOrbit() * cos(mPlanets[9]->getYr() - (29.60845f / (2.0f * M_PI)))));
	}
	if (mInputManager.isKeyPressed(SDLK_w)) {
		mCamera.moveFoward();
	}
	if (mInputManager.isKeyPressed(SDLK_a)) {
		mCamera.strafeLeft();
	}
	if (mInputManager.isKeyPressed(SDLK_s)) {
		mCamera.moveBackward();
	}
	if (mInputManager.isKeyPressed(SDLK_d)) {
		mCamera.strafeRight();
	}
	if (mInputManager.isKeyPressed(SDLK_r)) {
		mCamera.moveUp();
	}
	if (mInputManager.isKeyPressed(SDLK_f)) {
		mCamera.moveDown();
	}
	if (mInputManager.isKeyPressed(SDLK_l)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (mInputManager.isKeyPressed(SDLK_o)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (mInputManager.isKeyPressed(SDLK_SPACE)) {
		mPause == true ? mPause = false : mPause = true;
	}
}

void MainSystem::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mColorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	
	GLint texLocation = mColorProgram.getUniformLocation("mySampler");
	glUniform1i(texLocation, 0);

	
	glm::mat4 proj = mCamera.getProjMatrix(mScreenWidth, mScreenHeight);
	glm::mat4 view = mCamera.getViewMatrix();

	GLint projID = mColorProgram.getUniformLocation("proj");
	glUniformMatrix4fv(projID, 1, GL_FALSE, &proj[0][0]);

	GLint viewID = mColorProgram.getUniformLocation("view");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);

	GLint modelID = mColorProgram.getUniformLocation("model");

	SetLight(glm::vec4(0.0, 10.0, 0.0, 1.0), glm::vec4(0.7, 0.7, 0.7, 1.0), glm::vec4(0.9, 0.9, 0.9, 1.0), glm::vec4(0.5, 0.5, 0.5, 1.0));
	SetMaterial(glm::vec4(0.9, 0.9, 0.5, 1.0), glm::vec4(0.9, 0.9, 0.5, 1.0), glm::vec4(0.9, 0.9, 0.0, 1.0), 0.5);
	glUniform1i(mColorProgram.getUniformLocation("light_out"), true);

	// draw sun
	mPlanets[0]->draw(mBatch, modelID);

	SetMaterial(glm::vec4(0.5, 0.2, 0.7, 1.0), glm::vec4(0.5, 0.2, 0.7, 1.0), glm::vec4(0.7, 0.2, 0.8, 1.0), 5.5);
	glUniform1i(mColorProgram.getUniformLocation("light_out"), false);

	for (int i = 1; i < mPlanets.size(); i++) {
		mPlanets[i]->draw(mBatch, modelID);
	}

	

	glBindTexture(GL_TEXTURE_2D, 0);
	mColorProgram.unuse();

	mWindow.swapBuffer();
}

void MainSystem::SetMaterial(glm::vec4 ka, glm::vec4 kd, glm::vec4 ks, float s)
{
	//glUniform4fv(mColorProgram.getUniformLocation("kAmbient"), 1, &ka[0]);
	//glUniform4fv(mColorProgram.getUniformLocation("kd"), 1, &kd[0]);
	//glUniform4fv(mColorProgram.getUniformLocation("ks"), 1, &ks[0]);
	glUniform1f(mColorProgram.getUniformLocation("Shininess"), s);
}

void MainSystem::SetLight(glm::vec4 lpos, glm::vec4 la, glm::vec4 ld, glm::vec4 ls)
{
	glUniform4fv(mColorProgram.getUniformLocation("LightPos"), 1, &lpos[0]);
	glUniform4fv(mColorProgram.getUniformLocation("Ambient"), 1, &la[0]);
	glUniform4fv(mColorProgram.getUniformLocation("Diffuse"), 1, &ld[0]);
	glUniform4fv(mColorProgram.getUniformLocation("Specular"), 1, &ls[0]);
}


void MainSystem::fps() {
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currFrame = 0;

	static float prevTicks = SDL_GetTicks();
	float currTicks;
	currTicks = SDL_GetTicks();

	mFrameTime = currTicks - prevTicks;
	frameTimes[currFrame % NUM_SAMPLES] = mFrameTime;
	prevTicks = currTicks;

	int count;
	currFrame++;

	if (currFrame < NUM_SAMPLES) {
		count = currFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	float frameAverage = 0;

	for (int i = 0; i < count; i++) {
		frameAverage += frameTimes[i];
	}

	frameAverage /= count;

	if (frameAverage > 0) {
		mFPS = 1000.0f / frameAverage;
	}
	else {
		mFPS = 60.0f;
	}
}