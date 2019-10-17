#pragma once
#include <iostream>
#include <math.h>
#include <random>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "histogram.cpp"

using namespace std;
using namespace cv;

const float PI = 3.14159265358979323846;

int formula_gauss() 
{
return 0;
}

int Clamp(int x) {
	int n = x > 0 ? x : 0;
	n = x < 256 ? x : 255;
	return n;
}

int Clamp(int x, int y, int z) {
	int n = x < y ? y : x;
	n = n > z ? z : n;
	return n;
}
Mat createNoise(Mat image, Mat noise) 
{
	return image + noise;
}



Mat Generate_Mask_Gauss(int size_x, int size_y, double pr = 0.1) {
	Mat result(size_x, size_y, CV_8UC3);
	srand(time(NULL));
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.at<Vec3b>(i, j) = 0;
		}
	}
	for (int i = 0; i < size_x * size_y * pr; i++) {
		int x = rand() % size_x;
		int y = rand() % size_y;
		float U = (rand() % 100) / 100.0;
		float E = -log(rand());
		while (U > exp(-(E - 1) * (E - 1))) {
			E = -log(rand());
			U = (rand() % 100) / 100.0;
		}
		U = (rand() % 100) / 100.0;
		if (U > 0.5)E = abs(E);
		else E = -abs(E) + 19;
		result.at<Vec3b>(x, y)[0] = result.at < Vec3b>(x, y)[1] = result.at < Vec3b>(x, y)[2] = E + 5;
	}
	return result;
}

Mat Worse_Img_Gauss(Mat img) {
	Mat result = img.clone();
	Mat mask = Generate_Mask_Gauss(result.rows, result.cols, 0.3);
	imshow("Mask", mask);
	waitKey();
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.at<Vec3b>(i, j) += mask.at<Vec3b>(i, j);
		}
	}
	return result;
}

Mat Generate_Mask_Gamma(int size_x, int size_y,double pr=0.5) {
	random_device rd;
	mt19937 gen(rd());
	gamma_distribution<> d(10,1);
	Mat result(size_x, size_y, CV_8UC3);
	srand(time(NULL));
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.at<Vec3b>(i, j) = 0;
		}
	}
	for (int i = 0; i < size_x * size_y * pr; i++) {
		int x = rand() % size_x;
		int y = rand() % size_y;
		result.at<Vec3b>(x, y)[0] = result.at < Vec3b>(x, y)[1] = result.at < Vec3b>(x, y)[2] = abs(d(gen));
	}
	return result;
}

float** Gauss_Kernel(int radius, float sigma) {
	int size = 2 * radius + 1;
	float** kernel = new float* [size];
	for (int i = 0; i < size; i++) {
		kernel[i] = new float[size];
	}
	float norm = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			kernel[i][j] = (float)(exp(-(i * i + j * j) / (sigma * sigma)));
			norm += kernel[i][j];
		}
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			kernel[i][j] /= norm;
	return kernel;
}

Vec3b Get_Color(float** kernel, Mat img, int size, int x, int y) {
	Vec3b color = 0;
	int x1 = 0, y1 = 0;
	for (int i = x; i < size + x; i++) {
		y1 = 0;
		for (int j = y; j < size + y; j++) {
			color[0] += img.at<Vec3b>(i, j)[0] * kernel[x1][y1];
			color[1] += img.at<Vec3b>(i, j)[1] * kernel[x1][y1];
			color[2] += img.at<Vec3b>(i, j)[2] * kernel[x1][y1];
			y1++;
		}
		x1++;
	}
	return color;
}

Mat Gauss_Filter(Mat img) {
	int n = 3;
	Mat result = img.clone();
	float** kernel = Gauss_Kernel(n, 2);
	for (int i = 2 * n + 1; i < img.rows - (2 * n + 1); i++) {
		for (int j = 2 * n + 1; j < img.cols - (2 * n + 1); j++) {
			result.at<Vec3b>(i, j) = Get_Color(kernel, img, 2 * n + 1, i, j);
		}
	}
	return result;
}



//Mat gauss_noise(int rows,int cols,bool flag) 
//{
//	std::random_device rd;
//	std::mt19937 gen(rd());
//	std::normal_distribution<> d(5, 1);
//	Mat result;
//	if (flag == 0)
//	{
//		Mat img(rows, cols, CV_8UC1);
//		for (int i = 0; i < img.rows; i++)
//			for (int j = 0; j < img.cols; j++)
//				img.at <uchar>(i, j) = abs((int)d(gen) * 2);
//		result = img.clone();
//	}
//	else 
//	{
//		Mat img(rows, cols, CV_8UC3);
//		result = img.clone();
//		for (int i = 0; i < img.rows; i++)
//			for (int j = 0; j < img.cols; j++) {
//				img.at <Vec3b>(i, j)[0] = abs((int)d(gen) * 2);
//				img.at <Vec3b>(i, j)[1] = abs((int)d(gen) * 2);
//				img.at <Vec3b>(i, j)[2] = abs((int)d(gen) * 2);
//			}
//				result = img.clone();
//	}
//	return result;
//}


//Mat CreateNoise(/*Mat img,*/ double mu, double sigma)
//{
//	//Mat image(img.rows, img.cols, CV_8UC1);
//	Mat image(450, 450, CV_8UC1);
//	for (int i = 0; i < image.rows; i++)
//		for (int j = 0; j < image.cols; j++)
//			image.at <uchar>(i, j) = 150;
//	for (int i = 0; i < image.rows; i++)
//		for (int j = 0; j < image.cols; j++)
//			image.at <uchar>(i, j) = (1 / (sigma*sqrt(2 * PI)))*exp(-((pow(image.at <uchar>(i, j) - mu, 2))) / (2 * sigma));
//	imshow("filter", image);
//	waitKey();
//	return image;
//}



//class Noise
//{
//public:
//Mat CreateNoise(Mat img, double mu, double sigma) = 0;
//	Noise(Mat img)
//	{
//		image = img;
//	}
//protected:
//	Mat image;
//
//};
//
//class GaussNoise : public Noise
//{
//public:
//	GaussNoise(Mat img);
//	Mat CreateNoise(Mat img, double mu, double sigma)
//	{
//		for (int i = 0; i < img.rows; i++)
//			for (int j = 0; j < img.cols; j++)
//				img.at <uchar>(i, j) = (1 / (sigma*sqrt(2 * PI)))*exp(-((pow(img.at <uchar>(i, j) - mu, 2))) / (2 * sigma));
//		return image;
//
//	}
//};