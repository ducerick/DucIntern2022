#include "GSGameOver.h"
#include "Collision.h"


float screenWidth = 480; //need get on Graphic engine
float screenHeight = 800; //need get on Graphic engine
extern int character;


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
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// Character animations
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("larva_actor_dead.tga");
	if (character == 2) texture = ResourceManagers::GetInstance()->GetTexture("larva_actor2_dead.tga");
	m_Animation = std::make_shared<Player>(model, shader, texture, 9, 1, 0, 0.1f);
	m_Animation->Set2DPosition((float)Globals::screenWidth / 2 , screenHeight / 2 + 100);
	m_Animation->SetSize(50, 100);


	//restart
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
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

	// Sound
	std::string larva_eat = "larva_dead.mp3";
	ResourceManagers::GetInstance()->PlaySound(larva_eat);

	// "GAME OVER" text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_Text_GameOver = std::make_shared< Text>(shader, font, "GAME OVER", TextColor::RED, 2.0);
	m_Text_GameOver->Set2DPosition(Vector2(screenWidth / 2 - 125, 150));

	// Show score
	std::string finalscore = std::to_string(Collision::GetInstance()->GetScore());

	// Show highScore
	std::string highScore = std::to_string(Collision::GetInstance()->GetmaxScore());

	m_Text_Score = std::make_shared< Text>(shader, font, "YOUR SCORE: " + finalscore, TextColor::BLUE, 2.0);
	m_Text_Score->Set2DPosition(Vector2(screenWidth / 2 - 150, 250));

	m_Text_highScore = std::make_shared< Text>(shader, font, "HIGH SCORE: " + highScore, TextColor::GREEN, 2.0);
	m_Text_highScore->Set2DPosition(Vector2(screenWidth / 2 - 150, 350));

	//

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

	m_Animation->Update(deltaTime);

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

}

void GSGameOver::Draw()
{
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Animation->Draw();
	m_Text_GameOver->Draw();
	m_Text_Score->Draw();
	m_Text_highScore->Draw();
}