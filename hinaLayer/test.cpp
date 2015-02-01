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
	j.eo_write_mask("aaa.png");
	j.show_eo("写入奇偶水印");
	/*
	j.dtf_make(2);
	j.dtf_write_mask("pp2.png",2);
	//j.dtf_inverse_make(2);
	j.dtf_print(2);
	j.show_fdomain("2");
	j.show("nwe");
	*/
	
	
}


