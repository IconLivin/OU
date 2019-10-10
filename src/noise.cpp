#include <iostream>
#include <math.h>
#include <random>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

const float PI = 3.14159265358979323846;

Mat createNoise(Mat image, Mat noise) 
{
	return image + noise;
}

Mat gauss_noise(int rows,int cols) 
{	Mat img(rows, cols, CV_8UC1);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> d(5,1);
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			img.at <uchar>(i, j) = abs((int) d(gen)*2);
	return img;
}
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