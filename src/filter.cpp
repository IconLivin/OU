#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iomanip>
#include <fstream>
#include <conio.h>

using namespace std;
using namespace cv;

Mat Build_Gist(Mat img) {
	int Gist[256];
	for (int i = 0; i < 256; i++)Gist[i] = 0;
	int Max_value = 0;;
	for (int i = 0; i < img.rows; i++) { 
		for (int j = 0; j < img.cols; j++) {
			Gist[img.at<Vec3b>(i, j)[0]]++;
			Gist[img.at<Vec3b>(i, j)[1]]++;
			Gist[img.at<Vec3b>(i, j)[2]]++;
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
	cout << Max_value << endl << result.cols << endl;
	int counter = 0;
	for (int i = 2; i < result.cols; i+=5) {
		for (int j = result.rows-1; j>result.rows-Gist[counter]; j--) {
			for (int i1 = 0; i1 < 4; i1++) {
				result.at<uchar>(j, i + i1) = 0;
			}
		}
		if (++counter == 256)break;
	}
	return result;
}