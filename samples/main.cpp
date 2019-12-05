#pragma comment(linker, "/STACK:4294967296")

#include "filter.cpp"
#include <conio.h>
const char* cmdOptions =
"{ i  image         | <none> | image to process        }"
"{ q ? help usage   | <none> | print help message      }";


void main(int argc,char** argv) {
	
	CommandLineParser parser(argc, argv, cmdOptions);
	//string path_to_image(parser.get<String>("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU-build\\samples\\lobachevsky.jpg"));
	
	Mat image = imread("../../OU/picture/5.jpg");
	int porog;
	namedWindow("Win1", WINDOW_NORMAL);
	namedWindow("adgadg", WINDOW_NORMAL);
	namedWindow("Porog", WINDOW_NORMAL);
	Mat por = Make_Otsu(image, porog);
	imshow("Win1", image);
	imshow("Porog", hist_intensity(image, porog));
	vector<Moments> moments;
	vector<vector<double>> hu;
	cout << Find_Regions(por,moments,hu) << endl;

	for (int i = 0; i < moments.size(); ++i) {
		putText(por,to_string(i + 1), Point(moments[i].m10 / moments[i].m00, moments[i].m01 / moments[i].m00), FONT_ITALIC, 0.5, uchar(150));
		cout << "Object " + to_string(i + 1) + " size:" << moments[i].m00 << endl;
		cout << "Center of object " + to_string(i + 1) + ":" << Point(moments[i].m10 / moments[i].m00, moments[i].m01 / moments[i].m00) << endl;
	}
	for (int i = 0; i < hu.size(); ++i) {
		cout << "Hu vector " + to_string(i + 1) + ":" << endl;
		for (auto j = hu[i].begin(); j != hu[i].end(); ++j) {
			cout << *j << " ";
		}
		cout << endl;
	}
	imshow("adgadg", por);

	waitKey();
}



