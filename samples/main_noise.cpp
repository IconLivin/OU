#include "histogram.cpp"
#include "noise.cpp"
#include "filter.cpp"
//#include <conio.h>
const char* cmdOptions =
"{ i  image         | <none> | image to process        }"
"{ q ? help usage   | <none> | print help message      }";



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
//	Mat dst(image.rows, image.cols, CV_8UC1);
//	cvtColor(image, dst, COLOR_BGR2GRAY);
//	Mat noise(gauss_noise(image.rows,image.cols,false));
//	imshow("Image", image);
//	imshow("Noise", noise);
//	imshow("Hist", hist_intensity(dst));
//	cout << dst.rows << " " << dst.cols << endl;
//	cout << image.rows << " " << image.cols << endl;
//	imshow("Result", createNoise(noise,dst));
//	imshow("Hist noise", hist_intensity(noise));
//	imshow("Hist result", hist_intensity(createNoise(noise, dst)));
//	waitKey();
//	return 0;
//}

////Colorfull
int main(int argc,char** argv) {
	
	CommandLineParser parser(argc, argv, cmdOptions);
	//string path_to_image(parser.get<String>("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU-build\\samples\\lobachevsky.jpg"));
	Mat image = imread("../../OU/picture/lob.jpg");
	if (image.empty()) {
		cout << "Error load image" << endl;
		return -1;
	}
	string labels_noise[2] = { "Gauss","Gamma" };
	string labels_blur[2] = {"Gauss", "Median"};
	Mat noise[2];
	int key = 0;
	int curr = 0;
	noise[0] = Generate_Mask_Gauss(image.rows, image.cols, 0.3);
	noise[1] = Generate_Mask_Gamma(image.rows, image.cols, 0.3);
	while (key != 27) {//esc
		key = waitKey();
		cout << key << endl;
		switch (key)
		{
		case 52: {//numpad4
			if (curr > 0)curr--;
			system("cls");
			cout <<"Noise "<< labels_noise[curr] << endl;
			cout << "Blur"<<labels_blur[curr] << endl;
			break;
		}
		case 54: {//numpad6
			if (curr < 7)curr++;
			system("cls");
			cout << "Noise " << labels_noise[curr] << endl;
			cout << "Blur" << labels_blur[curr] << endl;
			break;
		}
		}
		namedWindow("Image", WINDOW_NORMAL);
		namedWindow("Noise", WINDOW_NORMAL);
		namedWindow("Noise image", WINDOW_NORMAL);
		namedWindow("Image after blur", WINDOW_NORMAL);
		namedWindow("Hist image", WINDOW_NORMAL);
		namedWindow("Hist noise", WINDOW_NORMAL);
		namedWindow("Hist noise image", WINDOW_NORMAL);
		namedWindow("Hist after blur", WINDOW_NORMAL);
		imshow("Image", image);
		imshow("Noise", noise[curr]);
		imshow("Noise image", createNoise(image, noise[curr]));
		imshow("Image after blur", CreateBlur(labels_blur[curr][0], createNoise(image, noise[curr])));
		imshow("Hist image", Build_Gist(image));
		imshow("Hist noise", Build_Gist(noise[curr],1));
		imshow("Hist after blur", Build_Gist(CreateBlur(labels_blur[curr][0], createNoise(image, noise[curr]))));
		imshow("Hist noise image", Build_Gist(createNoise(image, noise[curr])));

	//	waitKey(1);
	//}
	//destroyAllWindows();
	return 0;
}



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