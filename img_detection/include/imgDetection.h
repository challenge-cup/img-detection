//#pragma once 
#ifndef IMG_DETECTION_H
#define IMG_DETECTION_H

//#include <stdafx.h>  
#include <iostream>  
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <chrono>

#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/opencv.hpp>  
#include <opencv2/aruco.hpp>
#include <opencv2/imgproc/imgproc.hpp>  

#include <Eigen/Core>
#include <Eigen/Dense>

#include "img_detect_datatype.h"

using namespace std;
using namespace Eigen;

class imgDetection {

public:

	void quadDetection(cv::Mat &_img, ParamQuad &paramQuad);      //检查蓝色边缘是否出现
	void addSign(const cv::Mat& _src, cv::Mat& _res, cv::Point _location);

private:
	void quadDetection(cv::Mat &_img, bool &state, std::vector<cv::Rect> &bounding_box);      //检查蓝色边缘是否出现

	const double sign_factor = 0.2;
	const double sign_offset = 20; //感叹号离矩形偏移量
};

#endif 

