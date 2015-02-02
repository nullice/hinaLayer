#include <iostream>
#include "hinaLayer.h"


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


int 