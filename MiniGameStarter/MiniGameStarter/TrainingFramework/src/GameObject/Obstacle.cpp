#include "Obstacle.h"
#include "Texture.h"
#include "ResourceManagers.h"


char* s[][9] = { "brick1_a", "brick1_b", "brick1_c" , "brick2_a" , "brick2_b" , "brick2_c" , "brick3_a" , "brick3_b" , "brick3_c" , "brick4_a"
, "brick4_b" , "brick4_c" , "brick5_a" , "brick5_b" , "brick5_c" , "brick6_a" , "brick6_b" , "brick7_a" , "brick7_b" , "brick7_c" };
static int tmp;

Obstacle::Obstacle(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, ObstacleType type)
	: Sprite2D(model, shader, texture)
{
	std::shared_ptr<Texture> newTexture;
	switch (type)
	{
	case BRICK:
		{tmp = rand() % 21;

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
	case HOTDOG:
		break;
	case BANANA:
		break;
	case SPIKE:
		break;
	default:
		break;
	}

}

Obstacle::~Obstacle() {};