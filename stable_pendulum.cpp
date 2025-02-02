// stable_pendulum.cpp: Alec Chen
// Fiddling Around in C++, though hopefully eventually
// stabilizing a vertical pendulum w/ periodic movement

#include <iostream>
#include <SFML/Graphics.hpp> // Simple Graphics Library: SFML 3.0
#include <math.h>

using namespace std;


class Pendulum {
	public:
		sf::Vector2f my_loc;

		sf::RectangleShape line;
		sf::CircleShape circle;

		sf::RenderWindow& my_window;

		float my_length;
		float my_angle;

		float my_thickness;

		Pendulum(float loc[2],
				sf::RenderWindow& window,
				float length, float angle,
				float thickness = 5.f)
				: my_window(window) {

			my_loc = sf::Vector2f(loc[0], loc[1]);
			my_angle = angle;
			my_length = length;
			my_thickness = thickness;

			sf::Vector2f circle_loc(length, sf::radians(angle));
			circle_loc += my_loc;

			line.setSize({length, thickness});
			line.setRotation(sf::radians(angle));
			line.setPosition(my_loc);
			line.setOrigin({0,thickness/2});

			circle.setRadius(3*thickness);
			circle.setPosition(circle_loc);
			circle.setOrigin({3*thickness, 3*thickness});
		}
		void update(float angle, float length) {
			my_angle = angle;
			my_length = length;
			
			sf::Vector2f circle_loc(length, sf::radians(angle));
			circle_loc += my_loc;
			
			line.setSize({length, my_thickness});
			line.setRotation(sf::radians(angle));
			circle.setPosition(circle_loc);
		}
		float getAngle() {return my_angle;}
		float getLength() {return my_length;}
		void draw() {my_window.draw(line); my_window.draw(circle);}
};


int main() {
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({640,480}), "Pendulum", sf::Style::Default, sf::State::Windowed, settings);

	float default_length = 150.f;
	float loc[2] = {320.f,240.f};
	
	Pendulum pendulum(loc, window, default_length, 0.f);

	float d_angle = M_PI/18000;

	// Start Loop
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
        }
    }
		pendulum.update(pendulum.getAngle() + d_angle, default_length);

		window.clear();
		pendulum.draw();
		window.display();
	}

	return 0;
}

// int main () {
// 	int input_var = 0;
// 
// 	do {
// 		cout << "Enter any number, -1 will quit the program.";
// 		if (!(cin >> input_var)){
// 			cout << "Exiting the program. Thanks!" << endl;
// 			break;
// 		}
// 		if (input_var != -1) {
// 			cout << "You entered: " << input_var << endl;
// 		}
// 	} while (input_var != -1);
// 	cout << "Finished! Thanks." << endl;
// 	return 0;
// }
