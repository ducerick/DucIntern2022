#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"
#include "Obstacle.h"
#define speed 60.0f
static float delta_x;
static Vector2 lastTouchEvents;




GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_new_7.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// background
	m_background2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_background2->Set2DPosition((float)Globals::screenWidth / 2, -(float)Globals::screenHeight / 2);
	m_background2->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
			GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("larva_actor.tga");
	m_larva = std::make_shared<Player>(model, shader, texture, 9, 1, 0, 0.1f);
	
	m_larva->Set2DPosition(0, (float)Globals::screenHeight);
	m_larva->SetSize(30, 100);
	m_listAnimation.push_back(m_larva);
	m_KeyPress = 0;
	
	//Obstacle
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("tmp.tga");
	float n = -25;
	for (int i = 0; i < 21; i++) {
		std::shared_ptr<Obstacle> m_obstacleLeft = std::make_shared<Obstacle>(model, shader, texture, BRICK);
		std::shared_ptr<Obstacle> m_obstacleRight = std::make_shared<Obstacle>(model, shader, texture, BRICK);
		m_obstacleLeft->Set2DPosition(m_obstacleLeft->GetScale().x / 2, n);
		m_obstacleRight->Set2DPosition((float)Globals::screenWidth - m_obstacleRight->GetScale().x / 2, n);
		n += -50;
		m_listObstacleLeft.push_back(m_obstacleLeft);
		m_listObstacleRight.push_back(m_obstacleRight);
	}


}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress |= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress |= 1<<1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress |= 1<<2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress |= 1<<3;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress ^= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress ^= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}

	if (m_larva->HandleTouchEvents(x, y, bIsPressed, m_larva)) {
		lastTouchEvents = Vector2(x, y);
		m_mousePress = true;
		m_intro = false;
	}

	if (bIsPressed == false) m_mousePress = false;
}

void GSPlay::HandleMouseMoveEvents(float x, float y)
{
	if (m_mousePress == true) {
		float d_x = x - lastTouchEvents.x;
		float d_y = y - lastTouchEvents.y;
		float m_x = m_larva->Get2DPosition(m_larva).x + d_x;
		float m_y = m_larva->Get2DPosition(m_larva).y + d_y;
		m_larva->Set2DPosition(m_x, m_y);
		lastTouchEvents = Vector2(x, y);
	}
}

void GSPlay::Update(float deltaTime)
{
	float h = (float)Globals::screenHeight;
	float w = (float)Globals::screenWidth;
	if (m_intro == true) {
		Vector2 m_intro = m_larva->Get2DPosition(m_larva);
		if (m_intro.x <= w && m_intro.y <= h && delta_x != -1) {
			delta_x = m_intro.x;
			m_intro.x += speed * deltaTime;
			m_intro.y = (2 * h) / (pow(w, 2)) * pow(m_intro.x, 2) - (2 * h / w) * m_intro.x + h;
			delta_x = m_intro.x - delta_x;
			m_larva->Set2DPosition(m_intro.x, m_intro.y);
		} 
		else if (m_intro.x >= w / 2) {
			delta_x = m_intro.x;
			m_intro.x -= speed * deltaTime;
			delta_x = m_intro.x - delta_x;
			m_larva->Set2DPosition(m_intro.x, m_intro.y );
		} 
		else if (m_intro.y >= h/2 ) {
			delta_x = -1;
			m_intro.y -= speed * deltaTime;
			m_larva->Set2DPosition(m_intro.x, m_intro.y);
		}
		m_larva->Update(deltaTime);
	}

	else {

		Vector2 bg_pos = m_background->Get2DPosition();
		bg_pos.y += speed * deltaTime;
		if (bg_pos.y > 3 * (float)Globals::screenHeight / 2) {
			bg_pos.y -= 2 * (float)Globals::screenHeight;
		}
		m_background->Set2DPosition(bg_pos.x, bg_pos.y);

		Vector2 bg_pos2 = m_background2->Get2DPosition();
		bg_pos2.y += speed * deltaTime;
		if (bg_pos2.y > 3 * (float)Globals::screenHeight / 2) {
			bg_pos2.y -= 2 * (float)Globals::screenHeight;
		}
		m_background2->Set2DPosition(bg_pos2.x, bg_pos2.y);

		for (auto it : m_listObstacleLeft)
		{
			it->SetSpeed(it, speed, deltaTime);
		}

		for (auto it : m_listObstacleRight)
		{
			it->SetSpeed(it, speed, deltaTime);
		}

		switch (m_KeyPress)//Handle Key event
		{
		default:
			break;
		}
		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
		for (auto it : m_listAnimation)
		{
			it->Update(deltaTime);
		}
		for (auto it : m_listObstacleLeft)
		{
			it->Update(deltaTime);
		}
		for (auto it : m_listObstacleRight)
		{
			it->Update(deltaTime);
		}
		
	}

}

void GSPlay::Draw()
{
	m_background->Draw();
	m_background2->Draw();
	m_score->Draw();
	if (m_intro == true) {
		m_larva->Draw();
	}
	else {
		for (auto it : m_listButton)
		{
			it->Draw();
		}

		for (auto it : m_listAnimation)
		{
			it->Draw();
		}
		for (auto it : m_listObstacleLeft)
		{
			it->Draw();
		}
		for (auto it : m_listObstacleRight)
		{
			it->Draw();
		}
	}
}