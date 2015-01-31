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
	Mat fdomain;//频域用矩阵
	Mat mmat[3];//DTF变换用矩阵


	int openfile(char* filename, int mono = 0);//打开文件
	int writefile(char* filename);//写出文件
	void show();//预览图像
	void show_fdomain();//预览频域图像

	void resize(int w,int h);//重设图像大小
	void mirrorY();//垂直镜像
	void mirrorX();//水平镜像

	int  dtf_make(int rgb = 3);//图像转换到DTF中间矩阵
	int  dtf_print(int rgb = 3);//DTF中间矩阵可视化，频域图>>fdomain
	int  dtf_inverse_make(int rgb = 3);//DTF中间矩阵逆转换到图像
	int	 dtf_write_mask(Mat& mask, int rgb = 3);
	int	 dtf_write_mask(char* mask_file, int rgb = 3);
	void dtf_mmat_n2c(int rgb = 3);//DTF中间矩阵象限调换
	

	void dtf_to_image(int rgb = 3);

	//out
};














#endif



