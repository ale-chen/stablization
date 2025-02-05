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
	settings.antiAliasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode({640,480}), "Pendulum", sf::Style::Default, sf::State::Windowed, settings);
	window.setFramerateLimit(10);
	
	const float g = 1;
	float instant_ang_freq = 1;
	float epsilon = 0.05;

	float default_length = g/pow(instant_ang_freq,2);
	float loc[2] = {320.f,240.f};
	
	Pendulum pendulum(loc, window, default_length*50.f, 0.f);

	// Every frame is a 'second'; dt = 1.
	float phi = 0.f; // instantaneous phase
	float l0 = default_length;
	float ldot0 = (2 * g * epsilon * std::sin(phi)) / pow(epsilon * std::cos(phi) + instant_ang_freq, 2);
	float theta0 = -0.5 * M_PI;
	float omega0 = 0.f;
	float alpha0 = -2*ldot0*omega0/l0+(g/l0)*(std::cos(theta0)); // Perhaps needs to take into account the change (derivatives) of l?
	
	float l1;
	float ldot1;
	float theta1;
	float omega1;
	float alpha1;

	// Start Loop
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
          window.close();
				}
				else if (keyPressed->scancode == sf::Keyboard::Scancode::Space){
					omega0+=M_PI/180;
				}
				else if (keyPressed->scancode == sf::Keyboard::Scancode::LShift){
					if(std::fmod(instant_ang_freq,1) <= 0.25){
						epsilon = 0.05;
						instant_ang_freq = 0.5;
					}else if(std::fmod(instant_ang_freq,1) >= 0.25){
						instant_ang_freq = 1.f;
						epsilon = 0.05;
					}	
      	}
				else if (keyPressed->scancode == sf::Keyboard::Scancode::RShift){
					epsilon = 0;
				}
    	}
		}

		phi = std::fmod(phi + instant_ang_freq + epsilon*std::cos(phi), 2*M_PI);
		if (phi < 0) phi += 2*M_PI;

		l1 = g/(pow(instant_ang_freq + epsilon * std::cos(phi), 2));
		ldot1 = (2 * g * epsilon * std::sin(phi)) / pow(instant_ang_freq + epsilon * std::cos(phi), 2);
		theta1 = theta0 + omega0 + (0.5)*alpha0;
		alpha1 = -2*ldot1*omega1/l1 + (g/l1)*(std::cos(theta1));
		omega1 = omega0 + (0.5)*(alpha0+alpha1);
		
		pendulum.update(theta1, l1*50.f);


		l0=l1;
		ldot0 = ldot1;
		theta0 = theta1;
		omega0 = omega1;
		alpha0 = alpha1;
		
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
