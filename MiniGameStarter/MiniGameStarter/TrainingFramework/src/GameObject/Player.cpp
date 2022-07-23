#include "Player.h"

Player::Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime)
	: SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime) {}

Player::~Player() {}

bool Player::HandleTouchEvents(float x, float y, bool IsPressed, std::shared_ptr<Player> m_larva) {
	if (IsPressed) {
		if ((x >= Get2DPosition(m_larva).x - GetScale().x / 2 && x <= Get2DPosition(m_larva).x + GetScale().x / 2) && (y >= Get2DPosition(m_larva).y - GetScale().y / 2 && y <= Get2DPosition(m_larva).y + GetScale().y / 2)) {
			return true;
		}
	}
	return false;
}

void Player::SetSpeed(std::shared_ptr<Player> m_obj, float speed, float deltaTime) {
	Vector2 obj_pos = m_obj->Get2DPosition(m_obj);
	obj_pos.y += speed * deltaTime;
	if (obj_pos.y >= m_obj->GetScale().y / 2 + (float)Globals::screenHeight) {
		obj_pos.y -= (float)Globals::screenHeight + m_obj->GetScale().y;
		m_obj->SetSize(50, 50);
	}
	m_obj->Set2DPosition(obj_pos.x, obj_pos.y);
}