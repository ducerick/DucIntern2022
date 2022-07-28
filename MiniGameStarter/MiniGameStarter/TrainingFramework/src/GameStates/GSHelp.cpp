#include "GSHelp.h"
#include "Collision.h"


extern float screenWidth ; //need get on Graphic engine
extern float screenHeight ; //need get on Graphic engine



GSHelp::GSHelp() : GameStateBase(StateType::STATE_CREDIT)
{

}


GSHelp::~GSHelp()
{
}



void GSHelp::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// return main menu button
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	m_backButton = std::make_shared<GameButton>(model, shader, texture);
	m_backButton->Set2DPosition(25, 25);
	m_backButton->SetSize(50, 50);
	m_backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});

	// "GAME HELP" text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("BigSpace.ttf");
	m_Text_Help = std::make_shared< Text>(shader, font, "HELP", TextColor::RED, 2.0);
	m_Text_Help->Set2DPosition(Vector2(screenWidth / 2 - 50, 100));
	m_listText.push_back(m_Text_Help);

	// Brick sprite 2D
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("brick1_a.tga");
	m_brick = std::make_shared<Sprite2D>(model, shader, texture);
	m_brick->SetSize(90, 30);
	m_brick->Set2DPosition(60, 200);

	// Brick guide text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	m_Text_Brick = std::make_shared< Text>(shader, font, "Do not touch these \"magnets\", ", TextColor::BLUE, 1.0);
	m_Text_Brick->Set2DPosition(150, 200);
	m_listText.push_back(m_Text_Brick);
	m_Text_Brick = std::make_shared< Text>(shader, font, "you will be attracted to them.", TextColor::BLUE, 1.0);
	m_Text_Brick->Set2DPosition(150, 225);
	m_listText.push_back(m_Text_Brick);

	// Food sprite 2D
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("obj5_animation.tga");
	m_candy = std::make_shared<Sprite2D>(model, shader, texture);
	m_candy->Set2DPosition(30, 275);
	m_candy->SetSize(30, 40);
	m_listFood.push_back(m_candy);
	texture = ResourceManagers::GetInstance()->GetTexture("obj3_animation.tga");
	m_sausage = std::make_shared<Sprite2D>(model, shader, texture);
	m_sausage->Set2DPosition(80, 275);
	m_sausage->SetSize(30, 40);
	m_listFood.push_back(m_sausage);
	texture = ResourceManagers::GetInstance()->GetTexture("obj4_animation.tga");
	m_apple = std::make_shared<Sprite2D>(model, shader, texture);
	m_apple->Set2DPosition(30, 325);
	m_apple->SetSize(30, 40);
	m_listFood.push_back(m_apple);
	texture = ResourceManagers::GetInstance()->GetTexture("obj6_animation.tga");
	m_pear = std::make_shared<Sprite2D>(model, shader, texture);
	m_pear->Set2DPosition(80, 325);
	m_pear->SetSize(30, 40);
	m_listFood.push_back(m_pear);

	// Food text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	m_Text_Food = std::make_shared< Text>(shader, font, "Eat them and you will get points.", TextColor::BLUE, 1.0);
	m_Text_Food->Set2DPosition(150, 310);
	m_listText.push_back(m_Text_Food);

	// Moster animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("obj1_animation.tga");
	m_monster1 = std::make_shared<Player>(model, shader, texture, 9, 1, 0, 0.1f);
	m_monster1->Set2DPosition(30, 400);
	m_monster1->SetSize(25, 35);
	m_listMonster.push_back(m_monster1);
	texture = ResourceManagers::GetInstance()->GetTexture("obj2_animation.tga");
	m_monster2 = std::make_shared<Player>(model, shader, texture, 9, 1, 0, 0.1f);
	m_monster2->Set2DPosition(80, 400);
	m_monster2->SetSize(25, 35);
	m_listMonster.push_back(m_monster2);

	// Monster text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	m_Text_Monster = std::make_shared< Text>(shader, font, "Stay away from them", TextColor::BLUE, 1.0);
	m_Text_Monster->Set2DPosition(150, 400);
	m_listText.push_back(m_Text_Monster);
	m_Text_Monster = std::make_shared< Text>(shader, font, "or you will die.", TextColor::BLUE, 1.0);
	m_Text_Monster->Set2DPosition(150, 425);
	m_listText.push_back(m_Text_Monster);

	// Text credit
	m_Text_Credit = std::make_shared< Text>(shader, font, "Credits", TextColor::RED, 2.0);
	m_Text_Credit->Set2DPosition(screenWidth / 2 - 80, 550);
	m_listText.push_back(m_Text_Credit);

	//Text name
	m_Text_Name = std::make_shared< Text>(shader, font, "Bui Minh Duc", TextColor::BLUE, 1.5);
	m_Text_Name->Set2DPosition(screenWidth / 3 , 600);
	m_listText.push_back(m_Text_Name);

	// Thank you
	m_Text_Thankyou = std::make_shared< Text>(shader, font, "Thanks GameLoft", TextColor::RED, 2.0);
	m_Text_Thankyou->Set2DPosition(screenWidth / 3 - 80, 700);
	m_listText.push_back(m_Text_Thankyou);

}

void GSHelp::Exit()
{
}


void GSHelp::Pause()
{

}

void GSHelp::Resume()
{

}


void GSHelp::HandleEvents()
{

}

void GSHelp::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSHelp::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	if (m_backButton->HandleTouchEvents(x, y, bIsPressed))
	{

	}
}

void GSHelp::HandleMouseMoveEvents(float x, float y)
{
}

void GSHelp::Update(float deltaTime)
{

	for (auto it : m_listMonster)
	{
		it->Update(deltaTime);
	}

}

void GSHelp::Draw()
{
	m_backButton->Draw();
	m_brick->Draw();

	for (auto it : m_listMonster) {
		it->Draw();
	}

	for (auto it : m_listFood) {
		it->Draw();
	}

	for (auto it : m_listText) {
		it->Draw();
	}
}