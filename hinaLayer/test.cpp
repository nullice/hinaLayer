#include "hinaLayer.h"
#include "hinaLayer_comd.h"
//C++
#include <iostream>
#include <string>
#include<bitset>
#include<fstream>
#include<math.h>
using namespace std;



int main(int argc, char *argv[])
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




