#include<iostream>
#include <SFML/Graphics.hpp>
#include"Window.h"
//#include"Testing.cpp"
using namespace std;
void Camera_test_resh_param() {
	Camera Camer;
	float** m = new float* [3];
	*m = new float[4] {1, 2, 3, 1};
	*(1 + m) = new float[4] {5, 6, 7, 5};
	*(2 + m) = new float[4] {9, 6, 11, 9};
	Camer.resh_param(m);
	Camer.print_dop_resh_param();
	//cout << Camer.determinant(m) << endl;
}
int main() {
	//sf::RenderWindow win(sf::VideoMode(800, 800), "run");
	//Window window(win);
	//window.Run();
	Camera_test_resh_param();
	return 0;
}