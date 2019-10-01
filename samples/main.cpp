#include "filter.cpp"
const char* cmdOptions =
"{ i  image         | <none> | image to process        }"
"{ q ? help usage   | <none> | print help message      }";


void main(int argc,char** argv) {
	
	CommandLineParser parser(argc, argv, cmdOptions);
	//string path_to_image(parser.get<String>("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU-build\\samples\\lobachevsky.jpg"));
	Mat image = imread("C:\\Users\\aaron\\OneDrive\\Рабочий стол\\OU\\picture\\lob.jpg");
	Filter fil(image);
	Mat new_image = image.clone();
	Mat avg = fil.AverageFilter();
	cvtColor(image, new_image, COLOR_BGR2GRAY);
	int cc = Check_Diff(new_image, avg);
	int miss = 0;
	/*imshow("Gray Filter", new_image);
	imshow("Average Filter", avg);
	imshow("Lightness Filter", fil.LightnessFilter());
	imshow("Luminosity Filter", fil.LuminosityFilter());
	imshow("Photoshop Filter", fil.PhotoshopFilter());
	imshow("ITU-R", fil.ITU_R());
	imshow("Max", fil.Max());
	imshow("Min", fil.Min());
	imshow("NoName", fil.NoName());*/
	imshow("Windows", Print_Problems(new_image, avg, cc,miss));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << (int)avg.at<Vec3b>(i, j)[0] << " ";
		}
		cout << "          ";
		for (int j = 0; j < 5; j++)cout << (int)new_image.at<uchar>(i, j) << " ";
		cout << endl;
	}
	cout << endl;
	cout << cc << endl;
	cout << "Missed:" << miss << endl;
	cout << "Right:" << avg.cols * avg.rows - miss << endl;
	waitKey(0);
}



