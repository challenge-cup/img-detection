#pragma once 

//#include <stdafx.h>  
#include <iostream>  
#include <vector>

#ifndef PI
#define PI 3.1415926535
#endif

using namespace std;
using namespace Eigen;

struct ParamQuad {

	std::vector<cv::Rect> bounding_box;
	bool state;

	ParamQuad(std::vector<cv::Rect> _bounding_box, bool _state) :
		bounding_box(_bounding_box),
		state(_state)
		{ }
};





