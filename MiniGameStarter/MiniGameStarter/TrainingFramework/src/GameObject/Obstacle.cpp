#include "Obstacle.h"
#include "Texture.h"
#include "ResourceManagers.h"


char* s[][9] = { "brick1_a", "brick1_b", "brick1_c" , "brick2_a" , "brick2_b" , "brick2_c" , "brick3_a" , "brick3_b" , "brick3_c" , "brick4_a"
, "brick4_b" , "brick4_c" , "brick5_a" , "brick5_b" , "brick5_c" , "brick6_a" , "brick6_b" , "brick7_a" , "brick7_b" , "brick7_c" };


Obstacle::Obstacle(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, ObstacleType type)
	: Sprite2D(model, shader, texture)
{
	std::shared_ptr<Texture> newTexture;
	switch (type)
	{
	case BRICK:
		{int tmp = rand() % 21;
		printf("tmp: %d\n", tmp);
		switch (tmp)
		{
		case 0:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick1_a.tga");
			SetSize(256 * 2 / 3, 50);
				break;
		case 1:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick1_b.tga");
			SetSize(205 * 2 / 3, 50);
			break;
		case 2:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick1_c.tga");
			SetSize(308 * 2 / 3, 50);
			break;
		case 3:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick2_a.tga");
			SetSize(256 * 2 / 3, 50);
			break;
		case 4:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick2_b.tga");
			SetSize(205 * 2 / 3, 50);
			break;
		case 5:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick2_c.tga");
			SetSize(308 * 2 / 3, 50);
			break;
		case 6:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick3_a.tga");
			SetSize(256 * 2 / 3, 50);
			break;
		case 7:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick3_b.tga");
			SetSize(308 * 2 / 3, 50);
			break;
		case 8:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick3_c.tga");
			SetSize(205 * 2 / 3, 50);
			break;
		case 9:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick4_a.tga");
			SetSize(256 * 2 / 3, 50);
			break;
		case 10:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick4_b.tga");
			SetSize(205 * 2 / 3, 50);
			break;
		case 11:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick4_c.tga");
			SetSize(308 * 2 / 3, 50);
			break;
		case 12:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick5_a.tga");
			SetSize(256 * 2 / 3, 50);
			break;
		case 13:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick5_b.tga");
			SetSize(205 * 2 / 3, 50);
			break;
		case 14:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick5_c.tga");
			SetSize(308 * 2 / 3, 50);
			break;
		case 15:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick6_a.tga");
			SetSize(205 * 2 / 3, 50);
			break;
		case 16:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick6_b.tga");
			SetSize(256 * 2 / 3, 50);
			break;
		case 17:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick6_c.tga");
			SetSize(308 * 2 / 3, 50);
			break;
		case 18:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick7_a.tga");
			SetSize(205 * 2 / 3, 50);
			break;
		case 19:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick7_b.tga");
			SetSize(256 * 2 / 3, 50);
			break;
		case 20:
			newTexture = ResourceManagers::GetInstance()->GetTexture("brick7_c.tga");
			SetSize(308 * 2 / 3, 50);
			break;
		default:
			break;
		}
		SetTexture(newTexture);
		SetType(BRICK);
		}
		break;
	case MONSTER1:
		newTexture = ResourceManagers::GetInstance()->GetTexture("obj1_animation.tga");
		SetSize(50, 50);
		SetTexture(newTexture);
		break;
	case MONSTER2:
		newTexture = ResourceManagers::GetInstance()->GetTexture("obj2_animation.tga");
		SetSize(50, 50);
		SetTexture(newTexture);
		break;
	case SAUSAGE:
		newTexture = ResourceManagers::GetInstance()->GetTexture("obj3_animation.tga");
		SetSize(50, 50);
		SetTexture(newTexture);
		break;
	case PEAR:
		newTexture = ResourceManagers::GetInstance()->GetTexture("obj4_animation.tga");
		SetSize(50, 50);
		SetTexture(newTexture);
		break;
	case CANDY:
		newTexture = ResourceManagers::GetInstance()->GetTexture("obj5_animation.tga");
		SetSize(50, 50);
		SetTexture(newTexture);
		break;
	case APPLE:
		newTexture = ResourceManagers::GetInstance()->GetTexture("obj6_animation.tga");
		SetSize(50, 50);
		SetTexture(newTexture);
		break;

	default:
		break;
	}

}

