#ifndef HINALAYER_H
#define HINALAYER_H


//openCV 
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;


/// <summary>
/// Class hinaLayer.
/// </summary>
class hinaLayer
{
public:

	Mat image;//图像数据矩阵
	Mat mmat[3];//频域用矩阵
	int openfile(char* filename, int mono = 0);//打开文件
	int writefile(char* filename);//写出文件
	void show();//预览图像

	void resize(int w,int h);//重设图像大小
	void mirrorY();//垂直镜像
	void mirrorX();//水平镜像

	int  dtf_make(int rgb = 3);
	int  dtf_print(int rgb = 3);

	//out
};














#endif



