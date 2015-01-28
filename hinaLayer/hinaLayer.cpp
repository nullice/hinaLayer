#include "hinaLayer.h"
//C++
#include <iostream>
#include <string>
#include<bitset>
#include<fstream>
#include<math.h>
//openCV 
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;



//载入


/// <summary>
/// 打开文件以创建 hinaLayer 操作对象
/// </summary>
/// <param name="filename">要打开的图像文件名.</param>
/// <param name="mono">是否打开作为单色图像，0为彩色，1为单色，缺省为0.</param>
/// <returns>返回0打开文件失败</returns>
int hinaLayer::openfile(char* filename, int mono = 0)
{
	auto image = imread(filename,(mono==1)?0:1);
	if(image.empty())
	{
		cerr << "载入图片: "<<filename<<" 失败。" << endl;
		return 0;
	}
	return 1;
}

int writefile(char* filename)
{
	
}






/// <summary>
/// 重新设置图像大小，图像内容将被拉伸.
/// </summary>
/// <param name="w">新图像宽度 w.</param>
/// <param name="h">新图像高度 h.</param>
/// <returns>int.</returns>
void hinaLayer::resize(int w,int h)
{
	Mat temp(w,h,image.type());
    cv::resize(image,temp,temp.size(),0,0,CV_INTER_NN);
	temp.copyTo(image);
}





















