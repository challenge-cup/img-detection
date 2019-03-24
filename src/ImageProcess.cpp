#include "ImageProcess.h"

void ImageProcess::img_loop(){
    
    ofstream outFile; 
    outFile.open("/home/randy/ros_ws/detection_ws/src/data.csv" , ios::out); 
    while(1)    {
        
        if(new_image)   {

            cv::Mat res_img = cur_img.clone();
            ParamQuad paramQuad(std::vector<cv::Rect>{}, false);
            imgDetector.quadDetection(cur_img, paramQuad);      //得到是否有想要的数字，需输入牌子的方向
            
            if (paramQuad.state == true)    {
                //隔几次再刷新矩形框，看着不抖
                if ( true_count == 0 )   {  
                    bounding_box = paramQuad.bounding_box;
                }
                if( ++true_count == rect_flash_frq ) {
                    true_count = 0;
                }
                
                //画框和感叹号
                for (auto iter = bounding_box.begin(); iter != bounding_box.end(); iter++)	{
                    cv::rectangle(cur_img, *iter, cv::Scalar(171, 90, 0), 3, 1, 0);
                    imgDetector.addSign(cur_img, res_img, 
                    cv::Point(iter->x + iter->width / 2, iter->y + iter->height) );  //画上感叹号
                }

                //  计算速度并输出至csv
                cv::Rect cur_box = paramQuad.bounding_box.front();
                cur_pos = cv::Point(cur_box.x + cur_box.width/2, cur_box.y + cur_box.height);
                if ( pre_pos.x != 0 && pre_pos.y != 0 ) {
                    cur_vel = cur_pos - pre_pos;
                }
                outFile << "pre_pos" << "," << pre_pos << "," << "cur_pos" << ',' << cur_pos << ',' << "cur_vel" << "," << cur_vel << endl;
                pre_pos = cur_pos;
                cout << "write csv" <<endl;
 
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

