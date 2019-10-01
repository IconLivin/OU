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

class All_Fill {
protected:
	int cc;
	Mat img1, img2;
public:
	All_Fill() { cc = 0; }
	void Count_CC(Mat orig) {
		int res = 0;
		for (int i = 0; i < orig.rows; i++) {
			for (int j = 0; j < orig.cols; j++) {
				res += abs((int)orig.at<uchar>(i, j) - (int)img1.at<Vec3b>(i, j)[0]);
			}
		}
		cc = abs(res / (orig.rows * orig.cols));
	};
	int Get_CC() { return cc; }

	void Make_Problems(Mat orig) {
		Mat result = img1.clone();
		for (int i = 0; i < orig.rows; i++) {
			for (int j = 0; j < orig.cols; j++) {
				if (abs((int)orig.at<uchar>(i, j) - (int)img1.at<Vec3b>(i, j)[0]) > cc) {
					result.at<Vec3b>(i, j)[2] = 255;
					result.at<Vec3b>(i, j)[1] = 0;
					result.at<Vec3b>(i, j)[0] = 0;
				}
			}
		}
		img2 = result.clone();
	};
	Mat Get_Mat1() { return img1; }
	Mat Get_Mat2() { return img2; }
};

class Avg_Fill :public All_Fill {
public:
	Avg_Fill(Mat img) {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (result.at<Vec3b>(i, j)[0] + result.at<Vec3b>(i, j)[1] + result.at<Vec3b>(i, j)[2]) / 3;
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		img1 = result;
	}
};

class Light_Fill :public All_Fill {
public:
	Light_Fill(Mat img) {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (Find_Max(result.at<Vec3b>(i, j)[0], result.at <Vec3b>(i, j)[1], result.at <Vec3b>(i, j)[2]) + Find_Min(result.at<Vec3b>(i, j)[0], result.at <Vec3b>(i, j)[1], result.at <Vec3b>(i, j)[2])) / 2;
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		img1 = result.clone();
	}
};

class Lum_Fill :public All_Fill {
public:
	Lum_Fill(Mat img) {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (result.at<Vec3b>(i, j)[0] * 0.21 + result.at<Vec3b>(i, j)[1] * 0.72 + result.at<Vec3b>(i, j)[2] * 0.07);
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		img1 = result.clone();
	}
};

class Ph_Fill :public All_Fill {
public:
	Ph_Fill(Mat img) {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (result.at<Vec3b>(i, j)[0] * 0.3 + result.at<Vec3b>(i, j)[1] * 0.59 + result.at<Vec3b>(i, j)[2] * 0.11);
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		img1 = result.clone();
	}
};

class ITU_R_Fill :public All_Fill {
public:
	ITU_R_Fill(Mat img) {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (result.at<Vec3b>(i, j)[0] * 0.2126 + result.at<Vec3b>(i, j)[1] * 0.7152 + result.at<Vec3b>(i, j)[2] * 0.0722);
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		img1 = result.clone();
	}
};

class Max_Fill :public All_Fill {
public:
	Max_Fill(Mat img) {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (Find_Max(result.at<Vec3b>(i, j)[0], result.at<Vec3b>(i, j)[1], result.at<Vec3b>(i, j)[2]));
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		img1 = result.clone();
	}
};

class Min_Fill :public All_Fill {
public:
	Min_Fill(Mat img) {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (Find_Min(result.at<Vec3b>(i, j)[0], result.at<Vec3b>(i, j)[1], result.at<Vec3b>(i, j)[2]));
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		img1 = result.clone();
	}
};

class NN_Fill :public All_Fill {
public:
	NN_Fill(Mat img) {
		Mat result = img.clone();
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				int intense = (result.at<Vec3b>(i, j)[0] * 0.2952 + result.at<Vec3b>(i, j)[1] * 0.5547 + result.at<Vec3b>(i, j)[2] * 0.148);
				result.at<Vec3b>(i, j)[0] = intense;
				result.at<Vec3b>(i, j)[1] = intense;
				result.at<Vec3b>(i, j)[2] = intense;
			}
		}
		img1 = result.clone();
	}
};