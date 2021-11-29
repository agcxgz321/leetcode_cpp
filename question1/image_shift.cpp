#pragma comment(lib,"opencv_world341d.lib")

#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/opencv.hpp>
#include<string>
using namespace cv;

int main(int argc, char* argv[]) {
	String s1 = argv[1];
	String s2 = argv[2];

	Mat srcImage11 = imread(s1, -1);
	Mat srcImage21 = imread(s2, -1);

	if (!srcImage11.data) //判断图片调入是否成功
		return -1;

	Mat dst1, dst2;
	Mat srcImage1, srcImage2;
	//cvtColor(srcImage11, srcImage1, COLOR_BGR2GRAY);
	//cvtColor(srcImage21, srcImage2, COLOR_BGR2GRAY);
	// 转灰度图
	srcImage11.convertTo(dst1, CV_32FC1);
	srcImage21.convertTo(dst2, CV_32FC1);

	Point2d phase_shift;
	phase_shift = phaseCorrelate(dst1, dst2);

	std::cout << "x方向的偏移量：" << phase_shift.x << std::endl;
	std::cout << "y方向的偏移量：" << phase_shift.y << std::endl;
	return 0;

}


