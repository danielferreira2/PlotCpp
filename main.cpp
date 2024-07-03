#include <SFML/Graphics.hpp>
#include <iostream>
#include "Headers/Scatter.hpp"



int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Grafico x por y");
    Scatter scatter(500, 500, "eixo X", "eixo Y", 20.0f, 20.0f, 5.0f, 5.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        //desenhar eixos
        scatter.draw(window);

        //desenhar qualquer coisa desde esteja que no intervalo de pontos mapeados
        sf::Vector2f mappedPoint = scatter.map(5.f, 5.f);
        sf::CircleShape point(3);
        point.setFillColor(sf::Color::Red);
        point.setPosition(mappedPoint);

        sf::Vector2f mappedPoint2 = scatter.map(15.f, 10.f);
        sf::RectangleShape point2(sf::Vector2f(6,6));
        point2.setFillColor(sf::Color::Blue);
        point2.setPosition(mappedPoint2);

        window.draw(point);
        window.draw(point2);

        window.display();
    }

    return 0;
}
