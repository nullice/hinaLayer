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
	int out_file(char* filename);//写出文件
	int out_file_fdomain(char* filename);//写出文件(频域图像)
	void show(string title = "预览原图（image）");//预览图像
	void show_fdomain(string title = "预览频域图（fdomain）");//预览频域图像
	void show_eo(string title = "奇偶图像", int rgb = 3);//预览频域图像

	void resize(int w,int h);//重设图像大小
	void mirrorY();//垂直镜像
	void mirrorX();//水平镜像

	int  dtf_make(int rgb = 3);//图像转换到DTF中间矩阵（image >> mmat）；指定通道
	int  dtf_inverse_make(int rgb = 3);//DTF中间矩阵逆转换到图像（mmat >> image）；指定通道
	int  dtf_print(int rgb = 3);//DTF中间矩阵可视化（mmat >> fdomain）；指定通道
	void dtf_mmat_n2c(int rgb = 3);//DTF中间矩阵（mmat）象限调换；指定通道
	int	 dtf_write_mask(Mat& mask, int rgb = 3);//在 DTF中间矩阵（mask -> mmat） 写入水印图像矩阵；指定通道
	int	 dtf_write_mask(char* mask_file, int rgb = 3);//在 DTF中间矩阵（mask.png -> mmat） 写入水印图像文件；指定通道

	void eo_to_image(int rgb = 3);//奇偶位可视化，图像转换到图像数据矩阵(image)，
	void eo_write_mask(char* mask_file, int rgb = 3, int auto_size = 0);//在图像奇偶位上写入水印（mask -> image）；指定通道；auto_size 设置是否自动缩放水印大小
	void eo_write_mask(Mat& mask, int rgb = 3, int auto_size = 0);//在图像奇偶位上写入水印（mask.png -> image）；指定通道；auto_size 设置是否自动缩放水印大小
	void eo_write_file(char* info_file, int rgb = 3);//在图像奇偶位上写入文件二进制数据（file -> image）；指定通道
	void eo_out_file(char* out_file, int rgb = 3);//把图像奇偶位数据作为二进制数据文件写出（image -> file）；指定通道


	void lsb_write_file(char* info_file, int rgb = 3);//在图像像素数据低位写入文件二进制数据（file -> image）
	void lsb_out_file(char* info_file, int rbg = 3, int en_deep = 0);//在把图像像素数据低位作为二进制数据文件写出（image -> file）;en_deep 强制指定深度，为0自动；指定通道
	unsigned long lsb_get_max(int rgb = 3);//计算图像最大可写入二进制数据的大小，单位字节；指定通道
	int lsb_get_deep(char* file, int rgb = 3);// 计算一个文件写入到图像应该使用的深度；指定通道

private:
	void dtf_to_image(int rgb = 3);//DTF中间矩阵（mmat）转换到图像数据矩阵(image)

	//out
};


#endif



