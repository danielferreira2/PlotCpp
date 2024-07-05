#include "Headers/Scatter.hpp"
#include <iostream>

Scatter::Scatter(
    float width, float height,
    const std::string& xAxisName, const std::string& yAxisName,
    float xScale, float yScale, float xStep, float yStep):
    width(width), height(height),
    xAxisName(xAxisName), yAxisName(yAxisName),
    xScale(xScale), yScale(yScale),
    xStep(xStep), yStep(yStep),
    AXIS_MARGIN(50){    

    const int AXIS_THICKNESS = 2;
    const int LABEL_SIZE = 15;
    const int X_AXIS_LABEL_OFFSET_X = 10;
    const int X_AXIS_LABEL_OFFSET_Y = 10;
    const int Y_AXIS_LABEL_OFFSET_X = 10;
    const int Y_AXIS_LABEL_OFFSET_Y = 10;

    xAxis.setSize(sf::Vector2f(width - 2 * AXIS_MARGIN, AXIS_THICKNESS));
    xAxis.setPosition(AXIS_MARGIN, height - AXIS_MARGIN);
    xAxis.setFillColor(sf::Color::White);

    yAxis.setSize(sf::Vector2f(AXIS_THICKNESS, height - 2 * AXIS_MARGIN));
    yAxis.setPosition(AXIS_MARGIN, AXIS_MARGIN);
    yAxis.setFillColor(sf::Color::White);

    if (!font.loadFromFile("Fonts/Roboto-Regular.ttf")) {
        std::cerr << "Fonte não encontrada! Verifique se o arquivo está no diretório correto." << std::endl;
        exit(EXIT_FAILURE);
    }

    xAxisLabel.setFont(font);
    xAxisLabel.setString(xAxisName);
    xAxisLabel.setCharacterSize(LABEL_SIZE);
    xAxisLabel.setFillColor(sf::Color::White);
    xAxisLabel.setPosition(width - AXIS_MARGIN - X_AXIS_LABEL_OFFSET_X, height - AXIS_MARGIN + X_AXIS_LABEL_OFFSET_Y);

    yAxisLabel.setFont(font);
    yAxisLabel.setString(yAxisName);
    yAxisLabel.setCharacterSize(LABEL_SIZE);
    yAxisLabel.setFillColor(sf::Color::White);
    yAxisLabel.setPosition(AXIS_MARGIN - Y_AXIS_LABEL_OFFSET_X, Y_AXIS_LABEL_OFFSET_Y);
}

void Scatter::draw(sf::RenderWindow& window) {
    window.draw(xAxis);
    window.draw(yAxis);
    window.draw(xAxisLabel);
    window.draw(yAxisLabel);

    drawScales(window);

    for (const auto& set : pointSets) {
        for (const auto& point : set.points) {
            window.draw(point);
        }
    }

    drawLegends(window);
 
}

void Scatter::addSetOfPoints(const std::vector<std::pair<float, float>>& points, sf::Color color, const std::string& legendName) {
    PointSet pointSet;
    pointSet.color = color;
    pointSet.legendName = legendName;

    for (const auto& p : points) {
        sf::CircleShape point(5.0f); // tamanho do ponto
        point.setFillColor(color); // cor do ponto
        point.setPosition(map(p.first, p.second));
        pointSet.points.push_back(point);
    }
    pointSets.push_back(pointSet);
}


void Scatter::drawLegends(sf::RenderWindow& window){
    const int LEGEND_BOX_SIZE = 10;
    const int LEGEND_TEXT_SIZE = 12;
    sf::Text legendText;
    legendText.setFont(font);
    legendText.setCharacterSize(LEGEND_TEXT_SIZE);
    legendText.setFillColor(sf::Color::White);

    float legendY = AXIS_MARGIN;
    for (const auto& set : pointSets) {
        sf::RectangleShape legendBox(sf::Vector2f(LEGEND_BOX_SIZE, LEGEND_BOX_SIZE));
        legendBox.setFillColor(set.color);
        legendBox.setPosition(width - AXIS_MARGIN + 10, legendY);
        window.draw(legendBox);

        legendText.setString(set.legendName);
        legendText.setPosition(width - AXIS_MARGIN + 10 + LEGEND_BOX_SIZE + 5, legendY - (LEGEND_TEXT_SIZE / 4));
        window.draw(legendText);

        legendY += LEGEND_BOX_SIZE + 15; // Aumentado o espaçamento entre legendas
    }
}


sf::Vector2f Scatter::map(float x, float y) {
    float x1 = AXIS_MARGIN + (x / xScale) * (width - 2 * AXIS_MARGIN);
    float y1 = height - AXIS_MARGIN - (y / yScale) * (height - 2 * AXIS_MARGIN);
    return sf::Vector2f(x1, y1);
}

void Scatter::drawScales(sf::RenderWindow& window) {
    const int TICK_LENGTH = 5;
    const int LABEL_SIZE = 10;

    sf::Text label;
    label.setFont(font);
    label.setCharacterSize(LABEL_SIZE);
    label.setFillColor(sf::Color::White);

    //Desenha os divisões do eixo x
    for (float x = 0; x <= xScale; x += xStep) {
        float xPos = AXIS_MARGIN + (x / xScale) * (width - 2 * AXIS_MARGIN);
        sf::Vector2f tickPos(xPos, height - AXIS_MARGIN);

        sf::RectangleShape tick(sf::Vector2f(1, TICK_LENGTH));
        tick.setPosition(tickPos);
        tick.setFillColor(sf::Color::White);
        window.draw(tick);

        label.setString(std::to_string(static_cast<int>(x)));
        label.setPosition(tickPos.x, tickPos.y + TICK_LENGTH);
        window.draw(label);
    }

    //Desenha os divisões do eixo y
    for (float y = 0; y <= yScale; y += yStep) {
        float yPos = height - AXIS_MARGIN - (y / yScale) * (height - 2 * AXIS_MARGIN);
        sf::Vector2f tickPos(AXIS_MARGIN, yPos);

        sf::RectangleShape tick(sf::Vector2f(TICK_LENGTH, 1));
        tick.setPosition(tickPos);
        tick.setFillColor(sf::Color::White);
        window.draw(tick);

        label.setString(std::to_string(static_cast<int>(y)));
        label.setPosition(tickPos.x - TICK_LENGTH * 2, tickPos.y - LABEL_SIZE / 2);
        window.draw(label);
    }
}
