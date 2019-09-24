#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>

using namespace std;
using namespace cv;

int Find_Max(int a, int b, int c) {
	if (a > b) {
		if (a > c)return a;
		else return c;
	}
	else if (b > c)return b;
	else return c;
}

int Find_Min(int a, int b, int c) {
	if (a < b) {
		if (a < c)return a;
		else return c;
	}
	else if (b < c)return b;
	else return c;
}

class Filter {
	Mat img;
public:
	Filter(Mat img1) { img = img1; }
	Mat AverageFilter() {
		Mat result=img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (result.at<Vec3b>(i,j)[0] + result.at<Vec3b>(i,j)[1] + result.at<Vec3b>(i,j)[2]) / 3;
				result.at<Vec3b>(i,j)[0] = intense;
				result.at<Vec3b>(i,j)[1] = intense;
				result.at<Vec3b>(i,j)[2] = intense;
			}
		}
		return result;
	}
	Mat LightnessFilter() {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (Find_Max(result.at<Vec3b>(i, j)[0], result.at <Vec3b>(i, j)[1], result.at <Vec3b>(i, j)[2]) + Find_Min(result.at<Vec3b>(i, j)[0], result.at <Vec3b>(i, j)[1], result.at <Vec3b>(i, j)[2])) / 2;
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		return result;
	}
	Mat LuminosityFilter() {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (result.at<Vec3b>(i, j)[0] * 0.21 + result.at<Vec3b>(i, j)[1] * 0.72 + result.at<Vec3b>(i, j)[2] * 0.07);
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		return result;
	}
	Mat PhotoshopFilter() {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (result.at<Vec3b>(i, j)[0] * 0.3 + result.at<Vec3b>(i, j)[1] * 0.59 + result.at<Vec3b>(i, j)[2] * 0.11);
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		return result;
	}
};