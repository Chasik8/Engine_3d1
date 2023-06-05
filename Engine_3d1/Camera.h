#pragma once
#include<cmath>
#include"Poligon.h"
class Camera {
private:
	float* versh;
	float** vect;
	float alpha;
	float heid_weid;
	float dist = 50;
	float* plosk;
	float** projection_plosk;
	int kol_projection_plosk_max;
	int kol_projection_plosk;
	const float PI = 3.1415926535897932384626433832;
	float* dop_resh_param;
public:
	Camera() {
		heid_weid = 9 / 16;
		alpha = 90 / 180 * PI;
		versh = new float [3] {0, 0, 0};
		vect = new float* [4];
		float a = tan(alpha / 2) * dist;
		*(vect) = new float [3] {dist, a, a* heid_weid};
		*(vect + 1) = new float [3] {dist, a, -a * heid_weid};
		*(vect + 2) = new float [3] {dist, -a, a* heid_weid};
		*(vect + 3) = new float [3] {dist, -a, -a * heid_weid};
		plosk = new float[4] {1, 0, 0, -dist};
		kol_projection_plosk_max = 100;
		kol_projection_plosk = 0;
		projection_plosk = new float* [kol_projection_plosk_max];
		for (int i = 0; i < kol_projection_plosk_max; ++i) {
			*(i + projection_plosk) = new float[3];
		}
		dop_resh_param = new float[3];
	}
	void print_dop_resh_param() {
		std::cout << *dop_resh_param << " " << *(1 + dop_resh_param) << " " <<
			*(2 + dop_resh_param) << std::endl;
	}
	void print_matrix(float** m,int a, int b) {
		for (int i = 0; i < a; ++i) {
			for (int j = 0; j < b; ++j) {
				std::cout << *(j + *(i + m)) << " ";
			}
			std::cout << std::endl;
		}
	}
	void Plosk_update() {

	}
	void detection(Poligon* poligon, long long int Poligon_kol) {
		for (long long int a = 0; a < Poligon_kol; ++a) {
			detection_point((*(poligon+a)).point(0));

			detection_point((*(poligon + a)).point(1));
			detection_point((*(poligon + a)).point(2));
		}
	}
	void detection_point(float* point) {
		// матрица 3 на 4 для нахожднения точки пересечения точки полигона с прямой
		float** matrix = new float* [3];
		*matrix = plosk;
		float x = (*(point + 0) - *(versh + 0));
		float y = (*(point + 1) - *(versh + 1));
		float z = (*(point + 2) - *(versh + 2));
		//уравнение прямой через пересечение плоскостей.
		*(1 + matrix) = new float[4] {y, -x + z, -y, x* (*(versh + 1)) + y * (-(*(versh + 0)) + (*(versh + 2))) - z * (*(versh + 1))};
		*(2 + matrix) = new float[4] {z, 0, -x, x* (*(versh + 2)) - z * (*(versh + 0))};
		resh_param(matrix);
	}
	void resh_param(float** matrix) {
		float** det_matrix = new float* [3];
		// дельта для решения системы уравнений
		print_matrix(matrix, 3, 4);
		float delt = determinant(matrix);
		//std::cout << delt << std::endl;
		//std::cout << *(*(matrix)+3)<<std::endl;
		*(det_matrix) = new float[3] {-*(*(matrix)+3), * (*(matrix)+1), * (*(matrix)+2)};
		*(det_matrix+1) = new float[3] {-*(*(matrix + 1)+3), * (*(matrix + 1)+1), * (*(matrix + 1)+2)};
		*(det_matrix+2) = new float[3] {-*(*(matrix + 2)+3), * (*(matrix + 2)+1), * (*(matrix + 2)+2)};
		//print_matrix(det_matrix, 3, 3);
		//float delt_x = determinant(det_matrix
		//std::cout << determinant(det_matrix) << std::endl;
		*dop_resh_param = determinant(det_matrix) / delt;
		*(*(det_matrix)) = *(*(matrix)+0);
		*(*(det_matrix)+1) = -*(*(matrix)+3);
		*(*(det_matrix+1)) = *(*(matrix + 1)+0);
		*(*(det_matrix + 1)+1) = -*(*(matrix + 1)+3);
		*(*(det_matrix+2)) = *(*(matrix + 2)+0);
		*(*(det_matrix + 2)+1) = -*(*(matrix + 2)+3);
		//print_matrix(det_matrix, 3, 3);
		//float delt_y = determinant(det_matrix);
		*(1+dop_resh_param) = determinant(det_matrix) / delt;
		//std::cout << determinant(det_matrix) << std::endl;
		*(*(det_matrix)+1) = *(*(matrix)+1);
		*(*(det_matrix)+2) = -*(*(matrix)+3);
		*(*(det_matrix+1)+1) = *(*(matrix + 1) + 1);
		*(*(det_matrix + 1) + 2) = -*(*(matrix + 1) + 3);
		*(*(det_matrix+2)+1) = *(*(matrix + 2) + 1);
		*(*(det_matrix + 2) + 2) = -*(*(matrix + 2) + 3);
		//float delt_z = determinant(det_matrix);
		*(2+dop_resh_param) = determinant(det_matrix) / delt;
		//std::cout << determinant(det_matrix) << std::endl;
		//print_matrix(det_matrix, 3, 3);
		// сохранение ответа
		//*(*(kol_projection_plosk + projection_plosk)) = delt_x / delt;
		//*(*(kol_projection_plosk + projection_plosk)+1) = delt_y / delt;
		//*(*(kol_projection_plosk + projection_plosk)+2) = delt_z / delt;
		//*(det_matrix) = new float[3] {*plosk, * (*matrix + 1), * (*matrix + 2)};
		//*(det_matrix + 1) = new float[3] {*(plosk + 1), * (*(matrix + 1) + 1), * (*(matrix + 1) + 2)};
		//*(det_matrix + 2) = new float[3] {*(plosk + 2), * (*(matrix + 2) + 1), * (*(matrix + 2) + 2)};
	}
	float determinant(float** m) {
		//return (*(*(m + 0) + 0) * *(*(m + 1) + 1) * *(*(m + 2) + 2)) + (*(*(m + 0) + 1) * *(*(m + 1) + 2) * *(*(m + 2) + 0)) + (*(*(m + 0) + 2) * *(*(m + 1) + 0) * *(*(m + 2) + 1)) -
		//	(*(*(m + 0) + 2) * *(*(m + 1) + 1) * *(*(m + 2) + 0)) - (*(*(m + 0) + 1) * *(*(m + 1) + 0) * *(*(m + 0) + 2)) - (*(*(m + 0) + 0) * *(*(m + 0) + 2) * *(*(m + 2) + 1));
		//std::cout << -(*(*(m + 0) + 2) * *(*(m + 1) + 1) * *(*(m + 2) + 0)) - (*(*(m + 0) + 1) * *(*(m + 1) + 0) * *(*(m + 2) + 2)) - (*(*(m + 0) + 0) * *(*(m + 1) + 2) * *(*(m + 2) + 1)) << std::endl;
		return (*(*(m + 0) + 0) * *(*(m + 1) + 1) * *(*(m + 2) + 2)) + (*(*(m + 1) + 0) * *(*(m + 2) + 1) * *(*(m + 0) + 2)) + (*(*(m + 2) + 0) * *(*(m + 0) + 1) * *(*(m + 1) + 2)) -
			(*(*(m + 0) + 2) * *(*(m + 1) + 1) * *(*(m + 2) + 0)) - (*(*(m + 0) + 1) * *(*(m + 1) + 0) * *(*(m + 2) + 2)) - (*(*(m + 0) + 0) * *(*(m + 1) + 2) * *(*(m + 2) + 1));
	}
};