Obstacle::~Obstacle() {};

void Obstacle::SwitchType() {
	int newType;
	std::shared_ptr<Texture> resetTexture;
	newType = rand() % 21;
	printf("newType: %d\n", newType);
	switch (newType) {
	case 0:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick1_a.tga");
		SetSize(256 * 2 / 3, 50);
		break;
	case 1:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick1_b.tga");
		SetSize(205 * 2 / 3, 50);
		break;
	case 2:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick1_c.tga");
		SetSize(308 * 2 / 3, 50);
		break;
	case 3:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick2_a.tga");
		SetSize(256 * 2 / 3, 50);
		break;
	case 4:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick2_b.tga");
		SetSize(205 * 2 / 3, 50);
		break;
	case 5:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick2_c.tga");
		SetSize(308 * 2 / 3, 50);
		break;
	case 6:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick3_a.tga");
		SetSize(256 * 2 / 3, 50);
		break;
	case 7:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick3_b.tga");
		SetSize(308 * 2 / 3, 50);
		break;
	case 8:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick3_c.tga");
		SetSize(205 * 2 / 3, 50);
		break;
	case 9:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick4_a.tga");
		SetSize(256 * 2 / 3, 50);
		break;
	case 10:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick4_b.tga");
		SetSize(205 * 2 / 3, 50);
		break;
	case 11:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick4_c.tga");
		SetSize(308 * 2 / 3, 50);
		break;
	case 12:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick5_a.tga");
		SetSize(256 * 2 / 3, 50);
		break;
	case 13:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick5_b.tga");
		SetSize(205 * 2 / 3, 50);
		break;
	case 14:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick5_c.tga");
		SetSize(308 * 2 / 3, 50);
		break;
	case 15:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick6_a.tga");
		SetSize(205 * 2 / 3, 50);
		break;
	case 16:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick6_b.tga");
		SetSize(256 * 2 / 3, 50);
		break;
	case 17:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick6_c.tga");
		SetSize(308 * 2 / 3, 50);
		break;
	case 18:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick7_a.tga");
		SetSize(205 * 2 / 3, 50);
		break;
	case 19:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick7_b.tga");
		SetSize(256 * 2 / 3, 50);
		break;
	case 20:
		resetTexture = ResourceManagers::GetInstance()->GetTexture("brick7_c.tga");
		SetSize(308 * 2 / 3, 50);
		break;
	default:
		break;
	}
	SetTexture(resetTexture);
	SetType(BRICK);
}
static int i = 1;
void Obstacle::SetSpeed(std::shared_ptr<Obstacle> m_obstacle, float speed, float deltaTime) {
	Vector2 obstacleMove = m_obstacle->Get2DPosition();
	obstacleMove.y += speed * deltaTime;
	
	if (obstacleMove.y > (float)Globals::screenHeight + m_obstacle->GetScale().y / 2) {
		printf("%d. %f: %f\n",i , m_obstacle->GetScale().x, obstacleMove.y);
		m_obstacle->SwitchType();
		obstacleMove.y -= 21 * m_obstacle->GetScale().y;
		if (m_obstacle->Get2DPosition().x < (float)Globals::screenWidth / 2) {
			obstacleMove.x = m_obstacle->GetScale().x / 2;
		}
		else {
			obstacleMove.x = (float)Globals::screenWidth - m_obstacle->GetScale().x / 2;
		}
		printf("%f: %f\n", m_obstacle->GetScale().x, obstacleMove.y);
		printf("----------------\n");
		i++;
		if (i == 22) i = 1;
	}
	m_obstacle->Set2DPosition(obstacleMove.x, obstacleMove.y);
}

