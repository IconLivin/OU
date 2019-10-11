#include "filter.cpp"
#include <conio.h>
const char* cmdOptions =
"{ i  image         | <none> | image to process        }"
"{ q ? help usage   | <none> | print help message      }";


void main(int argc,char** argv) {
	
	CommandLineParser parser(argc, argv, cmdOptions);
	//string path_to_image(parser.get<String>("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU-build\\samples\\lobachevsky.jpg"));
	Mat image = imread("../../OU/picture/lob.jpg");
	Mat worse_Gauss = Worse_Img_Gauss(image);
	Mat worse_Gamma = Worse_Img_Gamma(image);
	imshow("Worse Gauss", worse_Gauss);
	imshow("Worse Gamma", worse_Gamma);
	imshow("Good", image);
	imshow("Good hist", Build_Gist(image));
	imshow("worse Gauss hist", Build_Gist(worse_Gauss));
	imshow("worse Gamma hist", Build_Gist(worse_Gamma));
	waitKey();
}



