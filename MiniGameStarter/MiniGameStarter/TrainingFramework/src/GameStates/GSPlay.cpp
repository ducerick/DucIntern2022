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
#include "Collision.h"

float speed = 60.0;
static float delta_x;
static Vector2 lastTouchEvents;
float mouse_x;
float mouse_y;
#define posLeft1 205 * 2 / 3 + 15
#define posRight1 -150 + 15
#define posLeft2 270 * 2 / 3 + 15
#define posRight2 -400 + 15
#define posLeft3 (float)Globals::screenWidth - 256 * 2 / 3 - 15
#define posRight3 -300 + 15
#define posLeft4 (float)Globals::screenWidth - 200 * 2 / 3 -15
#define posRight4 -600 + 15
#define postRight5 -100 + 15
#define postRight6 -350 + 15
#define posLeft5 (float)Globals::screenWidth - 205 * 2 / 3 - 15
#define postRight7 -550 + 15
#define postRight8 -750 + 15

extern int character;

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_new_8.tga");

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
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
			ResourceManagers::GetInstance()->StopSound("larva_song.wav");
			Collision::GetInstance()->SetScore(0);
			speed = 60;
		});
	m_listButton.push_back(button);

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 100, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PAUSE);
	});
	m_listButton.push_back(button);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 0", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("larva_actor.tga");
	if (character == 2) texture = ResourceManagers::GetInstance()->GetTexture("larva_actor2.tga");
	m_larva = std::make_shared<Player>(model, shader, texture, 9, 1, 0, 0.1f);
	
	m_larva->Set2DPosition(0, (float)Globals::screenHeight);
	m_larva->SetSize(30, 70);
	m_listAnimation.push_back(m_larva);
	m_KeyPress = 0;
	
	//Obstacle BRICK
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

	Level(0);

	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	// Food Left
	texture = ResourceManagers::GetInstance()->GetTexture("obj3_animation.tga");
	std::shared_ptr<Player> m_sausage = std::make_shared<Player>(model, shader, texture, 1, 1, 0, 0.1f);
	texture = ResourceManagers::GetInstance()->GetTexture("obj6_animation.tga");
	std::shared_ptr<Player> m_pear = std::make_shared<Player>(model, shader, texture, 1, 1, 0, 0.1f);
	m_sausage->Set2DPosition(posLeft1, postRight5);
	m_sausage->SetSize(30, 40);
	m_pear->Set2DPosition(posLeft2, postRight6);
	m_pear->SetSize(30, 40);
	m_listFoodLeft.push_back(m_sausage);
	m_listFoodLeft.push_back(m_pear);

	//Food Right
	texture = ResourceManagers::GetInstance()->GetTexture("obj5_animation.tga");
	std::shared_ptr<Player> m_candy = std::make_shared<Player>(model, shader, texture, 1, 1, 0, 0.1f);
	texture = ResourceManagers::GetInstance()->GetTexture("obj4_animation.tga");
	std::shared_ptr<Player> m_apple = std::make_shared<Player>(model, shader, texture, 1, 1, 0, 0.1f);
	m_candy->Set2DPosition(posLeft3, postRight7);
	m_candy->SetSize(30, 40);
	m_apple->Set2DPosition(posLeft5, postRight8);
	m_apple->SetSize(30, 40);
	m_listFoodRight.push_back(m_candy);
	m_listFoodRight.push_back(m_apple);
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
	mouse_x = x;
	mouse_y = y;
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
			m_larva->Set2DPosition(m_intro.x, m_intro.y);
		}
		else if (m_intro.y >= h / 2) {
			delta_x = -1;
			m_intro.y -= speed * deltaTime;
			m_larva->Set2DPosition(m_intro.x, m_intro.y);
		}
		m_larva->Update(deltaTime);
	}

	else {

		if (m_larva->Get2DPosition(m_larva).x > 480 || m_larva->Get2DPosition(m_larva).y > 800) {
			GameOver();
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OVER);
		}

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

		for (auto it : m_listMonsterLeft) {
			it->SetSpeed(it, speed, deltaTime);
			if (Collision::GetInstance()->CheckCollision(it, m_larva)) {
				GameOver();
				GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OVER);
			}
		}

		for (auto it : m_listMonsterRight) {
			it->SetSpeed(it, speed, deltaTime);
			if (Collision::GetInstance()->CheckCollision(it, m_larva)) {
				GameOver();
				GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OVER);
			}
		}

		for (auto it : m_listFoodLeft) {
			it->SetSpeed(it, speed, deltaTime);
			if (Collision::GetInstance()->CheckCollision(it, m_larva)) {
				score++;
				m_score->SetText("Score: " + std::to_string(score));
				it->SetSize(0, 0);
				Collision::GetInstance()->SetScore(score);
			}
		}

		for (auto it : m_listFoodRight) {
			it->SetSpeed(it, speed, deltaTime);
			if (Collision::GetInstance()->CheckCollision(it, m_larva)) {
				score++;
				m_score->SetText("Score: " + std::to_string(score));
				it->SetSize(0, 0);
				Collision::GetInstance()->SetScore(score);
			}
		}

		for (auto it : m_listObstacleLeft)
		{

			it->SetSpeed(it, speed, deltaTime);

			if (Collision::GetInstance()->CheckCollision(it, m_larva)) {
				m_mousePress = false;
				Vector2 m_pos = m_larva->Get2DPosition(m_larva);
				Vector3 m_scale = m_larva->GetScale();
				if (m_pos.x >= it->GetScale().x) {
					m_larva->Set2DPosition(it->GetScale().x + m_scale.x / 2, m_pos.y);
				}
				else if (m_pos.x - m_scale.x / 2 <= it->GetScale().x && m_pos.y <= it->Get2DPosition().y) {
					m_larva->Set2DPosition(m_pos.x, it->Get2DPosition().y - m_scale.y / 2 - it->GetScale().y / 2);
				}
				else if (m_pos.x - m_scale.x / 2 <= it->GetScale().x && m_pos.y > it->Get2DPosition().y) {
					m_pos.y += speed * deltaTime;
					m_larva->Set2DPosition(m_pos.x, m_pos.y + 10);
				}
			}
		}

		for (auto it : m_listObstacleRight)
		{
			it->SetSpeed(it, speed, deltaTime);

			if (Collision::GetInstance()->CheckCollision(it, m_larva)) {
				m_mousePress = false;
				float delta = (float)Globals::screenWidth - it->GetScale().x;
				Vector2 m_pos = m_larva->Get2DPosition(m_larva);
				Vector3 m_scale = m_larva->GetScale();
				if (m_pos.x <= delta) {
					m_larva->Set2DPosition(delta - m_scale.x / 2, m_pos.y);
				}
				else if (m_pos.x + m_scale.x / 2 >= delta && m_pos.y <= it->Get2DPosition().y) {
					m_larva->Set2DPosition(m_pos.x, it->Get2DPosition().y - m_scale.y / 2 - it->GetScale().y / 2);
				}
				else if (m_pos.x + m_scale.x / 2 >= delta && m_pos.y > it->Get2DPosition().y) {
					m_pos.y += speed * deltaTime;
					m_larva->Set2DPosition(m_pos.x, m_pos.y + 10);
				}
			}
		}

		for (auto it : m_listMonsterLeft) {
			Vector2 pos = it->Get2DPosition(it);
			pos.x += speed * deltaTime;
			if (pos.x > 480) {
				pos.x -= (float)Globals::screenWidth;
			}
			it->Set2DPosition(pos.x, pos.y);
		}

		if (score == 5 && m_continue) {
			Level(15);
			speed += 10;
			m_continue = false;
		} 

		if (score == 10 && !m_continue) {
			Level(30);
			speed += 10;
			m_continue = true;
		}

		if (score == 15 && m_continue) {
			Level(-25);
			speed += 10;
			m_continue = false;
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
		for (auto it : m_listMonsterLeft)
		{
			it->Update(deltaTime);
		}
		for (auto it : m_listMonsterRight)
		{
			it->Update(deltaTime);
		}
		for (auto it : m_listFoodLeft)
		{
			it->Update(deltaTime);
		}
		for (auto it : m_listFoodRight)
		{
			it->Update(deltaTime);
		}
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_background2->Draw();
	if (m_intro == true) {
		m_larva->Draw();
	}
	else {

		for (auto it : m_listAnimation)
		{
			it->Draw();
		}
		for (auto it : m_listMonsterLeft)
		{
			it->Draw();
		}
		for (auto it : m_listMonsterRight)
		{
			it->Draw();
		}
		for (auto it : m_listFoodLeft)
		{
			it->Draw();
		}
		for (auto it : m_listFoodRight)
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
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_score->Draw();
}

void GSPlay::GameOver() {
	speed = 60;
	m_intro == true;
	m_larva->Set2DPosition(0, 800);
}

void GSPlay::Level(float x) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	// Monster Left
	auto texture = ResourceManagers::GetInstance()->GetTexture("obj1_animation.tga");
	std::shared_ptr<Player> m_monsterLeft1 = std::make_shared<Player>(model, shader, texture, 9, 1, 0, 0.1f);
	texture = ResourceManagers::GetInstance()->GetTexture("obj2_animation.tga");
	std::shared_ptr<Player> m_monsterLeft2 = std::make_shared<Player>(model, shader, texture, 9, 1, 0, 0.1f);
	m_monsterLeft1->Set2DPosition(posLeft1, posRight1 - x);
	m_monsterLeft1->SetSize(25, 35);
	m_monsterLeft2->Set2DPosition(posLeft2 , posRight2 + x);
	m_monsterLeft2->SetSize(25, 35);
	m_listMonsterLeft.push_back(m_monsterLeft1);
	m_listMonsterLeft.push_back(m_monsterLeft2);

	// Monster Right
	texture = ResourceManagers::GetInstance()->GetTexture("obj1_animation.tga");
	std::shared_ptr<Player> m_monsterRight1 = std::make_shared<Player>(model, shader, texture, 9, 1, 0, 0.1f);
	texture = ResourceManagers::GetInstance()->GetTexture("obj2_animation.tga");
	std::shared_ptr<Player> m_monsterRight2 = std::make_shared<Player>(model, shader, texture, 9, 1, 0, 0.1f);
	m_monsterRight1->Set2DPosition(posLeft3, posRight3 + x);
	m_monsterRight1->SetSize(25, 35);
	m_monsterRight2->Set2DPosition(posLeft4, posRight4 - x);
	m_monsterRight2->SetSize(25, 35);
	m_listMonsterRight.push_back(m_monsterRight1);
	m_listMonsterRight.push_back(m_monsterRight2);
	m_listMonsterRight.push_back(m_monsterRight2);

}

