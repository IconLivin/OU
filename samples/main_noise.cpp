#include "histogram.cpp"
#include "noise.cpp"
#include "filter.cpp"
//#include <conio.h>
const char* cmdOptions =
"{ i  image         | <none> | image to process        }"
"{ q ? help usage   | <none> | print help message      }";

int main(int argc, char** argv) {
	CommandLineParser parser(argc, argv, cmdOptions);
	//string path_to_image(parser.get<String>("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU-build\\samples\\lobachevsky.jpg"));
	Mat image = imread("../../OU/picture/lob.jpg");
	if (image.empty()) {
		cout << "Error load image" << endl;
		return -1;
	}
	Mat w_G_img = Worse_Img_Gauss(image);
	imshow("Img", image);
	imshow("Gauss", w_G_img);
	imshow("f_img", Gauss_Filter(w_G_img));
	waitKey();
	//string labels_noise[2] = { "Gauss","Gamma" };
	//string labels_blur[2] = { "Gauss", "Median" };
	//Mat noise[2];
	//int key = 0;
	//int curr = 0;
	//noise[0] = Generate_Mask_Gauss(image.rows, image.cols, 0.3);
	//noise[1] = Generate_Mask_Gamma(image.rows, image.cols, 0.3);
	//while (key != 27) {//esc
	//	key = waitKey();
	//	cout << key << endl;
	//	switch (key)
	//	{
	//	case 52: {//numpad4
	//		if (curr > 0)curr--;
	//		system("cls");
	//		cout << "Noise " << labels_noise[curr] << endl;
	//		cout << "Blur" << labels_blur[curr] << endl;
	//		break;
	//	}
	//	case 54: {//numpad6
	//		if (curr < 7)curr++;
	//		system("cls");
	//		cout << "Noise " << labels_noise[curr] << endl;
	//		cout << "Blur" << labels_blur[curr] << endl;
	//		break;
	//	}
	//	}
	//	namedWindow("Image", WINDOW_NORMAL);
	//	namedWindow("Noise", WINDOW_NORMAL);
	//	namedWindow("Noise image", WINDOW_NORMAL);
	//	namedWindow("Image after blur", WINDOW_NORMAL);
	//	namedWindow("Hist image", WINDOW_NORMAL);
	//	namedWindow("Hist noise", WINDOW_NORMAL);
	//	namedWindow("Hist noise image", WINDOW_NORMAL);
	//	namedWindow("Hist after blur", WINDOW_NORMAL);
	//	imshow("Image", image);
	//	imshow("Noise", noise[curr]);
	//	imshow("Noise image", createNoise(image, noise[curr]));
	//	imshow("Image after blur", CreateBlur(labels_blur[curr][0], createNoise(image, noise[curr])));
	//	imshow("Hist image", Build_Gist(image));
	//	imshow("Hist noise", Build_Gist(noise[curr], 1));
	//	imshow("Hist after blur", Build_Gist(CreateBlur(labels_blur[curr][0], createNoise(image, noise[curr]))));
	//	imshow("Hist noise image", Build_Gist(createNoise(image, noise[curr])));

	//	waitKey(1);
	//}
	//destroyAllWindows();
	return 0;
}



