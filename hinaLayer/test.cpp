#include <iostream>
#include "hinaLayer.h"
//C++
#include <iostream>
#include <string>
#include<bitset>
#include<fstream>
#include<math.h>
using namespace std;


int main()
{
	cout<<11;
	hinaLayer j;
	j.open_file("rr.jpg");
	j.show("打开文件");

	//j.eo_write_mask("aaa.png",2);
	//j.show_eo("写入奇偶水印");

	//j.eo_to_image(3);
	//j.show();
	//j.show_eo();




	//j.lsb_write_file("test.txt");
	//j.lsb_out_file("1.txt");
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
	
	
}


