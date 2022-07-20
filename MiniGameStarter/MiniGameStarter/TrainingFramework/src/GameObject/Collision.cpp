#include "Collision.h"
#include "Player.h"
#include "Obstacle.h"
#include "Singleton.h"

bool Collision::CheckCollision(std::shared_ptr<Obstacle> m_obstacle, std::shared_ptr<Player> m_larva) {
    Vector2 pos_obstalce = m_obstacle->Get2DPosition();
    Vector2 pos_larva = m_larva->Get2DPosition(m_larva);
    int left_a = pos_obstalce.x - m_obstacle->GetScale().x / 2 ;
    int right_a = pos_obstalce.x + m_obstacle->GetScale().x / 2;
    int top_a = pos_obstalce.y - m_obstacle->GetScale().y / 2;
    int bottom_a = pos_obstalce.y + m_obstacle->GetScale().y/2;

    int left_b = pos_larva.x - m_larva->GetScale().x / 2;
    int right_b = pos_larva.x + m_larva->GetScale().x/2;
    int top_b = pos_larva.y - m_larva->GetScale().y / 2;
    int bottom_b = pos_larva.y + m_larva->GetScale().y/2;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

void Collision::SetCollision(std::shared_ptr<Player> m_larva) {
    m_collision = m_larva->Get2DPosition(m_larva);
}

Vector2 Collision::GetCollision() {
    return m_collision;
}

