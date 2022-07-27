#include "GSSettings.h"
#include "Player.h"

extern int character;
extern bool button_update;


GSSettings::GSSettings()
{

}


GSSettings::~GSSettings()
{
}



void GSSettings::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");

	// return main menu button
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_backButton = std::make_shared<GameButton>(model, shader, texture);
	m_backButton->Set2DPosition(25, 25);
	m_backButton->SetSize(50, 50);
	m_backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(m_backButton);

	// button for character and difficulty options
	// character options
	m_charaButton1 = std::make_shared<GameButton>(model, shader, texture);
	m_charaButton1->Set2DPosition((float)Globals::screenWidth / 2 - 50, 400);
	m_charaButton1->SetSize(50, 50);
	m_charaButton1->SetOnClick([]() {
		character = 1;
		button_update = true;
	});
	m_listButton.push_back(m_charaButton1);

	m_charaButton2 = std::make_shared<GameButton>(model, shader, texture);
	m_charaButton2->Set2DPosition((float)Globals::screenWidth / 2 + 50, 400);
	m_charaButton2->SetSize(50, 50);
	m_charaButton2->SetOnClick([]() {
		character = 2;
		button_update = true;
	});
	m_listButton.push_back(m_charaButton2);

	//"SETTINGS" text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd.ttf");
	m_Text_settings = std::make_shared< Text>(shader, font, "SETTINGS", TextColor::RED, 1.0);
	m_Text_settings->Set2DPosition((float)Globals::screenWidth / 2 - 50, 120);

	// Other texts
	font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	auto sometext = std::make_shared< Text>(shader, font, "Select character", TextColor::BLUE, 1.0);
	sometext->Set2DPosition((float)Globals::screenWidth / 2 - 80, 200);
	m_listText.push_back(sometext);

	// Character animations
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("larva_actor.tga");
	auto chara = std::make_shared<Player>(model, shader, texture, 9, 1, 0, 0.1f);
	chara->Set2DPosition((float)Globals::screenWidth / 2 - 50, 300);
	chara->SetSize(50, 100);
	m_listAnimation.push_back(chara);

	texture = ResourceManagers::GetInstance()->GetTexture("larva_actor2.tga");
	chara = std::make_shared<Player>(model, shader, texture, 9, 1, 0, 0.1f);
	chara->Set2DPosition((float)Globals::screenWidth / 2 + 50, 300);
	chara->SetSize(50, 100);
	m_listAnimation.push_back(chara);

	// Set up button textures
	UpdateButtons();
}

void GSSettings::Exit()
{
}


void GSSettings::Pause()
{

}

void GSSettings::Resume()
{

}


void GSSettings::HandleEvents()
{

}

void GSSettings::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed == 1) {
		switch (key) {
		case KEY_BACK: GameStateMachine::GetInstance()->PopState();
			break;
		default:
			break;
		}

	}
}

void GSSettings::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSSettings::HandleMouseMoveEvents(float x, float y)
{
}

void GSSettings::Update(float deltaTime)
{
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}

	if (button_update) {
		UpdateButtons();
	}
}

void GSSettings::Draw()
{
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_settings->Draw();

	for (auto it : m_listText)
	{
		it->Draw();
	}
	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
}

void GSSettings::UpdateButtons() {
	auto newTexture = ResourceManagers::GetInstance()->GetTexture("button_unselected.tga");
	for (auto it : m_listButton)
	{
		it->SetTexture(newTexture);
	}
	newTexture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	m_backButton->SetTexture(newTexture);
	newTexture = ResourceManagers::GetInstance()->GetTexture("btn_ok.tga");
	
	switch (character) {
	case 1: m_charaButton1->SetTexture(newTexture); break;
	case 2: m_charaButton2->SetTexture(newTexture); break;
	default: break;
	}
	
	button_update = false;
}
