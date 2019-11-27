#pragma comment(linker, "/STACK:4294967296")

#include "filter.cpp"
#include <conio.h>
const char* cmdOptions =
"{ i  image         | <none> | image to process        }"
"{ q ? help usage   | <none> | print help message      }";


void main(int argc,char** argv) {
	
	CommandLineParser parser(argc, argv, cmdOptions);
	//string path_to_image(parser.get<String>("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU-build\\samples\\lobachevsky.jpg"));
	
	Mat image = imread("../../OU/picture/lob.jpg");
	int porog;
	namedWindow("Win1", WINDOW_NORMAL);
	namedWindow("adgadg", WINDOW_NORMAL);
	namedWindow("Porog", WINDOW_NORMAL);
	Mat por = Make_Otsu(image, porog);
	imshow("Win1", image);
	imshow("adgadg", por);
	imshow("Porog", hist_intensity(image, porog));
	FindCountours(por);
	cout << "Regions:" << Find_Regions(por) << endl;
	waitKey();
}



