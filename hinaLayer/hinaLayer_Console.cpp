#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "hinaLayer.h"
#include "hinaLayer_comd.h"

#include<iostream>
#include<string>
#include<bitset>
#include<fstream>
#include<math.h>


// 这几个依赖库文件必须要添加，   
// 因为这些是OpenCV所使用的第三方库   
#pragma comment( lib, "libjasperd.lib" )   
#pragma comment( lib, "libjpegd.lib" )   
#pragma comment( lib, "libpngd.lib" )   
#pragma comment( lib, "libtiffd.lib" )   
#pragma comment( lib, "zlibd.lib" )  

// 这里根据你的程序添加依赖库文件   
#pragma comment( lib, "opencv_core2410.lib" )   
#pragma comment( lib, "opencv_imgproc2410.lib" )   
#pragma comment( lib, "opencv_highgui2410.lib" )   
// 添加这两个是因为win32程序   
#pragma comment( lib, "vfw32.lib" )   
#pragma comment( lib, "comctl32.lib" )


void main(int argc, char *argv[])
{
	int act(int argc, char *argv[]);
	act(argc, argv);
}





/*
[自动隐写]
s_in			in_file		info_file		out_file	rgb_	(steg_write_file_lsb)	在图片中隐写文件(LSB).
s_out			in_file		out_file/dir	rgb_				(steg_out_file_lsb)		导出图片中隐写的文件(LSB).

[奇偶位]
en_eo_mask		in_file		info_file	out_file	rgb_	(en_mig)	在图片奇偶位上写入水印
en_eo_file		in_file		info_file	out_file	rgb_	(en_bin)	在图片奇偶位上写入文件.
de_eo_mask		in_file		out_file	rgb_				(de_mig)	导出图片奇偶位水印.
de_eo_file		in_file		out_file	rgb_				(de_bin)	导出图片奇偶位文件.
read_eo			in_file		rgb								(read_mig)	在窗口中预览图片的奇偶位图像.

[低像素位]
en_lsb_file		in_file		info_file	out_file	rgb_	(en_bin_A)	在图片像素低位上写入文件.
de_lsb_file		in_file		out_file	rgb_				(de_bin_A)	导出图片像素低位文件.

[频域]
en_dtf_mask		in_file		info_file	out_file	rgb		(en_dtf)	在图片DTF频域上写入水印.
de_dtf_mask		in_file		out_file	rgb					(de_dtf)	导出图片DTF频域水印.
read_dtf		in_file		rgb											在窗口中预览图片的 DTF频域 图像.
read_dtf_3		in_file													在窗口中预览图片的 DTF频域 图像，三通道.

[辅助功能]
resize			in_file		out_file	w			h					重设图像大小（缩放）.
mirrorX			in_file		out_file						(m_x)		图片X轴镜像（水平翻转）.
mirrorY			in_file		out_file						(m_y)		图片Y轴镜像（垂直翻转）.

*/

