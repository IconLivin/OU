#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <vector>

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

void ClearFile(ofstream& out,string path_file)
{
	/*out.open("D:\\GithubProjects\\Computer Graphics\\OU\\info.txt");*/
	out.open(path_file);
	if (!out.is_open())
		cout << "Error open file " << path_file << endl;
out.close();
}

uchar MaxDiff(Mat diff)
{
	int max = 0;
	for (int i = 0; i < diff.rows; i++)
		for (int j = 0; j < diff.cols; j++)
			max = max < diff.at<uchar>(i, j) ? diff.at<uchar>(i, j) : max;
	return max;
}

int Out_Threshold(Mat image) {
	uchar min = image.at<uchar>(0, 0);
	uchar max = image.at<uchar>(0, 0);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			min = min > image.at<uchar>(i, j) ? image.at<uchar>(i, j) : min;
			max = max < image.at<uchar>(i, j) ? image.at<uchar>(i, j) : max;
		}
	}
	int hist_size = max - min + 1;
	int* hist = new int[hist_size];

	for (int i = 0; i < hist_size; i++) {
		hist[i] = 0;
	}

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			hist[image.at<uchar>(i, j) - min]++;
		}
	}

	int m = 0;
	int n = 0;

	for (int i = 0; i <= max - min; i++) {
		m += i * hist[i];
		n += hist[i];
	}

	float maxSigma = -1;
	int threshold = 0;

	int alpha1 = 0;
	int beta1 = 0;

	for (int i = 0; i < max - min; i++) {
		alpha1 += i * hist[i];
		beta1 += hist[i];
		float w1 = (float)beta1 / n;
		float a = (float)alpha1 / beta1 - (float)(m - alpha1) / (n - beta1);
		float sigma = w1 * (1 - w1) * a * a;
		if (sigma > maxSigma) {
			maxSigma = sigma;
			threshold = i;
		}
	}


	return threshold += min;
}

Mat hist_intensity(Mat img, int porog) {
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
		if (gist_intensity[i] > Max_value)
			Max_value = gist_intensity[i];
	while (Max_value > 700) {
		for (int i = 0; i < 256; i++) {
			gist_intensity[i] /= 2;
		}
		Max_value /= 2;
	}
	Point p(0, Max_value);
	Mat result(Max_value, 1290, CV_8UC3);
	for (int i = 0; i < 256; i++) {
		if (gist_intensity[i] > 1)
		{
			line(result, p, Point(p.x, result.rows - gist_intensity[i]), Scalar(255, 255, 255), 2);
			p.x += 5;
		}
	}
	line(result, Point(porog * 5, 5), Point(porog * 5 + 2, Max_value), Scalar(0, 0, 255), 5);
	return result;
}

Mat Make_Otsu(Mat source,int &tmp) {
	Mat gray_s;
	GaussianBlur(source, source, Size(3, 3), 0);
	cvtColor(source, gray_s, COLOR_BGR2GRAY);
	int threshold = Out_Threshold(gray_s);
	tmp = threshold;
	bool flag = threshold > 127 ? true : false;
	for (int i = 0; i < gray_s.rows; i++) {
		for (int j = 0; j < gray_s.cols; j++) {
			if (flag) {
				gray_s.at<uchar>(i, j) = gray_s.at<uchar>(i, j) < threshold ? 255 : 0;
			}
			else {
				gray_s.at<uchar>(i, j) = gray_s.at<uchar>(i, j) > threshold ? 255 : 0;
			}
		}
	}
	return gray_s;
}

Mat Make_Otsu_Main(Mat source,int &porog) {
	Mat gray_s = Make_Otsu(source,porog);
	for (int i = 0; i < source.rows; i++) {
		for (int j = 0; j < source.cols; j++) {
			source.at<Vec3b>(i, j) = gray_s.at<uchar>(i, j) == 255 ? Vec3b(0, 255, 0) : source.at<Vec3b>(i, j);
		}
	}
	return source;
}

int Second_Iter(Mat& img, int x, int y, Moments& m, double x_lined, double y_lined) {
	if (x < 0 || y < 0 || x >= img.rows || y >= img.cols)return 0;
	if (img.at<uchar>(x, y) != 254) {
		return 0;
	}
	m.mu02 += pow((x - x_lined), 2);
	m.mu03 += pow((x - x_lined), 3);
	m.mu11 += (x - x_lined) * (y - y_lined);
	m.mu12 += (x - x_lined) * (y - y_lined) * (x - x_lined);
	m.mu20 += (y - y_lined) * (y - y_lined);
	m.mu21 += (x - x_lined) * (y - y_lined) * (y - y_lined);
	m.mu30 += pow((y - y_lined), 3);
	img.at<uchar>(x, y) = 0;
	Second_Iter(img, x + 1, y, m, x_lined, y_lined);
	Second_Iter(img, x - 1, y, m, x_lined, y_lined);
	Second_Iter(img, x, y + 1, m, x_lined, y_lined);
	Second_Iter(img, x, y - 1, m, x_lined, y_lined);
}

