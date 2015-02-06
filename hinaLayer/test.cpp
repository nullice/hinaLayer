#include "hinaLayer.h"
#include "hinaLayer_comd.h"
//C++
#include <iostream>
#include <string>
#include<bitset>
#include<fstream>
#include<math.h>
using namespace std;

int act()
{




}




//----【奇偶位】处理
//en_mig  in_flie info_img out_flie  rgb  图片编码写入
//de_mig  in_flie  out_flie rgb	图片解码写出
//read_mig in_flie rgb 显示隐藏图片内容

//en_bin in_image_flie  info_bin 文件编码写入
//de_bin in_image_flie	info_bin 文件编码写出

//en_bin_A in_image_flie  info_bin 自适应深度文件编码写入
//en_bin_A in_image_flie	info_bin 自适应深度文件编码写出


//----【dtf频域】处理
//read_dtf in_flie rgb 显色图片指定通道dtf频域
//read_dtf_3 in_flie 显色图片3通道dtf频域

//en_dtf in_f info_f out_f rgb 图片指定通道dtf频域信息写入
//de_dtf in_f out_f rgb 图片指定通道dtf频域信息写出

//en_dtf_3 in_f info_f out_f  图片3通道dtf频域信息写入
//de_dtf_3  in_f out_f 图片3通道dtf频域信息写出

//----【其他】处理
//resize in_f out_f w h




/*
[奇偶位]
en_eo_mask		in_file		info_file	out_file	rgb_	(en_mig)	在图片奇偶位上写入水印
en_eo_file		in_file		info_file	out_file	rgb_	(en_bin)	在图片奇偶位上写入文件.
de_eo_mask		in_file		out_file	rgb_				(de_mig)	导出图片奇偶位水印.
de_eo_file		in_file		out_file	rgb_				(de_bin)	导出图片奇偶位文件.
read_eo			in_file		rgb								(read_mig)

[低像素位]
en_lsb_file		in_file		info_file	out_file	rgb_	(en_bin_A)	在图片像素低位上写入文件.
de_lsb_file		in_file		out_file	rgb_				(de_bin_A)	导出图片像素低位文件.

[频域]
en_dtf_mask		in_file		info_file	out_file	rgb		(en_dtf)	在图片DTF频域上写入水印.
de_dtf_mask		in_file		out_file	rgb					(de_dtf)	导出图片DTF频域水印.
read_dtf		in_file		rgb
read_dtf_3		in_file

[辅助功能]
resize			in_file		out_file	w			h					重设图像大小（缩放）.
mirrorX			in_file		out_file						(m_x)		图片X轴镜像（水平翻转）.
mirrorY			in_file		out_file						(m_y)		图片Y轴镜像（垂直翻转）.

*/
















int main(int argc, char *argv[])
{

	std::cout << " hinaLayer - ver0.8 -  \n Simple Steganography tool \n (C)2014 BGLL\n\n\n";
	std::cout << "-----奇偶位处理-----\nen_mig  in_flie info_img out_flie  rgb  图片编码写入\nde_mig  in_flie  out_flie rgb	图片解码写出\nread_mig in_flie rgb 显示隐藏图片内容\n\nen_bin in_image_flie  info_bin 文件编码写入\nde_bin in_image_flie	info_bin 文件编码写出\n\nen_bin_A in_image_flie  info_bin 自适应深度文件编码写入\nen_bin_A in_image_flie	info_bin 自适应深度文件编码写出\n\n-----DTF频域处理-----\nread_dtf in_flie rgb 显色图片指定通道dtf频域\nread_dtf_3 in_flie 显色图片3通道dtf频域\n\nen_dtf in_f info_f out_f rgb 图片指定通道dtf频域信息写入\nde_dtf in_f out_f rgb 图片指定通道dtf频域信息写出\n\nen_dtf_3 in_f info_f out_f  图片3通道dtf频域信息写入\nde_dtf_3  in_f out_f 图片3通道dtf频域信息写出\n\n-----其他处理-----\nresize in_f out_f w h\n\n";


	for (int a = 0; a < argc; a++)
	{
		std::cout << a << "/" << argc << ":" << argv[a] << "\n";
	}


	string com;
	string comb,comb2;

	if (argc >= 2)
		com = argv[1];

	std::cout << "\n-----------------\n";
	if (argc == 6)
	{//en_mig  in_flie info_img out_flie  rgb 
		comb = "en_mig";
		comb2 = "en_eo_mask";

		if (com == comb || com == comb2 || com == comb || com == comb22)
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
			read_dtf(argv[2],3);
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

	










	//en_eo_mask("test\\rr.jpg", "test\aaa.png", "test\out.png",2);
	//de_eo_mask("test\out.png", "test\out2.png", 3);
	//std::cout<<"奇偶位写入水印测试"

	//en_eo_file("test\\rr.jpg", "test\\test.txt", "test\\out.png", 3);
	//de_eo_file("test\\out.png", "test\\out2.txt", 3);
	//std::cout<<"奇偶位写入文件测试"

	//en_lsb_file("test\\rr.jpg", "test\\test.txt", "test\\out.png", 3);
	//de_lsb_file("test\\out.png", "test\\out2.txt", 3);
	//std::cout<<"像素低位位写入文件测试"

	//en_dtf_mask("test\\oo.jpg", "test\\pp2.png", "test\\out.png", 2);
	//de_dtf_mask("test\\out.png", "test\\out2.png", 3);
	//std::cout << "dtf频域写入水印测试";

	//resize("test\\oo.jpg", "test\\out.jpg",303,230);
	//mirrorX("test\\out.jpg", "test\\out2.jpg");
	//mirrorY("test\\out2.jpg", "test\\out3.jpg");
	//std::cout << "辅助功能测试";


	//de_lsb_file("test\\b2.png", "test\\b2_out.exe", 3);
	//de_lsb_file("test\\b3.png", "test\\b3_out.exe", 3);
	//en_lsb_file("test\\b.png","test\\1.exe", "test\\b_insfile.png", 3);
	//de_lsb_file("test\\2.png", "test\\22.exe", 3);
	//de_lsb_file("test\\2.png", "test\\22.exe", 3);
	//string a;
	//hide_file("test\\p4.png", "test\\R",3,a);
	//cout << a << endl;
	//hide_file("test\\2.png", "test\\R\\oo.exe", 3,a);
	//cout << a << endl;


	//steg_write_file_lsb("test\\b.png", "test\\R\\1.zip", "test\\R\\b_out.png", 3);

	//steg_out_file_lsb("test\\R\\b_out.png", "test\\R", 3);
	getchar();

}
















/*
int main()
{
	cout<<11;
	hinaLayer j;
	j.open_file("rr.jpg");
	j.show("打开文件");
	
	//j.eo_write_mask("aaa.png");
	//j.show_eo("写入奇偶水印");

	//j.eo_write_file("test.txt",2);
	//j.eo_out_file("1.txt",2);

	//j.eo_to_image(3);

	//j.show();
	//j.show_eo();



	//j.lsb_write_file("test.txt",0);
	//j.lsb_out_file("1.txt",0);
	//j.show("结果");
	//cout << endl <<"深度："<< j.lsb_get_deep("test.txt") << endl;
	//cout <<"最大尺寸："<< (j.lsb_get_max()) / 1000 << "KB" << endl;

	getchar();

	/*
	j.dtf_make(2);
	j.dtf_write_mask("pp2.png",2);
	//j.dtf_inverse_make(2);
	j.dtf_print(2);
	j.show_fdomain("2");
	j.show("nwe");
	*/	
//} 




