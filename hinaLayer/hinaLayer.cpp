#include "hinaLayer.h"
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
int hinaLayer::openfile(char* filename, int mono)
{
	image = imread(filename,(mono==1)?0:1);
	if(image.empty())
	{
		cerr << "载入图片: "<<filename<<" 失败。" << endl;
		return 0;
	}
	return 1;
}

/// <summary>
/// 写出保存 hinaLayer 的图像.
/// </summary>
/// <param name="filename">写出文件名.</param>
/// <returns>int.</returns>
int hinaLayer::writefile(char* filename)
{
	bool b = imwrite(filename,image);
	if (b!=true)
	{
		cerr<<"写到文件"<<filename<<"失败";
		return 0;
	}
	
	return 1;
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


/// <summary>
/// 在一个窗口中显示当前 hinaLayer 图像.
/// </summary>
void hinaLayer::show()
{
	imshow("预览", image);
	waitKey(0);
}


/// <summary>
/// 水平镜像.
/// </summary>
void hinaLayer::mirrorX()
{	
	Mat temp;
	image.copyTo(temp);
	void MirrorX(const Mat &in, Mat &out);
	MirrorX(temp, image);
}

/// <summary>
/// 垂直镜像.
/// </summary>
void hinaLayer::mirrorY()
{
	Mat temp;
	image.copyTo(temp);
	void MirrorY(const Mat &in, Mat &out);
	MirrorY(temp, image);
	
}



int hinaLayer::dtf_make(int rgb)
{
	void make_mmat(Mat& temp, Mat& mmat);
	
	Mat imageSplit[3];
	split(image, imageSplit);

	if (3 == rgb)
	{
		for (int i = 0; i < 3; i++)
		{
			make_mmat(imageSplit[i],mmat[i]);
		}
	}
	else
	{
		make_mmat(imageSplit[rgb], mmat[rgb]);
	}
}



int hinaLayer::dtf_print(int rgb /*= 3*/)
{



}




//openCV 操作-----------------------------------


void make_mmat(Mat& in, Mat& out) //预处理，把输入图像转换为能进行DFT的中间矩阵,输入&in,输出&out
{
	//实数部分	
	Mat real_image;

	//扩展图片边界成为正方形
	copyMakeBorder(in, real_image,
		0, getOptimalDFTSize(in.rows) - in.rows,
		0, getOptimalDFTSize(in.cols) - in.cols,
		BORDER_CONSTANT,
		Scalar::all(0));

	//创造浮点型Mat0存放图片数据，Mat1填充0
	Mat planes[] = { Mat_<float>(real_image), Mat::zeros(real_image.size(), CV_32F) };

	//合并2Mat为一个2通道Mat
	merge(planes, 2, out);
}


void show_dft(Mat& in, Mat& out)//让dft转换后的Mat可视化（变为0~255的矩阵）
{

	//创建2个Mat planes作为容器 ，并把2通道的 &in 分离 
	Mat planes[2];
	split(in, planes);

	//将复数转换为幅度
	magnitude(planes[0], planes[1], out);//求模

	//对数尺度(logarithmic scale)缩放
	out += Scalar::all(1);//每个像素加1
	log(out, out);//对数

	void mat_n2c(Mat& in);
	mat_n2c(out);

	//归一化，振幅0~1
	normalize(out, out, 0, 1, CV_MINMAX);
}







/// <summary>
/// 图像垂直镜像
/// </summary>
/// <param name="in">输入要处理的图像.</param>
/// <param name="out">输入保存结果的图像.</param>
void MirrorY(const Mat &in, Mat &out)
{
	CV_Assert(in.depth() == CV_8U);
	out.create(in.rows, in.cols, in.type());

	int rows = in.rows;

	for (int i = 0; i < rows; i++)
		in.row(rows - i - 1).copyTo(out.row(i));

}


/// <summary>
/// 图像水平镜像
/// </summary>
/// <param name="in">输入要处理的图像.</param>
/// <param name="out">输入保存结果的图像.</param>
void MirrorX(const Mat &in, Mat &out)
{
	CV_Assert(in.depth() == CV_8U);
	out.create(in.rows, in.cols, in.type());

	int rows = in.rows;
	int cols = in.cols;

	switch (in.channels())
	{
	case 1:
		const uchar *origal;
		uchar *p;
		for (int i = 0; i < rows; i++){
			origal = in.ptr<uchar>(i);
			p = out.ptr<uchar>(i);
			for (int j = 0; j < cols; j++){
				p[j] = origal[cols - 1 - j];
			}
		}
		break;
	case 3:
		const Vec3b *origal3;
		Vec3b *p3;
		for (int i = 0; i < rows; i++) {
			origal3 = in.ptr<Vec3b>(i);
			p3 = out.ptr<Vec3b>(i);
			for (int j = 0; j < cols; j++){
				p3[j] = origal3[cols - 1 - j];
			}
		}
		break;
	default:
		break;
	}
}































