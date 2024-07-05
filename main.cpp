#include <vector>
#include "Headers/Scatter.hpp"


using Point = std::pair<float, float>; //alias para simplificar a leitura

int main() {
    
    sf::RenderWindow window(
        sf::VideoMode(600,600),
        "window"
    );

    Scatter scatter(500, 500, "eixo X", "eixo Y", 20.0f, 20.0f, 5.0f, 5.0f);

    std::vector<Point> blue_set = {
        {1.0f,3.0f},
        {12.0f,1.0f},
        {5.0f,2.0f},
        {1.0f,2.0f},


    };

    std::vector<Point> red_set = {
        {4.5f,3.5f},
        {1.0f,9.0f},
        {6.0f,2.0f},
        {9.0f,8.0f},
    };

    std::vector<Point> yello_set ={
        {5.0f,5.5f},
        {7.0f,6.0f},
        {1.0f,7.0f},
    };

    //atenção jamais chamar esse metodos dentro de um loop
    scatter.addSetOfPoints(blue_set,sf::Color::Blue,"azuis");
    scatter.addSetOfPoints(red_set,sf::Color::Red,"vermelhos");
    scatter.addSetOfPoints(yello_set,sf::Color::Yellow,"amarelos");


    


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

       

        scatter.draw(window);
  
        

        window.display();
    }

    return 0;
}
