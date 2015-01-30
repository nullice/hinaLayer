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
	
	j.openfile("oo.jpg");
	j.mirrorX();
	j.mirrorY();
	j.show();
	j.dtf_make();
	//j.dtf_print();
	j.dtf_inverse_make();
	imshow("Ð´ÐÅÏ¢", j.mmat[1]);
	waitKey(0);

	j.dtf_show();
	
	
}


