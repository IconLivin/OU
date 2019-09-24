#include "filter.cpp"
const char* cmdOptions =
"{ i  image         | <none> | image to process        }"
"{ q ? help usage   | <none> | print help message      }";


void main(int argc,char** argv) {
	
	CommandLineParser parser(argc, argv, cmdOptions);
	string path_to_image(parser.get<String>("image"));
	Mat image = imread("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU-build\\samples\\lobachevsky.jpg");
	Filter fil(image);
	Mat new_image = image.clone();
	Mat g_f = fil.AverageFilter();
	Mat l_f = fil.LightnessFilter();
	Mat lum_f = fil.LuminosityFilter();
	Mat p_f = fil.PhotoshopFilter();
	cvtColor(image, new_image, COLOR_RGB2GRAY);
	imshow("Gray Filter", new_image);
	imshow("Average Filter", g_f);
	imshow("Lightness Filter", l_f);
	imshow("Luminosity Filter", lum_f);
	imshow("Photoshop Filter", p_f);
	waitKey(0);
}