int Fill_Img(Mat& img, int x, int y, Moments& m) {
	if (x < 0 || y < 0 || x >= img.rows || y >= img.cols)return 0;
	if (img.at<uchar>(x, y) != 255)return 0;
	m.m00++;
	m.m10 += y;
	m.m01 += x;
	img.at<uchar>(x, y) = 254;
	Fill_Img(img, x + 1, y, m);
	Fill_Img(img, x - 1, y, m);
	Fill_Img(img, x, y + 1, m);
	Fill_Img(img, x, y - 1, m);
}

int Find_Regions(Mat img, vector<Moments>& mom, vector<vector<double>>& hum) {
	Mat clone = img.clone();
	int count = 0;
	vector<Moments> moments;
	for (int i = 0; i < clone.rows; ++i) {
		for (int j = 0; j < clone.cols; ++j) {
			if (clone.at<uchar>(i, j) == 255) {
				Moments curr;
				count++;
				Fill_Img(clone, i, j, curr);
				
				double y_lined = curr.m10 / curr.m00;
				double x_lined = curr.m01 / curr.m00;
				Second_Iter(clone, i, j, curr, x_lined, y_lined);
				curr.nu02 = curr.mu02 / pow(curr.m00, 2);
				curr.nu03 = curr.mu03 / pow(curr.m00, 2.5);
				curr.nu11 = curr.mu11 / pow(curr.m00, 2);
				curr.nu12 = curr.mu12 / pow(curr.m00, 2.5);
				curr.nu20 = curr.mu20 / pow(curr.m00, 2);
				curr.nu21 = curr.mu21 / pow(curr.m00, 2.5);
				curr.nu30 = curr.mu30 / pow(curr.m00, 2.5);
				moments.push_back(curr);
			}
		}
	}
	vector<vector<double>> hu;
	for (int i = 0; i < moments.size(); ++i) {
		double humoments[7];
		humoments[0] = moments[i].nu20 + moments[i].nu02;
		humoments[1] = pow(moments[i].nu20 - moments[i].nu02, 2) + 4 * pow(moments[i].nu11, 2);
		humoments[2] = pow(moments[i].nu30 - 3 * moments[i].nu12, 2) + (3 * moments[i].nu21 - moments[i].nu03, 2);
		humoments[3] = pow(moments[i].nu30 + moments[i].nu12, 2) + pow(moments[i].nu21 + moments[i].nu03, 2);
		humoments[4] = (moments[i].nu30 - 3 * moments[i].nu12) * (moments[i].nu30 + moments[i].nu12) * (pow(moments[i].nu30 + moments[i].nu12, 2) - 3 * pow(moments[i].nu21 + moments[i].nu03, 2)) + (3 * moments[i].nu21 - moments[i].nu03) * (moments[i].nu21 + moments[i].nu03) * (3 * pow(moments[i].nu30 + moments[i].nu12, 2) - pow(moments[i].nu21 + moments[i].nu03, 2));		
		humoments[5] = (moments[i].nu20 - moments[i].nu02) * (pow(moments[i].nu30 + moments[i].nu12, 2) - pow(moments[i].nu21 - moments[i].nu03, 2)) + 4 * moments[i].nu11 * (moments[i].nu30 + moments[i].nu12) * (moments[i].nu21 + moments[i].nu03);
		humoments[6] = (3 * moments[i].nu21 - moments[i].nu03) * (moments[i].nu21 + moments[i].nu03) * (3 * pow(moments[i].nu30 + moments[i].nu12, 2) - pow(moments[i].nu21 + moments[i].nu03, 2)) - (moments[i].nu30 - 3 * moments[i].nu12) * (moments[i].nu21 + moments[i].nu03) * (3 * pow(moments[i].nu30 + moments[i].nu12, 2) - pow(moments[i].nu21 + moments[i].nu03, 2));
		vector<double> h;
		for (int j = 0; j < 7; ++j) {
			cout << humoments[j] << " ";
			h.push_back(humoments[j]);
		}
		cout << endl;
		hu.push_back(h);
	}
	mom = moments;
	hum = hu;
	return count;
}

