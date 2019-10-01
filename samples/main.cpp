#include "filter.cpp"
#include <fstream>
#include <conio.h>
const char* cmdOptions =
"{ i  image         | <none> | image to process        }"
"{ q ? help usage   | <none> | print help message      }";


int main(int argc,char** argv) {
	
	CommandLineParser parser(argc, argv, cmdOptions);
	string path_to_image(parser.get<String>("image"));
	Mat image = imread("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU\\picture\\cat.jpg");
	if (image.empty()) {
		cout << "Failed load image" << endl;
		return -1;
	}
	Filter fil(image);
	Mat new_image = image.clone();
	cvtColor(image, new_image, COLOR_BGR2GRAY);
	int curr = 1;
	string nf[9] = { "Opencv grey", "Average", "Lightness", "Luminosity", "Photoshop","ITU_R", "Max", "Min", "Noname" };//namef filter
	Mat picture[9];
	picture[0] = new_image;
	picture[1] = fil.AverageFilter();
	picture[2] = fil.LightnessFilter();
	picture[3] = fil.LuminosityFilter();
	picture[4] = fil.PhotoshopFilter();
	picture[5] = fil.ITU_R();
	picture[6] = fil.Max();
	picture[7] = fil.Min();
	picture[8] = fil.NoName();
	int key = 10;
	namedWindow(nf[0], WINDOW_AUTOSIZE);
	imshow(nf[0], picture[0]);
	waitKey(1);
	bool first = true;
	while (key!=27) 
	{
		if (first) {
			namedWindow(nf[1], WINDOW_AUTOSIZE);
			imshow(nf[1], picture[1]);
			first = false;
			waitKey(1);
		}
		key = _getch();
		key = _getch();
		if (key ==75 && curr > 1)
		{
			destroyWindow(nf[curr]);
			curr--;
			cout << curr << endl;
		}
		else if (key == 77 && curr < 8)
		{
			destroyWindow(nf[curr]);
			curr++;
			cout << curr << endl;
		}
		namedWindow(nf[curr], WINDOW_AUTOSIZE);
		imshow(nf[curr], picture[curr]);
		waitKey(1);
	}		
	destroyAllWindows();
	return 0;
}



