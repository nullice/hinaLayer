// ***********************************************************************
// Assembly         : 
// Author           : 语冰
// Created          : 01-28-2015
//
// Last Modified By : 语冰
// Last Modified On : 02-02-2015
// ***********************************************************************
// <copyright file="hinaLayer.cpp" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
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
int hinaLayer::open_file(char* filename, int mono)
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
int hinaLayer::out_file(char* filename)
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
/// 写出保存 hinaLayer 的图像(频域图像).
/// </summary>
/// <param name="filename">写出文件名.</param>
/// <returns>int.</returns>
int hinaLayer::out_file_fdomain(char* filename)
{
	bool b = imwrite(filename, fdomain*255);
	if (b != true)
	{
		cerr << "写到文件" << filename << "失败";
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
/// <param name="title">The title.</param>
void hinaLayer::show(string title)
{ 

	imshow(title, image);
	waitKey(0);
}


/// <summary>
/// Show_fdomains the specified title.
/// </summary>
/// <param name="title">The title.</param>
void hinaLayer::show_fdomain(string title)
{
	imshow(title, fdomain);
	waitKey(0);
}

/// <summary>
/// Show_eoes the specified title.
/// </summary>
/// <param name="title">The title.</param>
/// <param name="rgb">The RGB.</param>
void hinaLayer::show_eo(string title, int rgb /*= 3*/)
{
	void eo_decode(Mat& imageROI, int rgb);

	Mat temp;
	image.copyTo(temp);

	if (3 == rgb)
	{
		eo_decode(temp, 0);
		eo_decode(temp, 1);
		eo_decode(temp, 2);
	}
	else
	{
		eo_decode(temp, rgb);
	}
	

	imshow(title + " [" + to_string(rgb) + "]", temp);
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





/// <summary>
/// 预处理，把输入图像转换为能进行DFT的中间矩阵，并且进行过DFT转换,结果在 mmat 中.
/// </summary>
/// <param name="rgb">RGB通道, 0~2 顺序BGR ,3 为处理全部通道.</param>
/// <returns>int.</returns>
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
			dft(mmat[i], mmat[i]);
		}
	}
	else
	{
		make_mmat(imageSplit[rgb], mmat[rgb]);
		dft(mmat[rgb], mmat[rgb]);
	}
	return 0;
}


/// <summary>
/// DTF中间矩阵逆转换到图像
/// </summary>
/// <param name="rgb">RGB通道, 0~2 顺序BGR ,3 为处理全部通道.</param>
/// <returns>int.</returns>
int hinaLayer::dtf_inverse_make(int rgb /*= 3*/)
{
	void show_idft(const  Mat& in, const Mat& origin, Mat& out);

	
	if (3 == rgb)
	{
		for (int i = 0; i < 3; i++)
		{
			idft(mmat[i], mmat[i]);
			show_idft(mmat[i], image, mmat[i]);
		}
	}
	else
	{
		idft(mmat[rgb], mmat[rgb]);
		show_idft(mmat[rgb], image, mmat[rgb]);
	}
	
	dtf_to_image(rgb);
	return 0;
}



/// <summary>
/// mmat 可视化 ， 让DTF转换后的 mmat 可视化（变为0~1的矩阵）
/// </summary>
/// <param name="rgb">RGB通道, 0~2 顺序BGR ,3 为处理全部通道.</param>
/// <returns>int.</returns>
int hinaLayer::dtf_print(int rgb /*= 3*/)
{

	void show_dft(Mat& in, Mat& out);

	if (3 == rgb)
	{
		Mat temp[3];
		for (int i = 0; i < 3; i++)
		{
			show_dft(mmat[i], temp[i]);
		}
		merge(temp, 3, fdomain);

	}
	else
	{
		show_dft(mmat[rgb], fdomain);
	}
	return 0;
}

/// <summary>
/// DTF中间矩阵象限调换.
/// </summary>
/// <param name="rgb">RGB通道, 0~2 顺序BGR ,3 为处理全部通道.</param>
void hinaLayer::dtf_mmat_n2c(int rgb /*= 3*/)
{
	void mat_n2c(Mat& in);
	
	if (3 == rgb)
	{
		for (int i = 0; i < 3; i++)
		{
			mat_n2c(mmat[i]);
		}
	}
	else
	{
		mat_n2c(mmat[rgb]);
	}
}


