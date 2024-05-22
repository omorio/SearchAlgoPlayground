#include <SFML/Graphics.hpp>
#include <iostream>


class Grid : public sf::Drawable, public sf::Transformable {
public:

    bool renderGrid(sf::Vector2u tileSize, unsigned int width, unsigned int height)
    {
        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(width * height * 6);

        // populate the vertex array, with two triangles per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int cellState = level[i + j * width];

                // get a pointer to the triangles' vertices of the current tile
                sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

                // define the 6 corners of the two triangles
                triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

                sf::Color color;
                switch (cellState) {
                    case 0: // Tile number 0, color it red
                        color = sf::Color(150,150,150);
                        break;
                    case 1: // Tile number 1, color it green
                        color = sf::Color(33,33,33);
                        break;
                    case 2: // Tile number 2, color it blue
                        color = sf::Color::Blue;
                        break;
                    default: // Default color is white
                        color = sf::Color::White;
                        break;
                }
                
                // define the color for all vertices
                for (int k = 0; k < 6; ++k) {
                    triangles[k].color = color;
                }
            }
        drawGrid(32, 32, sf::Vector2f(800, 800));
        
        return true;
    }
    //set the internal level array to the given level
    bool loadLevel(const int* lvl){
        for(int i = 0; i < 32*32; i++){
            level[i] = lvl[i];
        }
        return true;
    }
    //set the state of a cell in the level at position x, y to the given state
    bool setCellState(int x, int y, int cellState){
        if(x < 0 || x > 800 || y < 0 || y > 800){
            return false;
        }
        //turn the x, y position into a grid position
        int gridX = x / 25;
        int gridY = y / 25;
        level[gridX + gridY*32] = cellState;
        return true;
    }

    int getCellState(int x, int y){
        if(x < 0 || x > 800 || y < 0 || y > 800){
            return false;
        }
        //turn the x, y position into a grid position
        int gridX = x / 25;
        int gridY = y / 25;
        return level[gridX + gridY*32];
    }

    void printLevel(){
        for(int i = 0; i < 32; i++){
            for(int j = 0; j < 32; j++){
                std::cout << level[i + j*32] << ", ";
            }
            std::cout << std::endl;
        }
    }
    
private:

    sf::VertexArray gridLineVertices;
    sf::VertexArray m_vertices;
    int level[32*32];

    bool drawGrid(int rows, int cols, sf::Vector2f windowSize){
        // initialize values
        int numLines = rows+cols-2;
        gridLineVertices.setPrimitiveType(sf::Lines);
        gridLineVertices.resize(2*numLines);

        float rowH = windowSize.y/rows;
        float colW = windowSize.x/cols;
        // row separators
        for(int i=0; i < rows-1; i++){
            int r = i+1;
            float rowY = rowH*r;
            gridLineVertices[i*2].position = sf::Vector2f(0, rowY);
            gridLineVertices[i*2+1].position = sf::Vector2f(windowSize.x, rowY);
        }
        // column separators
        for(int i=rows-1; i < numLines; i++){
            int c = i-rows+2;
            float colX = colW*c;
            gridLineVertices[i*2].position = sf::Vector2f(colX, 0);
            gridLineVertices[i*2+1].position = sf::Vector2f(colX, windowSize.y);
        }
        return true;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(m_vertices, states);
        target.draw(gridLineVertices, states);
    }
    
};
