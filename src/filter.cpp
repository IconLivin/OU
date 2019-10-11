#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <random>

using namespace std;
using namespace cv;

int Find_Max_Ch(int x, int y, int z) {
	int n = x > y ? x : y;
	n = n > z ? n : z;
	return n;
}

struct TNode {
	Vec3b color;
	int count;
};

class color_queue {
public:
	TNode mas[3];
	color_queue(int x, int y, int z) {
		mas[0].count = x;
		mas[0].color = { 255, 0, 0 };
		mas[1].count = y;
		mas[1].color = { 0, 255, 0 };
		mas[2].count = z;
		mas[2].color = { 0, 0, 255 };
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				if (mas[j].count > mas[j + 1].count) {
					TNode tmp = mas[j];
					mas[j] = mas[j + 1];
					mas[j + 1] = tmp;
				}
			}
		}
		for (int i = 2; i > 0; i--) {
			mas[i].count -= mas[i - 1].count;
		}

	}
};

int Clamp(int x) {
	int n = x > 0 ? x : 0;
	n = x < 256 ? x : 255;
	return n;
}


Mat Generate_Mask_Gauss(int size_x,int size_y) {
	random_device rd;
	mt19937 gen(rd());
	normal_distribution<> d(20, 1);
	Mat result(size_x, size_y, CV_8UC3);
	srand(time(NULL));
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.at<Vec3b>(i, j) = 0;
		}
	}
	for (int i = 0; i < size_x * size_y * 0.8; i++) {
		int x = rand() % size_x;
		int y = rand() % size_y;
		result.at<Vec3b>(x, y)[0] = result.at < Vec3b>(x, y)[1] = result.at < Vec3b>(x, y)[2] = abs(d(gen));
	}
	return result;
}

Mat Generate_Mask_Gamma(int size_x, int size_y) {
	random_device rd;
	mt19937 gen(rd());
	gamma_distribution<> d(60, 0.5);
	Mat result(size_x, size_y, CV_8UC3);
	srand(time(NULL));
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.at<Vec3b>(i, j) = 0;
		}
	}
	for (int i = 0; i < size_x * size_y * 0.8; i++) {
		int x = rand() % size_x;
		int y = rand() % size_y;
		result.at<Vec3b>(x, y)[0] = result.at < Vec3b>(x, y)[1] = result.at < Vec3b>(x, y)[2] = abs(d(gen));
	}
	return result;
}

Mat Build_Gist(Mat img) {
	int Gist_R[256];
	int Gist_G[256];
	int Gist_B[256];
	for (int i = 0; i < 256; i++)
	{
		Gist_R[i] = 0;
		Gist_G[i] = 0;
		Gist_B[i] = 0;
	}
	int Max_value = 0;;
	for (int i = 0; i < img.rows; i++) { 
		for (int j = 0; j < img.cols; j++) {
			Gist_R[img.at<Vec3b>(i, j)[0]]++;
			Gist_G[img.at<Vec3b>(i, j)[1]]++;
			Gist_B[img.at<Vec3b>(i, j)[2]]++;
		}
	}
	for (int i = 0; i < 256; i++) {
		if (Gist_R[i] > Max_value)Max_value = Gist_R[i];
		if (Gist_G[i] > Max_value)Max_value = Gist_G[i];
		if (Gist_B[i] > Max_value)Max_value = Gist_B[i];
	}
	while (Max_value > 700) {
		for (int i = 0; i < 256; i++) {
			Gist_R[i] /= 2;
			Gist_G[i] /= 2;
			Gist_B[i] /= 2;
		}
		Max_value /= 2;
	}
	Mat result(Max_value + 20, 1290, CV_8UC3);
	cout << Max_value << endl << result.rows << endl;
	int counter = 0;
	for (int i = 2; i < result.cols; i+=5) {
		color_queue c(Gist_R[counter], Gist_G[counter], Gist_B[counter]);
		int cc = 0;
		for (int j = result.rows-1; j>result.rows-Find_Max_Ch(Gist_R[counter],Gist_G[counter],Gist_B[counter]);) {
			int k = 0;
			while (k < c.mas[cc].count) {
				for (int i1 = 0; i1 < 4; i1++) {
					result.at<Vec3b>(j, i + i1) = c.mas[cc].color;
				}
				k++;
				j--;
			}
			cc++;
		}
		if (++counter == 256)break;
	}
	return result;
}

Mat Build_Gray_Hist(Mat img) {
	int Gist[256];
	for (int i = 0; i < 256; i++)Gist[i] = 0;
	int Max_value = 0;;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			Gist[img.at<uchar>(i, j)]++;
		}
	}
	for (int i = 0; i < 256; i++) {
		if (Gist[i] > Max_value)Max_value = Gist[i];
	}
	while (Max_value > 700) {
		for (int i = 0; i < 256; i++) {
			Gist[i] /= 2;
		}
		Max_value /= 2;
	}
	Mat result(Max_value + 20, 1290, CV_8UC1);
	cout << Max_value << endl << result.rows << endl;
	int counter = 0;
	for (int i = 2; i < result.cols; i += 5) {
		for (int j = result.rows - 1; j > result.rows - Gist[counter]; j--) {
			for (int i1 = 0; i1 < 4; i1++) {
				result.at<uchar>(j, i + i1) = 0;
			}
		}
		if (++counter == 256)break;
	}
	return result;
}

Mat Worse_Img_Gauss(Mat img) {
	Mat result = img.clone();
	Mat mask = Generate_Mask_Gauss(result.rows, result.cols);
	imshow("Win", Build_Gist(mask));
	waitKey();
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.at<Vec3b>(i, j) += mask.at<Vec3b>(i, j);
		}
	}
	return result;
}

Mat Worse_Img_Gamma(Mat img) {
	Mat result = img.clone();
	Mat mask = Generate_Mask_Gamma(result.rows, result.cols);
	imshow("Win", Build_Gist(mask));
	waitKey();
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.at<Vec3b>(i, j) += mask.at<Vec3b>(i, j);
		}
	}
	return result;
}