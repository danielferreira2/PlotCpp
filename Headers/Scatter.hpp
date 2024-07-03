#ifndef Scatter_HPP
#define Scatter_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Scatter {
public:
    Scatter(float width, float height, const std::string& xAxisName, const std::string& yAxisName, float xScale, float yScale, float xStep, float yStep);

    void draw(sf::RenderWindow& window);
    sf::Vector2f map(float x, float y);

private:
    void drawScales(sf::RenderWindow& window);

    float width, height;
    std::string xAxisName, yAxisName;
    float xScale, yScale;
    float xStep, yStep;
    sf::RectangleShape xAxis, yAxis;
    sf::Font font;
    sf::Text xAxisLabel, yAxisLabel;
    const int AXIS_MARGIN;
};

#endif // Scatter_HPP
