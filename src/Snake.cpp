#include "Snake.h"
#include "Utils.h"
#include "GameSettings.h"

namespace snek
{
    Snake::Snake() : m_Direction(GLFW_KEY_RIGHT)
    {
        // Initialize the snake with a few segments
        m_Body.push_back({4, 4});
        m_Body.push_back({3, 4});
        m_Body.push_back({2, 4});
    }

    // Implement the rest of the Snake class methods (move, grow, isCollision, etc.)
    void Snake::Move()
    {
        // Move the snake based on its current direction
        std::pair<int, int> head = m_Body.front();
        switch (m_Direction)
        {
        case GLFW_KEY_UP:
            m_Body.insert(m_Body.begin(), {head.first, head.second + 1});
            break;
        case GLFW_KEY_DOWN:
            m_Body.insert(m_Body.begin(), {head.first, head.second - 1});
            break;
        case GLFW_KEY_LEFT:
            m_Body.insert(m_Body.begin(), {head.first - 1, head.second});
            break;
        case GLFW_KEY_RIGHT:
            m_Body.insert(m_Body.begin(), {head.first + 1, head.second});
            break;
        }

        // Check for collision and remove the last segment
        if (!IsCollision())
        {
            m_Body.pop_back();
        }
    }

    void Snake::Grow()
    {
        // Add a new segment to the snake's body
        std::pair<int, int> tail = m_Body.back();
        m_Body.push_back(tail);
    }

    bool Snake::IsCollision()
    {
        GameSettings &settings = GameSettings::getInstance();

        // Check if the snake collides with the wall or itself
        std::pair<int, int> head = m_Body.front();
        if (head.first < 0 || head.first >= settings.GetWindowWidth() / settings.GetGridSize() ||
            head.second < 0 || head.second >= settings.GetWindowHeight() / settings.GetGridSize())
        {
            return true; // Wall collision
        }

        for (size_t i = 1; i < m_Body.size(); ++i)
        {
            if (head == m_Body[i])
            {
                return true; // Self collision
            }
        }

        return false;
    }

    void Snake::ChangeDirection(int newDirection)
    {
        // Prevent the snake from reversing its direction
        if ((m_Direction == GLFW_KEY_UP && newDirection != GLFW_KEY_DOWN) ||
            (m_Direction == GLFW_KEY_DOWN && newDirection != GLFW_KEY_UP) ||
            (m_Direction == GLFW_KEY_LEFT && newDirection != GLFW_KEY_RIGHT) ||
            (m_Direction == GLFW_KEY_RIGHT && newDirection != GLFW_KEY_LEFT))
        {
            m_Direction = newDirection;
        }
    }

    void Snake::Reset()
    {
        // Reset the snake's body and direction
        m_Body.clear();
        m_Direction = GLFW_KEY_RIGHT;

        // Initialize the snake with a few segments
        m_Body.push_back({4, 4});
        m_Body.push_back({3, 4});
        m_Body.push_back({2, 4});
    }

    std::vector<std::pair<int, int>> Snake::GetBody() const
    {
        return m_Body;
    }
}