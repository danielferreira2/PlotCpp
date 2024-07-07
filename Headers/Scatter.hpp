#ifndef Scatter_HPP
#define Scatter_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

using Point = std::pair<float, float>;

class Scatter {
public:
    Scatter(
        float width, float height,
        const std::string& xAxisName, const std::string& yAxisName,
        float xScale, float yScale,
        float xStep, float yStep);

    void draw(sf::RenderWindow& window);
    void addSetOfPoints(const std::string& legendName, std::vector<Point>& points, sf::Color color);
    void updatePoints(const std::string& legendName, std::vector<Point>& points);

    sf::Vector2f map(float x, float y);

private:
    void drawScales(sf::RenderWindow& window);
    void drawPoints(sf::RenderWindow& window);
    void drawLegends(sf::RenderWindow& window);

    float width, height;
    std::string xAxisName, yAxisName;
    float xScale, yScale;
    float xStep, yStep;
    sf::RectangleShape xAxis, yAxis;
    sf::Font font;
    sf::Text xAxisLabel, yAxisLabel;
    const int AXIS_MARGIN;
    const float POINT_SIZE;

    struct PointSet {
        std::vector<sf::CircleShape> points;
        sf::Color color;
    };
    
    std::unordered_map<std::string, PointSet> pointSets;
};

#endif // Scatter_HPP
