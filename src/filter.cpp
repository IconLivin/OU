#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>

using namespace std;
using namespace cv;

int Clamp(int a, int b) {
	if (a - b < 0)return 0;
	return a - b;
}

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

int Check_Diff(Mat or, Mat check) {
	int res = 0;
	for (int i = 0; i < check.rows; i++) {
		for (int j = 0; j < check.cols; j++) {
			res += abs((int) or.at<uchar>(i, j) - (int)check.at<Vec3b>(i, j)[0]);
		}
	}
	return abs(res/(or.rows*or.cols));
}

Mat Print_Problems(Mat cv_img, Mat oth_img, int diff,int &missed) {
	Mat result = oth_img.clone();
	for (int i = 0; i < cv_img.rows; i++) {
		for (int j = 0; j < cv_img.cols; j++) {
			if (abs((int)cv_img.at<uchar>(i, j) - (int)oth_img.at<Vec3b>(i, j)[0]) > diff) {
				result.at<Vec3b>(i, j)[2] = 255;
				result.at<Vec3b>(i, j)[1] = 0;
				result.at<Vec3b>(i, j)[0] = 0;
				missed++;
			}
		}
	}
	return result;
}




class Filter {
	Mat img;
public:
	Filter(Mat img1) { img = img1; }
	Mat AverageFilter() {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (result.at<Vec3b>(i, j)[0] + result.at<Vec3b>(i, j)[1] + result.at<Vec3b>(i, j)[2]) / 3;
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
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
	Mat ITU_R() {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (result.at<Vec3b>(i, j)[0] * 0.2126 + result.at<Vec3b>(i, j)[1] * 0.7152 + result.at<Vec3b>(i, j)[2] * 0.0722);
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		return result;
	}

	Mat Max() {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (Find_Max(result.at<Vec3b>(i, j)[0], result.at<Vec3b>(i, j)[1], result.at<Vec3b>(i, j)[2]));
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		return result;
	}

	Mat Min() {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (Find_Min(result.at<Vec3b>(i, j)[0], result.at<Vec3b>(i, j)[1], result.at<Vec3b>(i, j)[2]));
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		return result;
	}

	Mat NoName() {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (result.at<Vec3b>(i, j)[0] * 0.2952 + result.at<Vec3b>(i, j)[1] * 0.5547 + result.at<Vec3b>(i, j)[2] * 0.148);
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		return result;
	}

};