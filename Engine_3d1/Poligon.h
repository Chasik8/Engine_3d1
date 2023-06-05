#pragma once
class Poligon {
private:
	float** vect;
public:
	Poligon() {
		vect = new float* [3];
		*(vect) = new float [3] {70, 30, 0};
		*(vect + 1) = new float [3] {70, -30, 0};
		*(vect + 2) = new float [3] {70, 0, 30};
	}
	float* point(short i) {
		return *(i + vect);
	}
};