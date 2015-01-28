


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

	Mat image;//Í¼ÏñÊý¾Ý¾ØÕó
	int openfile(char* filename, int mono = 0);
	int writefile(char* filename);

	void resize(int w,int h);



	//out
};

#endif