/// <summary>
/// Dtf_to_images the specified RGB.
/// </summary>
/// <param name="rgb">The RGB.</param>
void hinaLayer::dtf_to_image(int rgb)
{
	Mat temp[3];
	if (3 == rgb)
	{
		for (int i = 0; i < 3; i++)
		{
			mmat[i].convertTo(temp[i], image.type(),255);
		}
		merge(temp, 3, image);
	}
	else
	{
		mmat[rgb].convertTo(image, image.type(), 255);
	}
}

/// <summary>
/// Dtf_write_masks the specified mask.
/// </summary>
/// <param name="mask">The mask.</param>
/// <param name="rgb">The RGB.</param>
/// <returns>int.</returns>
int hinaLayer::dtf_write_mask(Mat& mask, int rgb /*= 3*/)
{
	void writeINFO(Mat& in, Mat& info);
	Mat temp[3];
	if (3 == rgb)
	{
		for (int i = 0; i < 3; i++)
		{
			
			writeINFO(mmat[i],mask);
		}
	}
	else
	{
		writeINFO(mmat[rgb], mask);
	}
}

/// <summary>
/// Dtf_write_masks the specified mask_file.
/// </summary>
/// <param name="mask_file">The mask_file.</param>
/// <param name="rgb">The RGB.</param>
/// <returns>int.</returns>
int hinaLayer::dtf_write_mask(char* mask_file, int rgb /*= 3*/)
{
	void writeINFO(Mat& in, char* info_f);
	Mat temp[3];
	if (3 == rgb)
	{
		for (int i = 0; i < 3; i++)
		{

			writeINFO(mmat[i], mask_file);
		}
	}
	else
	{
		writeINFO(mmat[rgb], mask_file);
		
	}
	return 0;
}

/// <summary>
/// Eo_to_images the specified RGB.
/// </summary>
/// <param name="rgb">The RGB.</param>
void hinaLayer::eo_to_image(int rgb /*= 3*/)
{
	void eo_decode(Mat& imageROI, int rgb);


	if (3 == rgb)
	{
		for (int i = 0; i < 3; i++)
		{
			eo_decode(image, i);
		}
	}
	else
	{
		eo_decode(image, rgb);
	}


}








/// <summary>
/// Eo_write_masks the specified mask.
/// </summary>
/// <param name="mask">The mask.</param>
/// <param name="rgb">The RGB.</param>
/// <param name="auto_size">The auto_size.</param>
void hinaLayer::eo_write_mask(Mat& mask, int rgb /*= 3*/, int auto_size /*= 0*/)
{
	void eo_writeINFO(Mat& in, Mat& info, int rgb);
	void eo_writeINFO_org(Mat& in, Mat& info, int rgb);
	void eo_to0(Mat& in, int rgb);


	Mat info;
	mask.copyTo(info);
	normalize(info, info, 0, 1, CV_MINMAX);

	if (3 == rgb)
	{
		for (int i = 0; i < 3; i++)
		{
			eo_to0(image, i);
			if (0 == auto_size)
				eo_writeINFO_org(image, info, i);
			else
				eo_writeINFO(image, info, i);
			
		}
	}
	else
	{
		eo_to0(image, rgb);

		if (0 == auto_size)
			eo_writeINFO_org(image, info, rgb);
		else
			eo_writeINFO(image, info, rgb);
	}
}


/// <summary>
/// Eo_write_masks the specified mask_file.
/// </summary>
/// <param name="mask_file">The mask_file.</param>
/// <param name="rgb">The RGB.</param>
/// <param name="auto_size">The auto_size.</param>
void hinaLayer::eo_write_mask(char* mask_file, int rgb /*= 3*/, int auto_size /*= 0*/)
{
	void eo_writeINFO(Mat& in, Mat& info, int rgb);
	void eo_to0(Mat& in, int rgb);

	Mat info = imread(mask_file);

	eo_write_mask(info, rgb, auto_size);


}

/// <summary>
/// Eo_write_files the specified info_file.
/// </summary>
/// <param name="info_file">The info_file.</param>
void hinaLayer::eo_write_file(char* info_file, int rgb)
{
	void bit_f_write(char* filename, Mat& image, int rgb = 3);
	bit_f_write(info_file, image, rgb);
}

