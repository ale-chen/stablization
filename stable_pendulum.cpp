// stable_pendulum.cpp: Alec Chen
// Fiddling Around in C++, though hopefully eventually
// stabilizing a vertical pendulum w/ periodic movement

#include <iostream>
#include <SFML/Graphics.hpp> // Simple Graphics Library: SFML 3.0

using namespace std;


int main() {
	sf::RenderWindow window(sf::VideoMode({640,480}), "SFML Window");

	// Start Loop
	while (window.isOpen()){
		while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
                window.close();
        }
    }
		window.clear();

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
