#pragma once
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iomanip>
#include <fstream>
#include "noise.cpp"
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


Mat Build_Gist(Mat img, bool flag = 0) {
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
			if (flag == 0) {
				Gist_R[img.at<Vec3b>(i, j)[0]]++;
				Gist_G[img.at<Vec3b>(i, j)[1]]++;
				Gist_B[img.at<Vec3b>(i, j)[2]]++;
			}
			else if (img.at<Vec3b>(i, j)[0] != 0)
			{
				int c = img.at<Vec3b>(i, j)[0];
				Gist_R[img.at<Vec3b>(i, j)[0]]++;
				Gist_G[img.at<Vec3b>(i, j)[1]]++;
				Gist_B[img.at<Vec3b>(i, j)[2]]++;
			}
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
	int counter = 0;
	for (int i = 2; i < result.cols; i += 5) {
		color_queue c(Gist_R[counter], Gist_G[counter], Gist_B[counter]);
		int cc = 0;
		for (int j = result.rows - 1; j > result.rows - Find_Max_Ch(Gist_R[counter], Gist_G[counter], Gist_B[counter]);) {
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

Mat hist_intensity(Mat img) {
	int gist_intensity[256];
	for (int i = 0; i < 256; i++)
		gist_intensity[i] = 0;
	int Max_value = 0;;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			gist_intensity[img.at<uchar>(i, j)]++;
		}
	}
	for (int i = 0; i < 256; i++)
		if (gist_intensity[i] > Max_value)Max_value = gist_intensity[i];
	while (Max_value > 700) {
		for (int i = 0; i < 256; i++) {
			gist_intensity[i] /= 2;
		}
		Max_value /= 2;
	}
	Point p(0, Max_value);
	Mat result(Max_value, 1290, CV_8UC1);
	cout << Max_value << endl << result.rows << endl;
	for (int i = 0; i < 256; i++) {
		if (gist_intensity[i] > 1)
		{
			line(result, p, Point(p.x, result.rows - gist_intensity[i]), Scalar(255, 255, 255), 2);
			p.x += 5;
		}
	}
	return result;
}

const float PI = 3.14159265358979323846;

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

Mat Generate_Mask_Gamma(int size_x, int size_y,double pr=0.3) {
	random_device rd;
	mt19937 gen(rd());
	gamma_distribution<> d(9, 0.5);
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

Vec3b Get_Color_Gauss(float** kernel, Mat img, int size, int x, int y) {
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
			result.at<Vec3b>(i, j) = Get_Color_Gauss(kernel, img, 2 * n + 1, i, j);
		}
	}
	return result;
}

int median(vector <int> v) 
{
<<<<<<< HEAD
	
	sort(v.begin(), v.end(), greater<int>());
	return v[v.size()/2];

}

Vec3b Get_Color_Median(Mat img, int size, int x, int y) {
	Vec3b color = 0;
	int x1 = 0, y1 = 0;
	vector <int > b, g, r;
	for (int i = x; i < size + x; i++) {
		y1 = 0;
		for (int j = y; j < size + y; j++) {
			b.push_back((int)img.at <Vec3b>(i, j)[0]);
			g.push_back((int)img.at <Vec3b>(i, j)[1]);
			r.push_back((int)img.at <Vec3b>(i, j)[2]);
			y1++;
		}
	}
	Mat dst(src.rows, src.cols,CV_8UC3);
	if (flag)
	{
		switch (f) {
		case 'G':
			GaussianBlur(src, dst, Size(3, 3), 0);
			break;
		case 'M':
			medianBlur(src,dst,3);
		}
		x1++;
	}
	color[0] = median(b);
	color[1] = median(g);
	color[2] = median(r);
	return color;
}

Mat median_filter(Mat img)
{
	const int n = 3;
	Mat result=img.clone();
	for (int i = 0; i < result.rows - n; i++) {
		for (int j = 0; j < result.cols - n; j++)
		{
			result.at<Vec3b>(i, j) = Get_Color_Median(result, n, i, j);

		case 'G':
			Gauss_Filter(src);
			break;
		case 'M':
			median_filter(src);
		}
	}
	return result;
}



