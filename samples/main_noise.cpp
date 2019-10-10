#include "histogram.cpp"
#include "noise.cpp"
#include <conio.h>
const char* cmdOptions =
"{ i  image         | <none> | image to process        }"
"{ q ? help usage   | <none> | print help message      }";

///BLAck and White


int main(int argc,char** argv) {
	
	CommandLineParser parser(argc, argv, cmdOptions);
	namedWindow("Noise", WINDOW_NORMAL);
	namedWindow("Hist", WINDOW_NORMAL);
	namedWindow("Image", WINDOW_NORMAL);
	namedWindow("Result", WINDOW_NORMAL);
	namedWindow("Hist result", WINDOW_NORMAL);
	namedWindow("Hist noise", WINDOW_NORMAL);
	//string path_to_image(parser.get<String>("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU-build\\samples\\lobachevsky.jpg"));
	Mat image = imread("../../OU/picture/lob.jpg");
	if (image.empty()) {
		cout << "Error load image" << endl;
		return -1;
	}
	Mat dst(image.rows, image.cols, CV_8UC1);
	cvtColor(image, dst, COLOR_BGR2GRAY);
	Mat noise(gauss_noise(image.rows,image.cols,false));
	imshow("Image", image);
	imshow("Noise", noise);
	imshow("Hist", hist_intensity(dst));
	cout << dst.rows << " " << dst.cols << endl;
	cout << image.rows << " " << image.cols << endl;
	imshow("Result", createNoise(noise,dst));
	imshow("Hist noise", hist_intensity(noise));
	imshow("Hist result", hist_intensity(createNoise(noise, dst)));
	waitKey();
	return 0;
}

////Colorfull
//int main(int argc,char** argv) {
//	
//	CommandLineParser parser(argc, argv, cmdOptions);
//	namedWindow("Noise", WINDOW_NORMAL);
//	namedWindow("Hist", WINDOW_NORMAL);
//	namedWindow("Image", WINDOW_NORMAL);
//	namedWindow("Result", WINDOW_NORMAL);
//	namedWindow("Hist result", WINDOW_NORMAL);
//	namedWindow("Hist noise", WINDOW_NORMAL);
//	//string path_to_image(parser.get<String>("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU-build\\samples\\lobachevsky.jpg"));
//	Mat image = imread("../../OU/picture/lob.jpg");
//	if (image.empty()) {
//		cout << "Error load image" << endl;
//		return -1;
//	}
//	Mat noise(gauss_noise(image.rows,image.cols,1));
//	imshow("Image", image);
//	imshow("Hist", Build_Gist(image));
//	imshow("Noise", noise);
//	imshow("Result", createNoise(noise,image));
//	imshow("Hist noise", Build_Gist(noise));
//	imshow("Hist result", Build_Gist(createNoise(noise, image)));
//	waitKey();
//	return 0;
//}



//
//#include <iostream>
//#include <iomanip>
//#include <string>
//#include <map>
//#include <random>
//#include <cmath>
//int main()
//{
//	std::random_device rd;
//	std::mt19937 gen(rd());
//
//	// values near the mean are the most likely
//	// standard deviation affects the dispersion of generated values from the mean
//	//for (int i = 0; i < 100; i++)
//	//	i++;
//	std::normal_distribution<> d(20, 2);
//	//for (int i = 0; i < 50; i++)
//	//	std::cout << d(gen) << std::endl;
//	std::map<int, int> hist;
//	for (int n = 0; n < 10000; ++n) {
//		++hist[std::round(d(gen))];
//	}
//	for (auto p : hist) {
//		std::cout << std::fixed << std::setprecision(1) << std::setw(2)
//			<< p.first << ' ' << std::string(p.second / 200, '*') << '\n';
//	}
//	return 0;
//}