/// <summary>
/// Eo_out_files the specified out_file.
/// </summary>
/// <param name="out_file">The out_file.</param>
void hinaLayer::eo_out_file(char* out_file, int rgb)
{
	void bit_f_decode(Mat& image, char* filename, int rgb = 3);
	bit_f_decode(image, out_file, rgb);

}

/// <summary>
/// Lsb_write_files the specified info_file.
/// </summary>
/// <param name="info_file">The info_file.</param>
void hinaLayer::lsb_write_file(char* info_file, int rgb)
{
	void bit_f_write_A(char* filename, Mat& image, int rgb = 3);
	bit_f_write_A(info_file, image, rgb);
}

/// <summary>
/// Lsb_out_files the specified info_file.
/// </summary>
/// <param name="info_file">The info_file.</param>
/// <param name="en_deep">The en_deep.</param>
void hinaLayer::lsb_out_file(char* info_file, int rgb, int en_deep)
{
	void bit_f_decode_A(Mat& image, char* filename, int rgb, int en_deep = 0);
	bit_f_decode_A(image, info_file, rgb, en_deep);
}

/// <summary>
/// Lsb_get_maxes this instance.
/// </summary>
/// <returns>unsigned long.</returns>
unsigned long hinaLayer::lsb_get_max(int rgb)
{
	int nl = image.rows; // number of lines  
	int nc = image.cols; // number of columns  
	
	unsigned long  pxbit;

	if (3 == rgb)
		pxbit = nl*nc * 3;
	else
		pxbit = nl*nc * 1;

	return pxbit;
}

/// <summary>
/// Lsb_get_deeps the specified file.
/// </summary>
/// <param name="file">The file.</param>
/// <returns>int.</returns>
int hinaLayer::lsb_get_deep(char* file, int rgb)
{
	ifstream in(file, ios::binary);
	int tmp;//
	char* buffer;
	unsigned long  size;

	in.seekg(0, ios::end);
	size = in.tellg();//计算文件大小
	in.seekg(0, ios::beg);


	//----------------------
	int nl = image.rows; // number of lines  
	int nc = image.cols; // number of columns  

	//预处理，计算嵌入深度2~8
	int deep = 2;
	double f = 0;
	unsigned long  pxbit;
	if (3 == rgb)
		pxbit = nl*nc * 3;
	else
		pxbit = nl*nc * 1;


	f = (double)size / (double)((double)pxbit / 8);
	//_DEBUG cout << f << endl;
	if (((f * 1000000 - (int)f * 1000000)) > 0)
	{
		f = f + 1.0;
	}
	deep = f;
	if (deep <= 0)deep = 8;
	if (deep > 8)deep = 8;
	if (deep < 2)deep = 2;

	return deep;
}

//com









//openCV 操作==============================================================================================================================
/// <summary>
/// Make_mmats the specified in.
/// </summary>
/// <param name="in">The in.</param>
/// <param name="out">The out.</param>
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


/// <summary>
/// Show_dfts the specified in.
/// </summary>
/// <param name="in">The in.</param>
/// <param name="out">The out.</param>
void show_dft(Mat& in, Mat& out)//让dft转换后的Mat可视化（变为0~1的矩阵）
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
/// Mat_n2cs the specified in.
/// </summary>
/// <param name="in">The in.</param>
void mat_n2c(Mat& in){
	/*
	* +----+----+    +----+----+
	* |    |    |    |    |    |
	* | q0 | q1 |    | q3 | q2 |
	* |    |    |    |    |    |
	* +----+----+ -> +----+----+
	* |    |    |    |    |    |
	* | q2 | q3 |    | q1 | q0 |
	* |    |    |    |    |    |
	* +----+----+    +----+----+
	*/
	const int half_width = in.cols / 2;
	const int half_height = in.rows / 2;

	Mat tmp;

	Mat q0(in,
		Rect(0, 0, half_width, half_height));
	Mat q1(in,
		Rect(half_width, 0, half_width, half_height));
	Mat q2(in,
		Rect(0, half_height, half_width, half_height));
	Mat q3(in,
		Rect(half_width, half_height, half_width, half_height));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}





