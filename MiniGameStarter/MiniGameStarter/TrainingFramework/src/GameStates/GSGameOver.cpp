#include "GSGameOver.h"
#include "Collision.h"


float screenWidth = 480; //need get on Graphic engine
float screenHeight = 800; //need get on Graphic engine

GSGameOver::GSGameOver() : GameStateBase(StateType::STATE_OVER)
{

}


GSGameOver::~GSGameOver()
{
}



void GSGameOver::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("larva.tga");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//restart
	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth/2, screenHeight/2);
	button->SetSize(80, 80);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
	});
	m_listButton.push_back(button);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		ResourceManagers::GetInstance()->StopSound("larva_song.wav");

	});

	m_listButton.push_back(button);

	// "GAME OVER" text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_Text_GameOver = std::make_shared< Text>(shader, font, "GAME OVER", TextColor::RED, 2.0);
	m_Text_GameOver->Set2DPosition(Vector2(screenWidth / 2 - 125, 50));

	// Show score
	std::string finalscore = std::to_string(Collision::GetInstance()->GetScore());

	m_Text_Score = std::make_shared< Text>(shader, font, "YOUR SCORE: " + finalscore, TextColor::BLUE, 2.0);
	m_Text_Score->Set2DPosition(Vector2(screenWidth / 2 - 150, 250));

	Collision::GetInstance()->SetScore(0);
}

void GSGameOver::Exit()
{
}


void GSGameOver::Pause()
{

}

void GSGameOver::Resume()
{

}


void GSGameOver::HandleEvents()
{

}

void GSGameOver::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSGameOver::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSGameOver::HandleMouseMoveEvents(float x, float y)
{ 
}

void GSGameOver::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSGameOver::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_GameOver->Draw();
	m_Text_Score->Draw();
}