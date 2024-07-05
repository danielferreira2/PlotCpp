#ifndef Scatter_HPP
#define Scatter_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <utility>


class Scatter {
public:
Scatter(
        float width, float height,
        const std::string& xAxisName,const std::string& yAxisName,
        float xScale, float yScale,
        float xStep, float yStep);

    void draw(sf::RenderWindow& window);
    void addSetOfPoints(const std::vector<std::pair<float, float>>& points, sf::Color color, const std::string& legendName);

    sf::Vector2f map(float x, float y);

private:
    void drawScales(sf::RenderWindow& window);
    void drawLegends(sf::RenderWindow& window);

    float width, height;
    std::string xAxisName, yAxisName;
    float xScale, yScale;
    float xStep, yStep;
    sf::RectangleShape xAxis, yAxis;
    sf::Font font;
    sf::Text xAxisLabel, yAxisLabel;
    const int AXIS_MARGIN;

    struct PointSet {
        std::vector<sf::CircleShape> points;
        sf::Color color;
        std::string legendName;
    };
    
    std::vector<PointSet> pointSets;

};

#endif // Scatter_HPP
