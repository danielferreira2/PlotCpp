#include <SFML/Graphics.hpp>
#include "Headers/Scatter.hpp"
#include <vector>

using Point = std::pair<float, float>;

Point calculateCentroid(const std::vector<Point>& points) {
    float x_sum = 0.0f, y_sum = 0.0f;
    for (const auto& point : points) {
        x_sum += point.first;
        y_sum += point.second;
    }
    return { x_sum / points.size(), y_sum / points.size() };
}

void expandFromCenter(std::vector<Point>& points, float expandStep) {
    if (points.empty()) return;

    auto centroid = calculateCentroid(points);
    for (auto& point : points) {
        point.first += (point.first - centroid.first) * expandStep;
        point.second += (point.second - centroid.second) * expandStep;
    }
}

void convergeToCenter(std::vector<Point>& points, float convergeStep) {
    if (points.empty()) return;

    auto centroid = calculateCentroid(points);
    for (auto& point : points) {
        point.first += (centroid.first - point.first) * convergeStep;
        point.second += (centroid.second - point.second) * convergeStep;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 800), "Plot dinamico");

    Scatter scatter(800, 800, "Eixo X", "Eixo Y", 20.0f, 20.0f, 1.0f, 1.0f);
    std::vector<Point> blue_set = {
        {1.0f, 3.0f},
        {12.0f, 1.0f},
        {5.0f, 3.0f},
        {3.0f, 2.0f},
        {6.0f, 7.0f},
        {7.0f, 8.0f},
        {8.0f, 5.0f},
        {2.0f, 1.5f},
        {9.0f, 4.0f},
        {10.0f, 2.0f}
    };

    std::vector<Point> red_set = {
        {4.5f, 3.5f},
        {1.0f, 9.0f},
        {6.0f, 2.0f},
        {2.0f, 8.0f},
        {5.0f, 7.0f},
        {3.0f, 6.0f},
        {7.0f, 3.0f},
        {4.0f, 9.5f},
        {8.0f, 2.0f},
        {9.0f, 1.0f}
    };

    std::vector<Point> yellow_set = {
        {9.0f, 8.0f},
        {5.0f, 5.5f},
        {7.0f, 6.0f},
        {1.0f, 7.0f},
        {2.0f, 6.5f},
        {3.0f, 5.0f},
        {4.0f, 4.5f},
        {8.0f, 7.0f},
        {6.0f, 5.5f},
        {10.0f, 8.0f}
    };

    std::vector<Point> pink_set = {
        {10.0f, 6.0f},
        {12.0f, 7.0f},
        {11.0f, 8.0f},
        {13.0f, 6.5f},
        {9.0f, 7.5f},
        {14.0f, 5.5f},
        {15.0f, 6.0f},
        {16.0f, 7.0f},
        {13.0f, 8.0f},
        {12.5f, 6.5f}
    };

    scatter.addSetOfPoints("azuis", blue_set, sf::Color::Blue);
    scatter.addSetOfPoints("vermelhos", red_set, sf::Color::Red);
    scatter.addSetOfPoints("amarelos",yellow_set, sf::Color::Yellow);
    scatter.addSetOfPoints("rosas",pink_set,sf::Color::Magenta);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Atualiza os pontos convergindo para o ponto médio (exemplo de alteração dinâmica)
        convergeToCenter(blue_set,0.0001f);
        convergeToCenter(red_set,0.0001f);
        convergeToCenter(yellow_set,0.0001f);
        convergeToCenter(pink_set,0.0001f);

        // Atualiza os pontos expandindo do ponto médio (exemplo de alteração dinâmica)
        // expandFromCenter(blue_set,0.0001f);
        // expandFromCenter(red_set,0.0001f);
        // expandFromCenter(yellow_set,0.0001f);
        // expandFromCenter(pink_set,0.0001f);
        
        //atualiza plot
        scatter.updatePoints("azuis", blue_set);
        scatter.updatePoints("vermelhos",red_set);
        scatter.updatePoints("amarelos",yellow_set);
        scatter.updatePoints("rosas",pink_set);

        window.clear();
        scatter.draw(window);
        window.display();
    }

    return 0;
}
