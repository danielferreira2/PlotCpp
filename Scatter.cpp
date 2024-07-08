#include "Headers/Scatter.hpp"
#include <iostream>

Scatter::Scatter(
    float pos_x, float pos_y,
    float width, float height,
    const std::string& xAxisName, const std::string& yAxisName,
    float xScale, float yScale, float xStep, float yStep):
    pos_x(pos_x), pos_y(pos_y),
    width(width), height(height),
    xAxisName(xAxisName), yAxisName(yAxisName),
    xScale(xScale), yScale(yScale),
    xStep(xStep), yStep(yStep),
    AXIS_MARGIN(75), POINT_SIZE(5.0f) {

    const int AXIS_THICKNESS = 2;
    const int LABEL_SIZE = 15;

    xAxis.setSize(sf::Vector2f(width - 2 * AXIS_MARGIN, AXIS_THICKNESS));
    xAxis.setPosition(pos_x + AXIS_MARGIN, pos_y + height - AXIS_MARGIN);
    xAxis.setFillColor(sf::Color::White);

    yAxis.setSize(sf::Vector2f(AXIS_THICKNESS, height - 2 * AXIS_MARGIN));
    yAxis.setPosition(pos_x + AXIS_MARGIN, pos_y + AXIS_MARGIN);
    yAxis.setFillColor(sf::Color::White);

    if (!font.loadFromFile("Fonts/Roboto-Regular.ttf")) {
        std::cerr << "Fonte não encontrada! Verifique se o arquivo está no diretório correto." << std::endl;
        exit(EXIT_FAILURE);
    }

    xAxisLabel.setFont(font);
    xAxisLabel.setString(xAxisName);
    xAxisLabel.setCharacterSize(LABEL_SIZE);
    xAxisLabel.setFillColor(sf::Color::White);
    xAxisLabel.setPosition(pos_x + width / 2 - xAxisLabel.getLocalBounds().width / 2, pos_y + height - AXIS_MARGIN / 2);

    yAxisLabel.setFont(font);
    yAxisLabel.setString(yAxisName);
    yAxisLabel.setCharacterSize(LABEL_SIZE);
    yAxisLabel.setFillColor(sf::Color::White);
    yAxisLabel.setPosition(pos_x + AXIS_MARGIN - AXIS_MARGIN / 2, pos_y + height / 2);
    yAxisLabel.setRotation(-90); 
    yAxisLabel.setOrigin(0, yAxisLabel.getLocalBounds().width / 2);
}


void Scatter::draw(sf::RenderWindow& window) {
    window.draw(xAxis);
    window.draw(yAxis);
    window.draw(xAxisLabel);
    window.draw(yAxisLabel);

    drawScales(window);
    drawPoints(window);
    drawLegends(window);
}

void Scatter::drawPoints(sf::RenderWindow& window) {
    for (const auto& set : pointSets) {
        for (const auto& point : set.second.points) {
            window.draw(point);
        }
    }
}

void Scatter::drawLegends(sf::RenderWindow& window) {
    const int LEGEND_BOX_SIZE = 10;
    const int LEGEND_TEXT_SIZE = 12;
    sf::Text legendText;
    legendText.setFont(font);
    legendText.setCharacterSize(LEGEND_TEXT_SIZE);
    legendText.setFillColor(sf::Color::White);

    float legendY = pos_y + AXIS_MARGIN;
    for (const auto& set : pointSets) {
        sf::RectangleShape legendBox(sf::Vector2f(LEGEND_BOX_SIZE, LEGEND_BOX_SIZE));
        legendBox.setFillColor(set.second.color);
        legendBox.setPosition(pos_x + width - AXIS_MARGIN + 10, legendY);
        window.draw(legendBox);

        legendText.setString(set.first);
        legendText.setPosition(pos_x + width - AXIS_MARGIN + 10 + LEGEND_BOX_SIZE + 5, legendY - (LEGEND_TEXT_SIZE / 4));
        window.draw(legendText);

        legendY += LEGEND_BOX_SIZE + 15; 
    }
}

