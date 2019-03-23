
#if !defined(IMAGEPROCESS_H_)
#define IMAGEPROCESS_H_

#include <map>
#include <vector>
#include <iostream>
#include <image_transport/image_transport.h> //image_transport 
#include <cv_bridge/cv_bridge.h> //cv_bridge
#include <sensor_msgs/Image.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/imgproc.hpp>

#include "imgDetection.h"


class ImageProcess
{
private:
    cv::Mat cur_img;
    bool new_image = false;
    bool correct_image = false;
    int true_count = 0;   //检测到的次数，用于延迟画方框，不至于太抖
    int rect_flash_frq = 3;

    std::vector<cv::Rect> bounding_box;


    imgDetection imgDetector;

public:
    ImageProcess()  {};
    ~ImageProcess() {};
    void forward_image_callback_simple(const sensor_msgs::ImageConstPtr &_img);
    void img_loop();
    
};




#endif // IMAGEPROCESS_H_