int act(int argc, char *argv[])
{
	std::cout << " hinaLayer - ver1.0 -  \n Simple Steganography tool \n (C)2015 BGLL\n\n\n";
	std::cout << "[自动隐写]\ns_in  in_file info_file out_file rgb_ (steg_write_file_lsb) 在图片中隐写文件(LSB).\ns_out  in_file out_file/dir rgb_  (steg_out_file_lsb) 导出图片中隐写的文件(LSB).\n\n[奇偶位]\nen_eo_mask in_file info_file out_file rgb_ (en_mig) 在图片奇偶位上写入水印\nen_eo_file in_file info_file out_file rgb_ (en_bin) 在图片奇偶位上写入文件.\nde_eo_mask in_file out_file rgb_  (de_mig) 导出图片奇偶位水印.\nde_eo_file in_file out_file rgb_  (de_bin) 导出图片奇偶位文件.\nread_eo  in_file rgb    (read_mig) 在窗口中预览图片的奇偶位图像.\n\n[低像素位]\nen_lsb_file in_file info_file out_file rgb_ (en_bin_A) 在图片像素低位上写入文件.\nde_lsb_file in_file out_file rgb_  (de_bin_A) 导出图片像素低位文件.\n\n[频域]\nen_dtf_mask in_file info_file out_file rgb (en_dtf) 在图片DTF频域上写入水印.\nde_dtf_mask in_file out_file rgb   (de_dtf) 导出图片DTF频域水印.\nread_dtf in_file rgb      在窗口中预览图片的 DTF频域 图像.\nread_dtf_3 in_file       在窗口中预览图片的 DTF频域 图像，三通道.\n\n[辅助功能]\nresize  in_file out_file w  h   重设图像大小（缩放）.\nmirrorX  in_file out_file   (m_x) 图片X轴镜像（水平翻转）.\nmirrorY  in_file out_file   (m_y) 图片Y轴镜像（垂直翻转）.\n\n*/";


	for (int a = 0; a < argc; a++)
	{
		std::cout << a << "/" << argc << ":" << argv[a] << "\n";
	}


	string com;
	string comb, comb2;

	if (argc >= 2)
		com = argv[1];

	std::cout << "\n-----------------\n";
	if (argc == 6)
	{//en_mig  in_flie info_img out_flie  rgb 
		comb = "en_mig";
		comb2 = "en_eo_mask";

		if (com == comb || com == comb2)
		{
			std::cout << "[en_eo_mask(en_mig)]\n";
			en_eo_mask(argv[2], argv[3], argv[4], atoi(argv[5]));
		}
	}

	if (argc == 4)
	{//read_mig in_flie rgb
		comb = "read_mig";
		comb2 = "read_eo";
		if (com == comb || com == comb2)
		{
			std::cout << "[read_eo(read_mig)]\n";
			read_eo(argv[2], atoi(argv[3]));
		}
	}

	if (argc == 5)
	{//de_mig  in_flie  out_flie rgb
		comb = "de_mig";
		comb2 = "de_eo_mask";
		if (com == comb || com == comb2)
		{
			std::cout << "de_eo_mask(de_mig)\n";
			de_eo_mask(argv[2], argv[3], atoi(argv[4]));
		}
	}

	if (argc == 5)
	{//en_bin in_image_flie  info_bin 
		comb = "en_bin";
		comb2 = "en_eo_file";
		if (com == comb || com == comb2)
		{
			std::cout << "en_eo_file(en_bin)\n";
			en_eo_file(argv[2], argv[3], argv[4]);
		}
	}
	if (argc == 6)
	{//== en_bin in_image_flie  info_bin rgb
		comb = "en_bin";
		comb2 = "en_eo_file";
		if (com == comb || com == comb2)
		{
			std::cout << "en_eo_file(en_bin)\n";
			en_eo_file(argv[2], argv[3], argv[4], atoi(argv[5]));
		}
	}


	if (argc == 5)
	{//en_bin_A in_image_flie  info_bin 
		comb = "en_bin_A";
		comb2 = "en_lsb_file";
		if (com == comb || com == comb2)
		{
			std::cout << "en_lsb_file(en_bin_A)\n";
			en_lsb_file(argv[2], argv[3], argv[4]);
		}
	}
	if (argc == 6)
	{//==en_bin_A in_image_flie  info_bin  rgb
		comb = "en_bin_A";
		comb2 = "en_lsb_file";
		if (com == comb || com == comb2)
		{
			std::cout << "en_lsb_file(en_bin_A)\n";
			en_lsb_file(argv[2], argv[3], argv[4], atoi(argv[5]));
		}
	}


	if (argc == 4)
	{//de_bin in_image_flie	out_file
		comb = "de_bin";
		comb2 = "de_eo_file";
		if (com == comb || com == comb2)
		{
			std::cout << "de_eo_file(de_bin)\n";
			de_eo_file(argv[2], argv[3]);
		}
	}
	if (argc == 5)
	{//== de_bin in_image_flie	out_file rgb
		comb = "de_bin";
		comb2 = "de_eo_file";
		if (com == comb || com == comb2)
		{
			std::cout << "de_eo_file(de_bin)\n";
			de_eo_file(argv[2], argv[3], atoi(argv[4]));
		}
	}




	if (argc == 4)
	{//en_bin_A in_image_flie out_file
		comb = "de_bin_A";
		comb2 = "de_lsb_file";
		if (com == comb || com == comb2)
		{
			std::cout << "de_lsb_file(de_bin_A)\n";
			de_lsb_file(argv[2], argv[3]);
		}
	}
	if (argc == 5)
	{//== en_bin_A in_image_flie out_file rgb
		comb = "de_bin_A";
		comb2 = "de_lsb_file";
		if (com == comb || com == comb2)
		{
			std::cout << "de_lsb_file(de_bin_A)\n";
			de_lsb_file(argv[2], argv[3], atoi(argv[4]));
		}
	}


	if (argc == 4)
	{//read_dtf in_flie rgb 
		comb = "read_dtf";
		comb2 = "read_dtf";
		if (com == comb || com == comb2)
		{
			std::cout << "read_dtf(read_dtf)\n";
			read_dtf(argv[2], atoi(argv[3]));
		}
	}

	if (argc == 3)
	{//read_dtf_3 in_flie 
		comb = "read_dtf_3";
		if (com == comb)
		{
			std::cout << "read_dtf_3\n";
			read_dtf(argv[2], 3);
		}
	}

	if (argc == 6)
	{//en_dtf in_f info_f out_f rgb 
		comb = "en_dtf";
		comb2 = "en_dtf_mask";
		if (com == comb || com == comb2)
		{
			std::cout << "en_dtf_mask(en_dtf)\n";
			en_dtf_mask(argv[2], argv[3], argv[4], atoi(argv[5]));
		}
	}

	if (argc == 5)
	{//de_dtf in_f out_f rgb 
		comb = "de_dtf";
		comb2 = "de_dtf_mask";
		if (com == comb || com == comb2)
		{
			std::cout << "de_dtf_mask(de_dtf)\n";
			de_dtf_mask(argv[2], argv[3], atoi(argv[4]));
		}
	}

	if (argc == 5)
	{//en_dtf_3 in_f info_f out_f  
		comb = "en_dtf_3";
		if (com == comb)
		{
			std::cout << "en_dtf_3\n";
			en_dtf_mask(argv[2], argv[3], argv[4], 3);
		}
	}


	if (argc == 4)
	{//de_dtf_3  in_f out_f 
		comb = "de_dtf_3";
		if (com == comb)
		{
			std::cout << "de_dtf_3\n";
			de_dtf_mask(argv[2], argv[3], 3);
		}
	}

	if (argc == 6)
	{//resize in_f out_f w h
		comb = "resize";
		if (com == comb)
		{
			std::cout << "resize\n";
			resize(argv[2], argv[3], atoi(argv[4]), atoi(argv[5]));
		}
	}

	if (argc == 4)
	{//mirrorX in_f out_f
		comb = "mirrorX";
		comb2 = "m_x";
		if (com == comb || com == comb2)
		{
			std::cout << "m_x(mirrorX)\n";
			mirrorX(argv[2], argv[2]);
		}
	}
	if (argc == 4)
	{//mirrorX in_f out_f
		comb = "mirrorY";
		comb2 = "m_y";
		if (com == comb || com == comb2)
		{
			std::cout << "m_y(mirrorY)\n";
			mirrorY(argv[2], argv[2]);
		}
	}


	if (argc == 6)
	{//steg_write_file_lsb  rgb
		comb = "steg_write_file_lsb";
		comb2 = "s_in";
		if (com == comb || com == comb2)
		{
			std::cout << "s_in(steg_write_file_lsb)\n";
			steg_write_file_lsb(argv[2], argv[3], argv[4], atoi(argv[5]));
		}
	}
	if (argc == 5)
	{// ==steg_write_file_lsb  
		comb = "steg_write_file_lsb";
		comb2 = "s_in";
		if (com == comb || com == comb2)
		{
			std::cout << "s_in(steg_write_file_lsb)\n";
			steg_write_file_lsb(argv[2], argv[3], argv[4], 3);
		}
	}


	if (argc == 5)
	{//steg_write_file_lsb  rgb
		comb = "steg_out_file_lsb";
		comb2 = "s_out";
		if (com == comb || com == comb2)
		{
			std::cout << "s_out(steg_out_file_lsb)\n";
			steg_out_file_lsb(argv[2], argv[3], atoi(argv[4]));
		}
	}
	if (argc == 4)
	{//== steg_write_file_lsb 
		comb = "steg_out_file_lsb";
		comb2 = "s_out";
		if (com == comb || com == comb2)
		{
			std::cout << "s_out(steg_out_file_lsb)\n";
			steg_out_file_lsb(argv[2], argv[3], 3);
		}
	}
	return 0;
}

































