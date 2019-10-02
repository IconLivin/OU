#include "filter.cpp"
#include <fstream>
#include <conio.h>
#include <iomanip>
const char* cmdOptions =
"{ i  image         | <none> | image to process        }"
"{ q ? help usage   | <none> | print help message      }";




Mat Difference(Mat greyCV, Mat fil)
{

	Mat result(greyCV.rows, greyCV.cols, CV_8UC1);
	imshow("grey1", greyCV);
	waitKey(0);
	for (int i = 0; i < greyCV.rows; i++)
		for (int j = 0; j < greyCV.cols; j++)
			result.at<uchar>(i, j) = abs((int)greyCV.at<uchar>(i, j) - (int)fil.at<Vec3b>(i, j)[0]);
	imshow("grey", greyCV);
	waitKey(0);
	return result;
}

void fillFile(Mat dif, ofstream& out, string name) 
{
	
	out.open("D:\\GithubProjects\\Computer Graphics\\OU\\info1.txt",ios::app);
	if (out.is_open())
	{
		out << "Difference "<<name   << endl;
		for (int i = 0; i < dif.rows; i++) {
			for (int j = 0; j < dif.cols; j++)
			{
				int num =(int) dif.at<uchar>(i, j);
				if (num < 10)
					out << right << setw(6)<< num;
				else if (num < 100)
					out << right << setw(5)  << num;
				else
					out << right << setw(4)  << num;
			}
			out << endl;
		}
	}
	else
		cout << "Error open file" << endl;
	out.close();
}

void fillFile1(Mat grey,Mat image, ofstream& out, string name)
{

	out.open("D:\\GithubProjects\\Computer Graphics\\OU\\info.txt", ios::app);
	if (out.is_open())
	{
		out << "Difference test old  " << name << endl;
		for (int i = 0; i < grey.rows; i++) {
			for (int j = 0; j < grey.cols; j++)
			{
				int num = abs((int)grey.at<uchar>(i, j) - (int)image.at<Vec3b>(i, j)[0]);
				if (num < 10)
					out << right << setw(7) << right << num;
				else if (num < 100)
					out << right << setw(6) << right << num;
				else
					out << right << setw(5) << right << num;
			}
			out << endl;
		}
	}
	else
		cout << "Error open file" << endl;
	out.close();
}



int main(int argc,char** argv) {
	ofstream out;
	out.open("D:\\GithubProjects\\Computer Graphics\\OU\\info1.txt");
	out.close();
	out.open("D:\\GithubProjects\\Computer Graphics\\OU\\info.txt");
	out.close();
	CommandLineParser parser(argc, argv, cmdOptions);
	string path_to_image(parser.get<String>( "image"));
	Mat image = imread(path_to_image);
	if (image.empty()) {
		cout << "Failed load image" << endl;
		return -1;
	}
	Filter fil(image);
	Mat new_image = image.clone();
 	cvtColor(image, new_image, COLOR_BGR2GRAY);
	Mat avg=fil.AverageFilter();
	Mat lightness = fil.LightnessFilter();
//	fillFile(avg, out, "avg");
	Mat dif = Difference(new_image, avg);
	fillFile(dif, out," avg");
	//fillFile(Difference(new_image, lightness), out, " lightness");
	fillFile1(new_image, avg, out, "first avg");
	//fillFile(new_image, lightness, out, "first light");*/
	
	return 0;
}





//лагающий кусок дерьма
//int curr = 1;
//string nf[9] = { "Opencv grey", "Average", "Lightness", "Luminosity", "Photoshop","ITU_R", "Max", "Min", "Noname" };//namef filter
//Mat picture[9];
//cvtColor(image, picture[0], COLOR_BGR2GRAY);
//picture[1] = fil.AverageFilter();
//picture[2] = fil.LightnessFilter();
//picture[3] = fil.LuminosityFilter();
//picture[4] = fil.PhotoshopFilter();
//picture[5] = fil.ITU_R();
//picture[6] = fil.Max();
//picture[7] = fil.Min();
//picture[8] = fil.NoName();
//int key = 10;
//namedWindow(nf[0], WINDOW_AUTOSIZE);
//imshow(nf[0], picture[0]);
//waitKey(1000000000000);
//bool first = true;
//while (key != 27)
//{
//	if (first) {
//		namedWindow(nf[1], WINDOW_AUTOSIZE);
//		imshow(nf[1], picture[1]);
//		first = false;
//		waitKey(100000);
//	}
//	key = _getch();
//	key = _getch();
//	if (key == 75 && curr > 1)
//	{
//		destroyWindow(nf[curr]);
//		curr--;
//		cout << curr << endl;
//	}
//	else if (key == 77 && curr < 8)
//	{
//		destroyWindow(nf[curr]);
//		curr++;
//		cout << curr << endl;
//	}
//	namedWindow(nf[curr], WINDOW_AUTOSIZE);
//	imshow(nf[curr], picture[curr]);
//	waitKey(10000000);
//}