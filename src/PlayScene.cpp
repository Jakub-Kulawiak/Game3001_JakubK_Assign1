#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 100, 100, 100, 100);
}

void PlayScene::update()
{
	updateDisplayList();

	CollisionManager::AABBCheck(m_pTank, m_pTarget);
	CollisionManager::AABBCheck(m_pTank, m_pObstacle);
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";


	const SDL_Color green = { 0, 255, 50, 255 };
	m_pInstructions = new Label("To change AI behaviour use buttons in the Imgui menu.", "vgafix", 48, green, glm::vec2(400.0f, 40.0f));
	m_pInstructions->setParent(this);
	addChild(m_pInstructions);

	m_pInstructions2 = new Label("Enabling objects and other functions are also done through Imgui.", "vgafix", 48, green, glm::vec2(400.0f, 60.0f));
	m_pInstructions2->setParent(this);
	addChild(m_pInstructions2);
	
	m_pTarget = new Target();
	m_pTarget->setEnabled(false);
	m_pTarget->getTransform()->position = glm::vec2(700.0f, 300.0f);
	addChild(m_pTarget);
	
	m_pObstacle = new Obstacle();
	m_pObstacle->setEnabled(false);
	m_pObstacle->getTransform()->position = glm::vec2(500.0f, 300.0f);
	addChild(m_pObstacle);

	m_pTank = new Tank();
	m_pTank->getTransform()->position = glm::vec2(100.0f, 300.0f);
	m_pTank->setEnabled(false);
	m_pTank->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pTank);

	/*
	// instantiating spaceship
	m_pSpaceShip = new SpaceShip();
	m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, 300.0f);
	m_pSpaceShip->setEnabled(false);
	m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pSpaceShip);
	*/
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME3001 - Assignment 1", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static float speed = 10.0f;
	if(ImGui::SliderFloat("MaxSpeed", &speed, 0.0f, 100.0f))
	{
		m_pTank->setMaxSpeed(speed);
	}

	static float acceleration_rate = 2.0f;
	if(ImGui::SliderFloat("Acceleration Rate", &acceleration_rate, 0.0f, 50.0f))
	{
		m_pTank->setAccelerationRate(acceleration_rate);
	}

	static float angleInRadians = m_pTank->getRotation();
	if(ImGui::SliderAngle("Orientation Angle", &angleInRadians))
	{
		m_pTank->setRotation(angleInRadians * Util::Rad2Deg);
	}

	static float turn_rate = 5.0f;
	if(ImGui::SliderFloat("Turn Rate", &turn_rate, 0.0f, 20.0f))
	{
		m_pTank->setTurnRate(turn_rate);
	}
	
	if(ImGui::Button("Start"))
	{
		m_pTank->setEnabled(true);
	}

	ImGui::SameLine();
	
	if (ImGui::Button("Reset"))
	{
		m_pTank->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pTank->setEnabled(false);
		m_pTank->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pTank->setRotation(0.0f); // set Angle to 0 degrees
		turn_rate = 5.0f;
		acceleration_rate = 2.0f;
		speed = 10.0f;
		angleInRadians = m_pTank->getRotation();

		m_pObstacle->setEnabled(false);
		m_pTarget->setEnabled(false);
	}
	
	ImGui::SameLine();
	
	if(ImGui::Button("Seek"))
	{
		m_pTank->setState(0);
	}
	
	ImGui::SameLine();
	
	if(ImGui::Button("Flee"))
	{
		m_pTank->setState(1);
	}

	if(ImGui::Button("Target"))
	{
		m_pTarget->setEnabled(true);
	}

	ImGui::SameLine();

	if(ImGui::Button("Obstacle"))
	{
		m_pObstacle->setEnabled(true);
	}
	
	ImGui::SameLine();

	if(ImGui::Button("Instructions"))
	{
		m_pInstructions->setEnabled(false);
		m_pInstructions2->setEnabled(false);
	}
	
	ImGui::Separator();

	static float targetPosition[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("Target", targetPosition, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(targetPosition[0], targetPosition[1]);
		m_pTank->setDestination(m_pTarget->getTransform()->position);
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
