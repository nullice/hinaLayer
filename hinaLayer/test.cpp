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




int main(int argc, char *argv[])
{

	bit_f_write_A(info_f, image);
	imwrite(out_f, image);

}

void com_de_bin_A(char* in_f, char* out_f)
{
	void bit_f_decode_A(Mat& image, char* filename);
	auto image = imread(in_f);
	bit_f_decode_A(image, out_f);

}

void bit_f_write(char* filename, Mat& image)
{
	using namespace std;



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
void bit_f_write_A(char* filename, Mat& image)
{
	using namespace std;
	ifstream in(filename, ios::binary);


	//载入文件
	if (!in)
	{
		cerr << "open error!" << endl;
		abort();
	}

	int tmp;//
	char* buffer;
	long size;

	in.seekg(0, ios::end);
	size = in.tellg();//计算文件大小
	//cout<<size<<endl;
	in.seekg(0, ios::beg);



	bitset<8> bit;
	bitset<8> bit_temp;


	for (int i = 0; i < size; i++)
	{
		bit = in.get();
	}

	//----------------------
	int nl = image.rows; // number of lines  
	int nc = image.cols; // number of columns  

	//预处理，计算嵌入深度2~8
	long pxbit = nl*nc * 3;
	int deep = 2;
	double f = 0;

	f = (double)size / (double)((double)pxbit / 8);
	cout << "size:" << size << endl;
	cout << "pxbit/8:" << (double)pxbit / 8 << endl;

	cout << f << endl;
	if (((f * 1000000 - (int)f * 1000000)) > 0)
	{
		f = f + 1.0;
	}

	deep = f;
	if (deep <= 0)deep = 8;
	if (deep > 8)deep = 8;
	if (deep < 2)deep = 2;

	cout << "计算深度：" << deep << endl;

	//写入嵌入深度
	int i = image.at<cv::Vec3b>(0, 0)[0];
	if (i >= 250 || deep == 8) i = i - 10;
	image.at<cv::Vec3b>(0, 0)[0] = i - i % 100 % 10 + deep - 2;


	int cheak = 0;
	int pass = 0;

	in.seekg(0, ios::beg);
	bit = in.get();
	long rrr = 0;
	for (int j = 0; j < nl; j++) {
		for (int i = 0; i < nc; i++)
		{

			if (pass <= size && (j + i > 0))
			{
				for (int p = 0; p < 3; p++)
				{//--------------------------------------------

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

				}//--------------------------------------------
			}

		}
	}

	cout << rrr;
}


void bit_f_decode_A(Mat& image, char* filename)
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

	deep = image.at<cv::Vec3b>(0, 0)[0];
	deep = deep % 100 % 10 + 2;

	if (deep > 8)deep = 8;
	cout << "判断深度:" << deep;


	char t;
	for (int j = 0; j < nl; j++)
	{
		for (int i = 0; i < nc; i++)
		{
			if (i + j > 0)
			{
				for (int p = 0; p < 3; p++)
				{//------------------------
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

			}//------------------------
		}
	}


	in.close();

}



void bit_f_decode(Mat& image, char* filename)
{

	using namespace std;

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

	in.close();

}




void com_read_dtf(char* in_f, int rgb)
{
	Mat in[3], mmat, idft_mat;
	auto image = imread(in_f);
	split(image, in);

	make_mmat(in[rgb], mmat);
	dft(mmat, mmat);
	show_dft(mmat, idft_mat);
	show(idft_mat);


}

void com_read_dtf_3(char* in_f)
{
	Mat in[3], mmat, idft_mat;
	auto image = imread(in_f);
	split(image, in);

	for (int p = 0; p < 3; p++)
	{
		make_mmat(in[p], mmat);
		dft(mmat, mmat);
		show_dft(mmat, in[p]);
	}
	merge(in, 3, idft_mat);
	show(idft_mat);

}


void com_de_dtf(char* in_f, char* out_f, int rgb)
{
	Mat in[3], mmat, idft_mat;
	auto image = imread(in_f);
	split(image, in);

	make_mmat(in[rgb], mmat);
	dft(mmat, mmat);
	show_dft(mmat, idft_mat);
	imwrite(out_f, idft_mat * 255);

}

void com_de_dtf_3(char* in_f, char* out_f)
{
	Mat in[3], mmat, idft_mat;
	auto image = imread(in_f);
	split(image, in);

	for (int p = 0; p < 3; p++)
	{
		make_mmat(in[p], mmat);
		dft(mmat, mmat);
		show_dft(mmat, in[p]);
	}
	merge(in, 3, idft_mat);

	imwrite(out_f, idft_mat * 255);

}

void en_dtf_main(char* in_f, char* in_info, Mat& out, int rgb)
{
	Mat in[3], mmat, idft_mat;
	auto image = imread(in_f);
	split(image, in);

	make_mmat(in[rgb], mmat);
	dft(mmat, mmat);
	show_dft(mmat, idft_mat);

	writeINFO(mmat, in_info);
	show_dft(mmat, idft_mat);

	//imshow("写信息", idft_mat);
	//waitKey(0);


	idft(mmat, idft_mat);
	show_idft(idft_mat, image, idft_mat);

	//std::cout<<idft_mat;

	idft_mat = idft_mat * 255;
	idft_mat.convertTo(in[rgb], in[rgb].type());

	//show(in[rgb]);
	merge(in, 3, out);
}

void com_en_dtf(char* in_f, char* in_info, char* out_f, int rgb)
{

	Mat out;
	en_dtf_main(in_f, in_info, out, rgb);

	imwrite(out_f, out);

}


void com_en_dtf_3(char* in_f, char* in_info, char* out_f)
{
	Mat out[3];
	Mat outimg;
	Mat temp[3];


	for (int p = 0; p < 3; p++)
	{
		en_dtf_main(in_f, in_info, out[p], p);
		split(out[p], temp);
		temp[p].copyTo(out[p]);
	}


	merge(out, 3, outimg);
	imwrite(out_f, outimg);



}


void com_resize(char* in_f, char* out_f, int w, int h)

{

	Mat in = imread(in_f);
	Mat big(w, h, in.type());

	resize(in, big, big.size(), 0, 0, CV_INTER_NN);

	big.copyTo(in);
	imwrite(out_f, in);


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





int main(int argc, char *argv[])
{

	std::cout << " hinaLayer - ver0.8 -  \n Simple Steganography tool \n (C)2014 BGLL\n\n\n";
	std::cout << "-----奇偶位处理-----\nen_mig  in_flie info_img out_flie  rgb  图片编码写入\nde_mig  in_flie  out_flie rgb	图片解码写出\nread_mig in_flie rgb 显示隐藏图片内容\n\nen_bin in_image_flie  info_bin 文件编码写入\nde_bin in_image_flie	info_bin 文件编码写出\n\nen_bin_A in_image_flie  info_bin 自适应深度文件编码写入\nen_bin_A in_image_flie	info_bin 自适应深度文件编码写出\n\n-----DTF频域处理-----\nread_dtf in_flie rgb 显色图片指定通道dtf频域\nread_dtf_3 in_flie 显色图片3通道dtf频域\n\nen_dtf in_f info_f out_f rgb 图片指定通道dtf频域信息写入\nde_dtf in_f out_f rgb 图片指定通道dtf频域信息写出\n\nen_dtf_3 in_f info_f out_f  图片3通道dtf频域信息写入\nde_dtf_3  in_f out_f 图片3通道dtf频域信息写出\n\n-----其他处理-----\nresize in_f out_f w h\n\n";


	for (int a = 0; a < argc; a++)
	{
		std::cout << a << "/" << argc << ":" << argv[a] << "\n";
	}


	string com;
	string comb;

	if (argc >= 2)
		com = argv[1];

	std::cout << "\n-----------------\n";
	if (argc == 6)
	{
		comb = "en_mig";////en_mig  in_flie info_img out_flie  rgb 

		if (com == comb)
		{
			std::cout << "en_mig\n";
			com_en_mig(argv[2], argv[3], argv[4], atoi(argv[5]));
		}
	}


	if (argc == 4)
	{
		comb = "read_mig";
		if (com == comb)
		{
			std::cout << "read_mig\n";
			com_read_mig(argv[2], atoi(argv[3]));
		}
	}

	if (argc == 5)
	{
		comb = "de_mig";
		if (com == comb)
		{
			std::cout << "de_mig\n";
			com_de_mig(argv[2], argv[3], atoi(argv[4]));
		}
	}

	if (argc == 5)
	{
		comb = "en_bin";
		if (com == comb)
		{
			std::cout << "en_bin\n";
			com_en_bin(argv[2], argv[3], argv[4]);
		}
	}
	if (argc == 5)
	{
		comb = "en_bin_A";
		if (com == comb)
		{
			std::cout << "en_bin_A\n";
			com_en_bin_A(argv[2], argv[3], argv[4]);
		}
	}

	if (argc == 4)
	{
		comb = "de_bin";
		if (com == comb)
		{
			std::cout << "de_bin\n";
			com_de_bin(argv[2], argv[3]);
		}
	}

	if (argc == 4)
	{
		comb = "de_bin_A";
		if (com == comb)
		{
			std::cout << "de_bin_A\n";
			com_de_bin_A(argv[2], argv[3]);
		}
	}



	if (argc == 4)
	{
		comb = "read_dtf";
		if (com == comb)
		{
			std::cout << "read_dtf\n";
			com_read_dtf(argv[2], atoi(argv[3]));
		}
	}

	if (argc == 3)
	{
		comb = "read_dtf_3";
		if (com == comb)
		{
			std::cout << "read_dtf_3\n";
			com_read_dtf_3(argv[2]);
		}
	}

	if (argc == 6)
	{
		comb = "en_dtf";
		if (com == comb)
		{
			std::cout << "en_dtf\n";
			com_en_dtf(argv[2], argv[3], argv[4], atoi(argv[5]));
		}
	}

	if (argc == 5)
	{
		comb = "de_dtf";
		if (com == comb)
		{
			std::cout << "de_dtf\n";
			com_de_dtf(argv[2], argv[3], atoi(argv[4]));
		}
	}

	if (argc == 5)
	{
		comb = "en_dtf_3";
		if (com == comb)
		{
			std::cout << "en_dtf_3\n";
			com_en_dtf_3(argv[2], argv[3], argv[4]);
		}
	}


	if (argc == 4)
	{
		comb = "de_dtf_3";
		if (com == comb)
		{
			std::cout << "de_dtf_3\n";
			com_de_dtf_3(argv[2], argv[3]);
		}
	}

	if (argc == 6)
	{
		comb = "resize";
		if (com == comb)
		{
			std::cout << "resize\n";
			com_resize(argv[2], argv[3], atoi(argv[4]), atoi(argv[5]));
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


	steg_write_file_lsb("test\\b.png", "test\\R\\1.zip", "test\\R\\b_out.png", 3);

	steg_out_file_lsb("test\\R\\b_out.png", "test\\R", 3);
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