void Scatter::addSetOfPoints(const std::string& legendName, std::vector<Point>& points, sf::Color color) {
    PointSet pointSet;
    pointSet.color = color;

    for (const auto& p : points) {
        sf::CircleShape point(POINT_SIZE); // tamanho do ponto
        point.setFillColor(color); // cor do ponto
        point.setOrigin(POINT_SIZE , POINT_SIZE ); // centra o ponto
        point.setPosition(map(p.first, p.second));
        pointSet.points.push_back(point);
    }
    pointSets[legendName] = pointSet;
}

void Scatter::updatePoints(const std::string& legendName, std::vector<Point>& points) {
    auto it = pointSets.find(legendName);
    if (it != pointSets.end()) {
        it->second.points.clear();
        for (const auto& p : points) {
            sf::CircleShape point(POINT_SIZE); // tamanho do ponto
            point.setFillColor(it->second.color); // cor do ponto
            point.setOrigin(POINT_SIZE , POINT_SIZE ); // centra o ponto
            point.setPosition(map(p.first, p.second));
            it->second.points.push_back(point);
        }
    }
}


sf::Vector2f Scatter::map(float x, float y) {
    float x1 = pos_x + AXIS_MARGIN + (x / xScale) * (width - 2 * AXIS_MARGIN);
    float y1 = pos_y + height - AXIS_MARGIN - (y / yScale) * (height - 2 * AXIS_MARGIN);
    return sf::Vector2f(x1, y1);
}

void Scatter::drawScales(sf::RenderWindow& window) {
    const int TICK_LENGTH = 5;
    const int LABEL_SIZE = 10;
    const int LABEL_OFFSET = 5;
    const sf::Color GRID_COLOR = sf::Color(200, 200, 200, 100); // cor cinza

    sf::Text label;
    label.setFont(font);
    label.setCharacterSize(LABEL_SIZE);
    label.setFillColor(sf::Color::White);

    for (float x = 0; x <= xScale; x += xStep) {
        float xPos = pos_x + AXIS_MARGIN + (x / xScale) * (width - 2 * AXIS_MARGIN);
        sf::Vector2f tickPos(xPos, pos_y + height - AXIS_MARGIN);

        // linha do grid
        sf::RectangleShape gridLine(sf::Vector2f(1, height - 2 * AXIS_MARGIN));
        gridLine.setPosition(sf::Vector2f(xPos, pos_y + AXIS_MARGIN));
        gridLine.setFillColor(GRID_COLOR);
        window.draw(gridLine);

        // ticks
        sf::RectangleShape tick(sf::Vector2f(1, TICK_LENGTH));
        tick.setPosition(tickPos);
        tick.setFillColor(sf::Color::White);
        window.draw(tick);

        // labels
        label.setString(std::to_string(static_cast<int>(x)));
        label.setPosition(tickPos.x - LABEL_OFFSET, tickPos.y + TICK_LENGTH + LABEL_OFFSET);
        window.draw(label);
    }

    for (float y = 0; y <= yScale; y += yStep) {
        float yPos = pos_y + height - AXIS_MARGIN - (y / yScale) * (height - 2 * AXIS_MARGIN);
        sf::Vector2f tickPos(pos_x + AXIS_MARGIN, yPos);

        // linha do grid
        sf::RectangleShape gridLine(sf::Vector2f(width - 2 * AXIS_MARGIN, 1));
        gridLine.setPosition(sf::Vector2f(pos_x + AXIS_MARGIN, yPos));
        gridLine.setFillColor(GRID_COLOR);
        window.draw(gridLine);

        // ticks
        sf::RectangleShape tick(sf::Vector2f(TICK_LENGTH, 1));
        tick.setPosition(tickPos);
        tick.setFillColor(sf::Color::White);
        window.draw(tick);

        // labels
        label.setString(std::to_string(static_cast<int>(y)));
        label.setPosition(tickPos.x - TICK_LENGTH - LABEL_OFFSET * 2, tickPos.y - LABEL_SIZE / 2);
        window.draw(label);
    }
}

