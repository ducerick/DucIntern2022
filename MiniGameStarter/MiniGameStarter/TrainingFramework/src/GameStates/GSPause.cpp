#include "GSPause.h"
#include "Collision.h"


extern float screenWidth; //need get on Graphic engine
extern float screenHeight; //need get on Graphic engine

GSPause::GSPause() : GameStateBase(StateType::STATE_PAUSE)
{

}


GSPause::~GSPause()
{
}



void GSPause::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");

	// btn continue
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 - 25, screenHeight / 2);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});

	m_listButton.push_back(button);

	//go back to main menu
	texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 25, screenHeight / 2);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		Collision::GetInstance()->SetScore(0);
	});
	m_listButton.push_back(button);

	// Show score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	std::string finalscore = std::to_string(Collision::GetInstance()->GetScore());

	m_Text_Score = std::make_shared< Text>(shader, font, "YOUR SCORE: " + finalscore, TextColor::BLUE, 2.0);
	m_Text_Score->Set2DPosition(Vector2(screenWidth / 2 - 150, 250));
}

void GSPause::Exit()
{
}


void GSPause::Pause()
{

}

void GSPause::Resume()
{

}


void GSPause::HandleEvents()
{

}

void GSPause::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPause::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPause::HandleMouseMoveEvents(float x, float y)
{
}

void GSPause::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPause::Draw()
{
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_Score->Draw();
}