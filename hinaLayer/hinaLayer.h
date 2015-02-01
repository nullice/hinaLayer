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

	int open_file(char* filename, int mono = 0);//打开文件
	int write_file(char* filename);//写出文件
	void show(string title = "预览原图（image）");//预览图像
	void show_fdomain(string title = "预览频域图（fdomain）");//预览频域图像
	void show_eo(string title = "奇偶图像", int rgb = 3);//预览频域图像




	void resize(int w,int h);//重设图像大小
	void mirrorY();//垂直镜像
	void mirrorX();//水平镜像

	int  dtf_make(int rgb = 3);//图像转换到DTF中间矩阵（image >> mmat）
	int  dtf_inverse_make(int rgb = 3);//DTF中间矩阵逆转换到图像（mmat >> image）
	int  dtf_print(int rgb = 3);//DTF中间矩阵可视化（mmat >> fdomain）
	void dtf_mmat_n2c(int rgb = 3);//DTF中间矩阵（mmat）象限调换

	int	 dtf_write_mask(Mat& mask, int rgb = 3);//在 DTF中间矩阵（mask -> mmat） 写入水印图像矩阵
	int	 dtf_write_mask(char* mask_file, int rgb = 3);//在 DTF中间矩阵（mask.png -> mmat） 写入水印图像文件

	void eo_to_image(int rgb = 3);
	void eo_write_mask(char* mask_file, int rgb = 3, int auto_size = 0);
	void eo_write_mask(Mat& mask, int rgb = 3, int auto_size = 0);





private:
	void dtf_to_image(int rgb = 3);//DTF中间矩阵（mmat）转换到图像数据矩阵(image)

	//out
};














#endif



