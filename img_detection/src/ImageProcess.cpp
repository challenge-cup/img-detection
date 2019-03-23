#include "ImageProcess.h"

void ImageProcess::img_loop(){
    while(1)    {
        if(new_image)   {

            cv::Mat res_img = cur_img.clone();
            ParamQuad paramQuad(std::vector<cv::Rect>{}, false);
            imgDetector.quadDetection(cur_img, paramQuad);      //得到是否有想要的数字，需输入牌子的方向
            if (paramQuad.state == true)	{
                cout << "find quadrotor!" << endl;

                
                std::vector<cv::Rect> bounding_box = paramQuad.bounding_box;
                for (auto iter = bounding_box.begin(); iter != bounding_box.end(); iter++)	{
                    cv::rectangle(cur_img, *iter, cv::Scalar(171, 90, 0), 3, 1, 0);
                    imgDetector.addSign(cur_img, res_img, 
                                        cv::Point(iter->x + iter->width / 2, iter->y + iter->height) );  //画上感叹号
                }
            }
            cv::imshow("showImg", res_img);
            cv::waitKey(1);

            new_image = false;
        }
    }
}

void ImageProcess::forward_image_callback_simple(const sensor_msgs::ImageConstPtr &_img){
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        //cv_ptr = cv_bridge::toCvShare(_img);
        cv_ptr = cv_bridge::toCvCopy(_img, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    cur_img = cv_ptr->image;

    // cv::imshow("showImg", cur_img);
    // cv::waitKey(1);

    new_image = true;
}

// void ImageProcess::down_image_callback_simple(const sensor_msgs::ImageConstPtr &img_down){
//     cv_bridge::CvImageConstPtr cv_ptr;
//     try
//     {
//         //cv_ptr = cv_bridge::toCvShare(img_down);
//         cv_ptr = cv_bridge::toCvCopy(img_down, sensor_msgs::image_encodings::BGR8);
//     }
//     catch (cv_bridge::Exception& e)
//     {
//         ROS_ERROR("cv_bridge exception: %s", e.what());
//         return;
//     }
//     cv::Mat temp = cv_ptr->image;
//     cv::Mat DownRGB;
//     distCorrect(temp, DownRGB);
//     map<int, cv::Point2f> down_result = get_down_result(DownRGB, down_num_knn_);
//     int offset = 10;
//     if (down_result.size() > 0) {
//         for (auto front_iter = down_result.begin(); front_iter != down_result.end(); front_iter++)
//         {
//             //cout << "find num: " << front_iter->first << endl;
//             if ( front_iter->first == 0 && 
//                  front_iter->second.x > offset && front_iter->second.x < DownRGB.cols-offset     &&
//                  front_iter->second.y > offset && front_iter->second.y < DownRGB.rows-offset     
//                  ) //Change to func pram later.
//             {
//                 downnum_center = front_iter->second;// cv::Point( front_iter->second.x, front_iter->second.y);
//                 //ROS_INFO("downnum_center: (%d,%d)", downnum_center.x, downnum_center.y);

//                 showImg = DownRGB.clone();
//                 circle(showImg, front_iter->second, 8, Scalar(0, 0, 255), -1, 8, 0);
//                 //cv::imshow("showImg", showImg);
//                 //cv::waitKey(1);
//                 correct_down_image = true;
//                 break;
//             }
//             else
//                 correct_down_image = false;
//         }
//     }
//     else
//         correct_down_image = false;
//     new_down_image = true;
// }