/// <summary>
/// Show_idfts the specified in.
/// </summary>
/// <param name="in">The in.</param>
/// <param name="origin">The origin.</param>
/// <param name="out">The out.</param>
void show_idft(const Mat& in, const Mat& origin, Mat& out)//in 输入idft 后的矩阵（mmat）,origin 原图 用来取得图像大小 剪掉预处理扩展的边界，out 输出
{

	Mat splitted_image[2];
	split(in, splitted_image);
	splitted_image[0](cv::Rect(0, 0, origin.cols, origin.rows)).copyTo(out);
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


/// <summary>
/// Writes the mx.
/// </summary>
/// <param name="in">The in.</param>
/// <param name="info">The information.</param>
void writeMx(Mat& in, Mat& info)
{
	for (int j = 0; j < info.rows; j++)//按照图像布局打印数值
	{
		for (int i = 0; i < info.cols; i++)
		{
			in.at<cv::Vec2f>(i, j) = in.at<cv::Vec2f>(i, j)*info.at<uchar>(i, j);
		}
	}
}


/// <summary>
/// Eo_wbools the specified in.
/// </summary>
/// <param name="in">The in.</param>
/// <returns>int.</returns>
int eo_wbool(int in)//奇偶
{
	in = in + 1;
	return in;
}

/// <summary>
/// Eo_bools the specified in.
/// </summary>
/// <param name="in">The in.</param>
/// <returns>int.</returns>
int eo_bool(int in)//奇偶验证
{
	if ((in & 1) == 1)
		return 1;
	else
		return 0;
}

/// <summary>
/// Eo_decodes the specified image roi.
/// </summary>
/// <param name="imageROI">The image roi.</param>
/// <param name="rgb">The RGB.</param>
void eo_decode(Mat& imageROI, int rgb)
{
	int dot = 0;
	for (int j = 0; j < imageROI.cols; j++)//按照图像布局打印数值
	{
		for (int i = 0; i < imageROI.rows; i++)
		{
			dot = imageROI.at<cv::Vec3b>(i, j)[rgb];

			if (eo_bool(dot) == 1)
			{
				imageROI.at<cv::Vec3b>(i, j)[rgb] = 255;
				if (3 == rgb)
				{
					imageROI.at<cv::Vec3b>(i, j)[0] = 255;
					imageROI.at<cv::Vec3b>(i, j)[1] = 255;
					imageROI.at<cv::Vec3b>(i, j)[2] = 255;
				}
				
				

			}
			else
			{
				imageROI.at<cv::Vec3b>(i, j)[rgb] = 0;
				if (3 == rgb)
				{
					imageROI.at<cv::Vec3b>(i, j)[0] = 0;
					imageROI.at<cv::Vec3b>(i, j)[1] = 0;
					imageROI.at<cv::Vec3b>(i, j)[2] = 0;
				}

			}
		}
	}
}

/// <summary>
/// Eo_outbitimgs the specified in.
/// </summary>
/// <param name="in">The in.</param>
/// <param name="rgb">The RGB.</param>
void eo_outbitimg(Mat& in, int rgb)
{
	Mat imageROI;
	in.copyTo(imageROI);
	imshow("原图", imageROI);
	eo_decode(imageROI, rgb);
	imshow("解码", imageROI);
	waitKey(0);
}


/// <summary>
/// Writes the information.
/// </summary>
/// <param name="in">The in.</param>
/// <param name="info">The information.</param>
void writeINFO(Mat& in, Mat& info)
{	
	normalize(info, info, 0, 1, CV_MINMAX);

	Mat imageROI;
	imageROI = in(Rect(0, 0, info.rows, info.cols));

	const int half_width = in.cols / 2;
	const int half_height = in.rows / 2;

	Mat tmp;

	Mat q0(in,
		Rect(0, 0, half_width, half_height));
	Mat q1(in,
		Rect(half_width, 0, half_width, half_height));
	Mat q2(in,
		Rect(0, half_height, half_width, half_height));
	Mat q3(in,
		Rect(half_width, half_height, half_width, half_height));


	imageROI = q3(Rect(0, 0, info.rows, info.cols));


	writeMx(imageROI, info);

	imageROI = q0(Rect(q0.cols - info.cols, q0.rows - info.rows, info.rows, info.cols));
	Mat a, b;

	MirrorY(info, a);
	MirrorX(a, b);
	writeMx(imageROI, b);

}

/// <summary>
/// Writes the information.
/// </summary>
/// <param name="in">The in.</param>
/// <param name="info_f">The info_f.</param>
void writeINFO(Mat& in, char* info_f)
{
	//获取最大值最小值
	Mat info = imread(info_f, IMREAD_GRAYSCALE);
	writeINFO(in, info);
}


/// <summary>
/// Eo_to0s the specified in.
/// </summary>
/// <param name="in">The in.</param>
/// <param name="rgb">The RGB.</param>
void eo_to0(Mat& in, int rgb)
{
	int dot = 0;
	for (int j = 0; j<in.cols; j++)
	{
		for (int i = 0; i<in.rows; i++)
		{
			dot = in.at<cv::Vec3b>(i, j)[rgb];
			//到单数
			if ((dot & 1) == 1)
			{
				if (dot >= 255)
					dot = 254;
				else
					dot = dot + 1;
			}
			in.at<cv::Vec3b>(i, j)[rgb] = dot;
		}
	}
}


/// <summary>
/// Eo_writes the information.
/// </summary>
/// <param name="in">The in.</param>
/// <param name="info">The information.</param>
/// <param name="rgb">The RGB.</param>
void eo_writeINFO(Mat& in, Mat& info, int rgb)
{
	//改变Info大小
	int llong = 0;
	if (in.rows <= in.cols)
		llong = in.rows;
	else
		llong = in.cols;

	int neww = 0, newh = 0;

	if (info.rows >= info.cols)
	{
		neww = llong*0.8;
		newh = neww * info.cols / info.rows;
	}
	else
	{
		newh = llong*0.8;
		neww = newh*info.rows / info.cols;
	}

	if (newh >= info.rows * 2)
	{
		Mat big(neww, newh, info.type());
		resize(info, big, big.size(), 0, 0, CV_INTER_NN);
		big.copyTo(info);
	}

	//改变Info大小=============
	int w = (in.rows - info.rows) / 4;
	int h = (in.cols - info.cols) / 2;

	Mat imageROI(in, Rect(h, w, info.cols, info.rows));

	int dot = 0;
	int scr = 0;


	int min_rows, min_cols;
	min_rows = (in.rows <= info.rows) ? in.rows : info.rows;//列j
	min_cols = (in.cols <= info.cols) ? in.cols : info.cols;//行i

	for (int j = 0; j < imageROI.rows; j++)//按照图像布局打印数值
	{
		for (int i = 0; i < imageROI.cols; i++)
		{
				dot = info.at<cv::Vec3b>(j, i)[rgb];
				scr = imageROI.at<cv::Vec3b>(j, i)[rgb];
			
				if (dot > 0)
				{
					scr = eo_wbool(scr);
				}

				imageROI.at<cv::Vec3b>(j, i)[rgb] = scr;
		}
	}
}

/// <summary>
/// Eo_writes the inf o_org.
/// </summary>
/// <param name="in">The in.</param>
/// <param name="info">The information.</param>
/// <param name="rgb">The RGB.</param>
void eo_writeINFO_org(Mat& in, Mat& info, int rgb)
{
	int dot = 0;
	int scr = 0;


	int min_rows, min_cols;
	min_rows = (in.rows <= info.rows) ? in.rows : info.rows;//列j
	min_cols = (in.cols <= info.cols) ? in.cols : info.cols;//行i
	//_DEBUG cout <<endl<< min_rows << endl << min_cols;

	for (int j = 0; j < min_rows; j++)//按照图像布局打印数值
	{
		for (int i = 0; i <min_cols; i++)
		{
			//cout << endl << i << "<" << min_cols;

				dot = info.at<cv::Vec3b>(j, i)[rgb];
				scr = in.at<cv::Vec3b>(j, i)[rgb];
				
				if (dot > 0)
				{
					scr = eo_wbool(scr);
				}

				in.at<cv::Vec3b>(j, i)[rgb] = scr;

		}
	}
}




//bit-------

/// <summary>
/// Bit_to0s the specified in.
/// </summary>
/// <param name="in">The in.</param>
/// <param name="rgb">The RGB.</param>
void bit_to0(Mat& in, int rgb)
{
	int dot = 0;
	for (int j = 0; j<in.cols; j++)
	{
		for (int i = 0; i<in.rows; i++)
		{
			dot = in.at<cv::Vec3b>(i, j)[rgb];
			//到单数
			if ((dot & 1) == 1)
			{
				if (dot >= 255)
					dot = 254;
				else
					dot = dot + 1;
			}
			in.at<cv::Vec3b>(i, j)[rgb] = dot;
		}
	}
}

/// <summary>
/// Bit_f_writes the specified filename.
/// </summary>
/// <param name="filename">The filename.</param>
/// <param name="image">The image.</param>
void bit_f_write(char* filename, Mat& image, int rgb)
{
	ifstream in(filename, ios::binary);
	if (!in)
	{
		cerr << "open error!" << endl;
		abort();
	}
	int tmp;
	char* buffer;
	long size;

	in.seekg(0, ios::end);
	size = in.tellg();
	//cout<<size<<endl;
	in.seekg(0, ios::beg);

	bitset<8> bit;
	for (int i = 0; i < size; i++)
	{
		bit = in.get();

	}
	//----------------------
	int nl = image.rows; // number of lines  
	int nc = image.cols; // number of columns  
	bit_to0(image, 0);
	bit_to0(image, 1);
	bit_to0(image, 2);



	int cheak = 0;
	int pass = 0;

	in.seekg(0, ios::beg);
	bit = in.get();

	for (int j = 0; j < nl; j++) {
		for (int i = 0; i < nc; i++)
		{

			if (pass <= size)
			{
				for (int p = 0; p < 3; p++)
				{
					if ((3 == rgb) || (rgb == p))
					{
						if (cheak == 8)
						{
							//cout<<bit<<"<";
							bit = in.get();
							pass++;
							cheak = 0;
						}


						//cout<<(int)(image.at<cv::Vec3b>(j,i)[p]&1)<<"->";
						if (bit.test(7 - cheak) == 1)
						{
							image.at<cv::Vec3b>(j, i)[p] = image.at<cv::Vec3b>(j, i)[p] + 1;

						}
						//cout<<(int)(image.at<cv::Vec3b>(j,i)[p]&1)
						//<<"="<<bit.test(cheak)
						//<<",";
						cheak++;
					}
				}
			}


		}
	}
}

/// <summary>
/// Bit_f_write_s a.
/// </summary>
/// <param name="filename">The filename.</param>
/// <param name="image">The image.</param>
void bit_f_write_A(char* filename, Mat& image, int rgb)
{
	ifstream in(filename, ios::binary);
	//载入文件
	if (!in)
	{
		cerr << "open error!" << endl;
		abort();
	}

	int tmp;//
	char* buffer;
	unsigned long  size;

	in.seekg(0, ios::end);
	size = in.tellg();//计算文件大小
	//cout<<size<<endl;
	in.seekg(0, ios::beg);



	bitset<8> bit;
	bitset<8> bit_temp;


	for (unsigned long i = 0; i < size; i++)
	{
		bit = in.get();
	}

	//----------------------
	int nl = image.rows; // number of lines  
	int nc = image.cols; // number of columns  

	//预处理，计算嵌入深度2~8
	int deep = 2;
	double f = 0;
	unsigned long  pxbit;
	if (3 == rgb)
		pxbit = nl*nc * 3;
	else
		pxbit = nl*nc * 1;
	


	f = (double)size / (double)((double)pxbit / 8);
	//_DEBUG cout << "size:" << size << endl;
	//_DEBUG cout << "pxbit/8:" << (double)pxbit / 8 << endl;

	//_DEBUG cout << f << endl;
	if (((f * 1000000 - (int)f * 1000000)) > 0)
	{
		f = f + 1.0;
	}

	deep = f;
	if (deep <= 0)deep = 8;
	if (deep > 8)deep = 8;
	if (deep < 2)deep = 2;

	//_DEBUG cout << "计算深度：" << deep << endl;

	//写入嵌入深度
	int i = image.at<cv::Vec3b>(0, 0)[0];
	if (i >= 250 || deep == 8) i = i - 10;
	image.at<cv::Vec3b>(0, 0)[0] = i - i % 100 % 10 + deep - 2;


	int cheak = 0;
	int pass = 0;

	in.seekg(0, ios::beg);
	bit = in.get();
	unsigned long  rrr = 0;
	for (int j = 0; j < nl; j++) {
		for (int i = 0; i < nc; i++)
		{

			if (pass <= size && (j + i > 0))
			{
				for (int p = 0; p < 3; p++)
				{//--------------------------------------------
					if ((3 == rgb) || (rgb == p))
					{
						bit_temp = image.at<cv::Vec3b>(j, i)[p];
						//if(pass<200)
						//cout<<"-------\n";
						for (int z = 0; z < deep; z++)
						{
							if (cheak == 8)
							{
								//	if(pass<200)
								//cout<<"=============\n";
								bit = in.get();
								pass++;
								cheak = 0;
							}
							//if(pass<200)
							//cout<<"bit="<<bit<<">temp="<<bit_temp<<"<"<<cheak<<":"<<bit.test(7-cheak)<<">";


							if (bit.test(7 - cheak) == 1)
							{
								bit_temp.set(z);
								cheak++;
							}
							else
							{
								bit_temp.reset(z);
								cheak++;

							}
							//if(pass<200)
							//cout<<bit_temp<<endl;

						}

						image.at<cv::Vec3b>(j, i)[p] = bit_temp.to_ulong();
					}

				}//--------------------------------------------
			}

		}
	}
	in.close();
	//_DEBUG cout << rrr;
}

/// <summary>
/// Bit_f_decode_s a.
/// </summary>
/// <param name="image">The image.</param>
/// <param name="filename">The filename.</param>
/// <param name="en_deep">The en_deep.</param>
void bit_f_decode_A(Mat& image, char* filename , int rgb, int en_deep)
{
	using namespace std;

	int nl = image.rows; // number of lines  
	int nc = image.cols; // number of columns  

	ofstream in(filename, ios::binary);
	int cheak = 0;
	int pass = 0;

	bitset<8> bit(0);
	bitset<8> bit_temp(0);
	in.seekp(0, ios::beg);

	int deep;//判断深度
	if (0 == en_deep)
	{	//以第一个像素首位0通道值的个位数判断深度
		deep = image.at<cv::Vec3b>(0, 0)[0];
		deep = deep % 100 % 10 + 2;

		if (deep > 8)deep = 8;
		//_DEBUG cout << "判断深度:" << deep;
	}
	else
	{
		deep = en_deep;
	}

	char t;
	for (int j = 0; j < nl; j++)
	{
		for (int i = 0; i < nc; i++)
		{
			if ((i + j > 0) || (0 != en_deep))//是否忽略第一个像素
			{
				for (int p = 0; p < 3; p++)
				{//------------------------
					if ((rgb == p) || (3 == rgb))
					{
						pass++;
						bit_temp = image.at<cv::Vec3b>(j, i)[p];

						for (int z = 0; z < deep; z++)
						{
							if (cheak == 8)
							{
								t = (char)bit.to_ulong();
								in.put(t);
								cheak = 0;
								bit.reset();
							}


							if (bit_temp.test(z) == 1)
							{
								bit.set(7 - cheak);
								cheak++;
							}
							else
							{
								bit.reset(7 - cheak);
								cheak++;
							}
						}
					}
				}

			}//------------------------
		}
	}
	in.close();
}

/// <summary>
/// Bit_f_decodes the specified image.
/// </summary>
/// <param name="image">The image.</param>
/// <param name="filename">The filename.</param>
void bit_f_decode(Mat& image, char* filename, int rgb)
{

	int nl = image.rows; // number of lines  
	int nc = image.cols; // number of columns  

	ofstream in(filename, ios::binary);
	int cheak = 0;
	int pass = 0;

	bitset<8> bit(0);
	in.seekp(0, ios::beg);
	char t;
	for (int j = 0; j < nl; j++) {
		for (int i = 0; i < nc; i++)
		{
			
			
			for (int p = 0; p < 3; p++)
			{
				if ((3==rgb)|| (rgb == p))
				{ 
					if (cheak == 8)
					{
						t = (char)bit.to_ulong();
						in.put(t);
						cheak = 0;
						bit.reset();
					}

					pass++;
					//if(pass<100)
					//cout<<(int)(image.at<cv::Vec3b>(j,i)[p]&1)<<",";

					if ((image.at<cv::Vec3b>(j, i)[p] & 1) == 1)
					{
						bit.set(7 - cheak);
						cheak++;
					}
					else
					{
						bit.reset(7 - cheak);
						cheak++;
					}
				}
			}

		}
	}

	in.close();

}


