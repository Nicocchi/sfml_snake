#include "world.hpp"

World::World(sf::Vector2u l_windSize) {
    m_blockSize = 16;

    m_windowSize = l_windSize;
    RespawnApple();
    m_appleShape.setFillColor(sf::Color::Red);
    m_appleShape.setRadius(m_blockSize / 2);

    // Iterate for each four sides of teh game screen in order to set up a red rectangle wall on
    // each side
    for (int i = 0; i < 4; ++i) {
        m_bounds[i].setFillColor(sf::Color(150, 0, 0));

        // Determine if the index is even or odd
        // Done in order to know how big each wall has to be on a specific axis
        if (!((i + 1) % 2)) {
            m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
        } else {
            m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
        }

        //  Check if the index is below 2. If so, working with the top-left corner so
        // set the position of the rectangle to (0,0), else, set the origin to the size of the
        // rectangle, which makes it the bottom right corner and then set the position of the rect
        // to be the same size as teh screen, which puts the shape all the way down to the bottom
        // right corner
        if (i < 2) {
            m_bounds[i].setPosition(0, 0);
        } else {
            m_bounds[i].setOrigin(m_bounds[i].getSize());
            m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
        }
    }
}

World::~World() {}

void World::RespawnApple() {
    // Determine boundaries of which the apple can spawn
    int maxX = (m_windowSize.x / m_blockSize) - 2;
    int maxY = (m_windowSize.y / m_blockSize) - 2;

    // Generate the apple's coordinates
    m_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);

    // Set the apple's position
    m_appleShape.setPosition(m_item.x * m_blockSize, m_item.y * m_blockSize);
}

void World::Update(Snake &l_player) {
    // Check the player's position is the same as the apple.
    // If we have a collision and the snake gets extended, the score increases and the apple
    // re-spawns
    if (l_player.GetPosition() == m_item) {
        l_player.Extend();
        l_player.IncreaseScore();
        RespawnApple();
    }

    // Determine the grid size and check if the player coordinates are anywhere outside of the
    // designated boundaries, if so, call Lose() method to illustrate the collision with the wall
    // and give player a "game over"
    int gridSize_x = m_windowSize.x / m_blockSize;
    int gridSize_y = m_windowSize.y / m_blockSize;

    if (l_player.GetPosition().x <= 0 || l_player.GetPosition().y <= 0 ||
        l_player.GetPosition().x >= gridSize_x - 1 || l_player.GetPosition().y >= gridSize_y - 1) {
        l_player.Lose();
    }
}

void World::Render(sf::RenderWindow &l_window) {
    // Draw the boundaries
    for (int i = 0; i < 4; ++i) {
        l_window.draw(m_bounds[i]);
    }

    // Draw the apple
    l_window.draw(m_appleShape);
}

int World::GetBlockSize() { return m_blockSize; }