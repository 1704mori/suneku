#include "Food.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Utils.h"

namespace snek
{
    Food::Food()
    {
        // Initialize random seed
        SetLogger(new common::Logger("Food", false));
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        // Spawn();
    }

    Food::~Food()
    {
        delete logger;
    }

    void Food::Spawn()
    {
        logger->info("Spawning food...");

        int x = std::rand() % (m_Settings.GetWindowWidth() / m_Settings.GetGridSize());
        int y = std::rand() % (m_Settings.GetWindowHeight() / m_Settings.GetGridSize());

        // Check if the food spawned on the snake
        for (const auto &segment : m_Snake.GetBody())
        {
            if (segment.first == x && segment.second == y)
            {
                logger->info("Food spawned on snake, respawning...");
                Spawn();
                return;
            }
        }

        // m_Position.push_back(std::make_pair(x, y));
        m_Position.push_back({x, y});
    }

    void Food::Remove(int index)
    {
        m_Position.erase(m_Position.begin() + index);
        
        std::string message = "Food removed at index: " + std::to_string(index);
        logger->info(message);
    }

    void Food::RemoveAllFood()
    {
        m_Position.clear();
        m_Position.shrink_to_fit();
    }

    std::vector<Position> Food::GetPosition() const
    {
        return m_Position;
    }
}