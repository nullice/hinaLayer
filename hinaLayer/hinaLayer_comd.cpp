#include <iostream>
#include <string>
#include<bitset>
#include<fstream>
#include "hinaLayer.h"
#include <vector>
#include <algorithm>


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




/// <summary>
/// 在图片奇偶位上写入水印.
/// </summary>
/// <param name="in_file">要写入水印的图片文件.</param>
/// <param name="mask_file">作为水印的图片文件.</param>
/// <param name="out_file">保存结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int en_eo_mask(char* in_file, char* mask_file, char* out_file, int rgb)
{
	hinaLayer h;
	h.open_file(in_file);
	h.eo_write_mask(mask_file, rgb);
	h.out_file(out_file);
	return 0;
}

/// <summary>
/// 在图片奇偶位上写入文件.
/// </summary>
/// <param name="in_file">要写入文件的图片文件.</param>
/// <param name="info_file">作为写入信息的文件.</param>
/// <param name="out_file">保存结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int en_eo_file(char* in_file, char* info_file, char* out_file, int rgb)
{
	hinaLayer h;
	h.open_file(in_file);
	h.eo_write_file(info_file, rgb);
	h.out_file(out_file);
	return 0;
}

/// <summary>
/// 在图片像素低位上写入文件.
/// </summary>
/// <param name="in_file">要写入文件的图片文件.</param>
/// <param name="info_file">作为写入信息的文件.</param>
/// <param name="out_file">保存结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int en_lsb_file(char* in_file, char* info_file, char* out_file, int rgb)
{
	hinaLayer h;
	h.open_file(in_file);
	h.lsb_write_file(info_file, rgb);
	h.out_file(out_file);
	return 0;
}

/// <summary>
/// 在图片DTF频域上写入水印.
/// </summary>
/// <param name="in_file">要写入水印的图片文件.</param>
/// <param name="mask_file">作为水印的图片文件.</param>
/// <param name="out_file">保存结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int en_dtf_mask(char* in_file, char* mask_file, char* out_file, int rgb)
{
	hinaLayer h;
	h.open_file(in_file);
	h.dtf_make(3);
	h.dtf_write_mask(mask_file, rgb);
	h.dtf_inverse_make(3);
	h.out_file(out_file);
	return 0;
}



/// <summary>
/// 导出图片奇偶位水印.
/// </summary>
/// <param name="in_file">要导出水印的图片文件.</param>
/// <param name="out_file">保存导出结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int de_eo_mask(char* in_file, char* out_file, int rgb)
{
	hinaLayer h;
	h.open_file(in_file);
	h.eo_to_image(rgb);
	h.out_file(out_file);
	return 0;
}

/// <summary>
/// 导出图片奇偶位文件.
/// </summary>
/// <param name="in_file">要导出文件的图片文件.</param>
/// <param name="out_file">保存导出结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int de_eo_file(char* in_file, char* out_file, int rgb)
{
	hinaLayer h;
	h.open_file(in_file);
	h.eo_out_file(out_file, rgb);
	return 0;
}

/// <summary>
/// 导出图片像素低位文件.
/// </summary>
/// <param name="in_file">要导出文件的图片文件.</param>
/// <param name="out_file">保存导出结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int de_lsb_file(char* in_file, char* out_file, int rgb)
{
	hinaLayer h;
	h.open_file(in_file);
	h.lsb_out_file(out_file, rgb);
	return 0;
}

/// <summary>
/// 导出图片DTF频域水印.
/// </summary>
/// <param name="in_file">要导出水印的图片文件</param>
/// <param name="out_file">保存导出结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int de_dtf_mask(char* in_file, char* out_file, int rgb)
{
	hinaLayer h;
	h.open_file(in_file);
	h.dtf_make(rgb);
	h.dtf_print(rgb);
	h.out_file_fdomain(out_file);
	return 0;
}


/// <summary>
/// 重设图像大小（缩放）.
/// </summary>
/// <param name="in_file">要进行处理图片文件.</param>
/// <param name="out_file">保存处理结果的图片文件.</param>
/// <param name="w">图片新的宽度.</param>
/// <param name="h">图片新的高度.</param>
void resize(char* in_file, char* out_file, int w, int h)
{
	hinaLayer hl;
	hl.open_file(in_file);
	hl.resize(w, h);
	hl.out_file(out_file);
}

/// <summary>
/// 图片Y轴镜像（垂直翻转）.
/// </summary>
/// <param name="in_file">要进行处理图片文件.</param>
/// <param name="out_file">保存处理结果的图片文件.</param>
void mirrorY(char* in_file, char* out_file)
{
	hinaLayer hl;
	hl.open_file(in_file);
	hl.mirrorY();
	hl.out_file(out_file);
}

/// <summary>
/// 图片X轴镜像（水平翻转）.
/// </summary>
/// <param name="in_file">要进行处理图片文件.</param>
/// <param name="out_file">保存处理结果的图片文件.</param>
void mirrorX(char* in_file, char* out_file)
{
	hinaLayer hl;
	hl.open_file(in_file);
	hl.mirrorX();
	hl.out_file(out_file);
}



//=====================================================================================
//文件隐写功能：
//=====================================================================================


int hide_file(char* in_file, char* out_file, int rgb)
{
	using namespace std;
	//de_lsb_file(in_file, out_file, rgb);



	//_DEBUG ifstream in(out_file, ios::binary);
	ifstream in(in_file, ios::binary);

	//载入文件
	if (!in)
	{
		cerr << "open error!" << endl;
		abort();
	}

	in.seekg(0, ios::end);
	//in.tellg();//计算文件大小
	in.seekg(0, ios::beg);


	wstring data;

	for (unsigned long i; true != in.eof(); i++)
	{
		data.push_back(in.get());
	}
	cout << (unsigned int)data[0];
	
	ofstream out(out_file, ios::binary);

	
	wstring::iterator it;
	it = data.begin();
	for (unsigned long i; it != data.end(); it++)
	{
		out.put((*it));

	}


}







int main()
{
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


	//de_lsb_file("test\\rr_INfile1.png", "test\\outttttttt.txt", 3);
	hide_file("test\\1.zip", "test\\2.zip",3);
	getchar();

}


