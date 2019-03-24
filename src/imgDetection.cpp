#include "imgDetection.h"

using namespace cv;
using namespace cv::ml;

void imgDetection::quadDetection(cv::Mat &_img, ParamQuad &paramQuad)	{
	quadDetection(_img, paramQuad.state, paramQuad.bounding_box);
}

void imgDetection::quadDetection(cv::Mat &_img, bool &state, std::vector<cv::Rect> &bounding_box)
{
	/*  intel黑  */

	int iLowH = 19;
	int iHighH = 102;

	int iLowS = 23;
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 63;

	Mat imgHSV;
	cvtColor(_img, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV  
										   //cvtColor(imageROI, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV  
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image 

																								  //cv::imshow("img", imgThresholded);
																								  //cv::waitKey(0);


	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(8, 8));
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	//morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//imshow("Thresholded Image2", imgThresholded); //show the thresholded image
	//闭操作 (连接一些连通域)

	//cv::imshow("imgThresholded", imgThresholded);
	//cv::waitKey(0);

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	findContours(imgThresholded, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE, cv::Point());
	std::vector<cv::RotatedRect> box(contours.size());

	cv::Mat imageContours = cv::Mat::zeros(_img.size(), CV_32FC3); //最小外接矩形画布 
	state = false;

	for (int i = 0; i < contours.size(); i++) {
		cv::Rect rect = cv::boundingRect(contours[i]);
		int width, height, px, py;
		px = rect.x;
		py = rect.y;
		width = rect.width;
		height = rect.height;

		float maxRatio = 8, minRatio = 1, ratio = float(width) / height;

		//cout << height << ',' << width << ',' << ratio << endl;

		//cout << "num" << contours.size() << endl;
		//drawContours(imageContours, contours, i, cv::Scalar(255, 255, 255), 1, 8, hierarchy);
		//cv::imshow("imageContours", imageContours);
		//cv::waitKey(0);

		if (height < 130 || height > 300 || width < 200 || width > 400)  continue;
		if (ratio < 1 || ratio > 2)	continue;

		//cout << height << ',' << width << ',' << ratio << endl;

		//drawContours(imageContours, contours, i, cv::Scalar(255, 0, 0), 3, 8, hierarchy);
		//cv::imshow("img", imageContours);
		//cv::waitKey(0);
		bounding_box.push_back(rect);
		state = true;

	}

}

void imgDetection::addSign(const cv::Mat& _src, cv::Mat& _res, cv::Point _location)
{
	cv::Mat imgSign = imread("/home/randy/ros_ws/detection_ws/src/img_detection/image/1.png");
	cv::resize(imgSign, imgSign, cv::Size(imgSign.cols * sign_factor, imgSign.rows * sign_factor));
	cvtColor(imgSign, imgSign, COLOR_RGB2GRAY);

	std::vector<cv::Mat> channels;
	cv::split(_src, channels);															//分离色彩通道

	for (int i = 0; i < imgSign.rows; ++i) {										//遍历字符白点叠加
		int _y = i + _location.y - imgSign.rows;
		uchar* iDataB = channels[0].ptr<uchar>(_y);
		uchar* iDataG = channels[1].ptr<uchar>(_y);
		uchar* iDataR = channels[2].ptr<uchar>(_y);
		uchar* iDataString = imgSign.ptr<uchar>(i);
		for (int j = 0; j < imgSign.cols; ++j) {
			if (iDataString[j] <= 200)	{
				//cout << j << "  " << _location.x << "  " << imgSign.cols / 2 << endl;
				int _x = j + _location.x - imgSign.cols/2;
				iDataR[_x] = 197;
				iDataG[_x] = 31;
				iDataB[_x] = 31;
			}
		}
	}
	cv::merge(channels, _res);		

	//合并色彩通道
}
