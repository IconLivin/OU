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
	Mat mask = Generate_Mask_Gauss(image.rows, image.cols);
	Mat noise_image = createNoise(image,mask);
	Mat dst;
	Mat our_b = Gauss_Filter(noise_image);
	GaussianBlur(noise_image, dst, Size(3, 3), 0);
	namedWindow("image", WINDOW_NORMAL);
	namedWindow("hist_image", WINDOW_NORMAL);
	namedWindow("hist_noise", WINDOW_NORMAL);
	namedWindow("hist_opencv", WINDOW_NORMAL);
	namedWindow("hist_blur", WINDOW_NORMAL);
	namedWindow("noise_image", WINDOW_NORMAL);
	namedWindow("hist_noise", WINDOW_NORMAL);
	namedWindow("our_blur", WINDOW_NORMAL);
	namedWindow("opencv_blur", WINDOW_NORMAL);
	imshow("image", image);
	imshow("hist_noise", Build_Gist(noise_image));
	imshow("hist_opencv", Build_Gist(dst));
	imshow("hist_blur", Build_Gist(our_b));

	imshow("hist_image",Build_Gist( image));
	imshow("noise_image", noise_image);
	imshow("hist_noise", Build_Gist(mask, 1));
	imshow("our_blur",our_b);
	
	imshow("opencv_blur", dst);
	while(waitKey()!=52);
	cout << "awdwad" << endl;
	mask = Generate_Mask_Gamma(image.rows, image.cols);
	noise_image = createNoise(image, mask);
	our_b = median_filter(noise_image);
	imshow("noise_image", noise_image);
	imshow("hist_noise", Build_Gist(mask, 1));
	imshow("our_blur",median_filter(noise_image));
	medianBlur(noise_image, dst, 3);
	imshow("opencv_blur", dst);

	imshow("hist_opencv", Build_Gist(dst));
	imshow("hist_blur", Build_Gist(our_b));

		waitKey();
		while (waitKey() != 52);
		return 0;
	}

