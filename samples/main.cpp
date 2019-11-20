#pragma comment(linker, "/STACK:1073741824")

#include "filter.cpp"
#include <conio.h>
const char* cmdOptions =
"{ i  image         | <none> | image to process        }"
"{ q ? help usage   | <none> | print help message      }";


void main(int argc,char** argv) {
	
	CommandLineParser parser(argc, argv, cmdOptions);
	//string path_to_image(parser.get<String>("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU-build\\samples\\lobachevsky.jpg"));
	Mat image = imread("../../OU/picture/4.jpg");
	imshow("Win1", image);
	imshow("adgadg", Make_Otsu(image));

	cout << "Regions:" << Find_Regions(Make_Otsu(image)) << endl;
	waitKey();
}



