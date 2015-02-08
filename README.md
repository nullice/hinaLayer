# hinaLayer

![](https://github.com/nullice/hinaLayer/raw/master/about/hinaLayer_logo_0.5X.png)

simple and convenient
Image steganography tool

with C++ &amp; openCV

Window GUI App [imageIN](http://nullice.com/imagein) used hinaLayer. ( here hinaLayer is  Console Application)


##介绍
hinaLayer 是一个使用 C++ 语言，依赖 openCV 库的非常简单的隐写工具<br>
原本是为一个有着极友好界面的图片隐写工具 [imageIN](http://nullice.com/imagein) 写的临时用的组件
后来 [imageIN](http://nullice.com/imagein) 源码不幸丢失了:no_mouth:<br>
[imageIN](http://nullice.com/imagein)的截图：<br>
![](http://nullice.com/wordpress/wp-content/uploads/2014/11/anime.gif)<br>


##功能

**图片奇偶位写入、导出文件、水印**
<br>
根据图片像素值的奇偶性写入文件或水印

**图片像素低位写入、导出文件**
<br>
根据图像像素低位内容写入信息，即 LSB 隐写

**在图片频域（DTF）写入、导出水印**
<br>
把图片转换到 DTF 频域，并写入水印图片

**隐写文件**
<br>
在图片中写入或导出文件，使用的是图片像素低位，与此不同的是会记录原文件大小与文件名



##hinaLayer.exe
hinaLayer.exe 是在 windows 下的静态编译版本（使用时不需要机器上有 openCV ）

`in_file` 是输入文件，`info_file` 是作为写入内容的文件，`out_file` 是输出文件，`rgb`是色彩通道（012顺序BGR，3为使用全部通道），`rgb_`表示可以忽略色彩通道参数，使用默认值3


| 命令名 | 参数1 | 参数2 | 参数3 | 参数4 | 别名 | 功能 |
| :------------- | :------------- | :------------- | ------------- | ------------- | ------------- | --------- |
| s_in | in_file | info_file | out_file | rgb_ | (steg_write_file_lsb) | 在图片中隐写文件(LSB).
| s_out | in_file | out_file/dir | rgb_ |  | (steg_out_file_lsb)  | ( 导出图片中隐写的文件(LSB).
| [奇偶位]
| en_eo_mask | in_file | info_file | out_file | rgb_ | (en_mig) | 在图片奇偶位上写入水印
| en_eo_file | in_file | info_file | out_file | rgb_ | (en_bin) | 在图片奇偶位上写入文件.
| de_eo_mask | in_file | out_file | rgb_ | | (de_mig)   | 导出图片奇偶位水印.
| de_eo_file | in_file | out_file | rgb_ | |  (de_bin)   | 导出图片奇偶位文件.
| read_eo | in_file | rgb | ||  (read_mig) |在窗口中预览图片的奇偶位图像.
| [低像素位]
| en_lsb_file | in_file | info_file | out_file | rgb_ | (en_bin_A) | 在图片像素低位上写入文件.
| de_lsb_file | in_file | out_file | rgb_ ||  (de_bin_A)   |导出图片像素低位文件.
| [频域]
| en_dtf_mask | in_file | info_file | out_file | rgb | (en_dtf) | 在图片DTF频域上写入水印.
| de_dtf_mask | in_file | out_file | rgb | | (de_dtf)  |导出图片DTF频域水印.
| read_dtf | in_file | rgb |  | | |在窗口中预览图片的 DTF频域 图像.
| read_dtf_3 | in_file | |  | | |在窗口中预览图片的 DTF频域图像，三通道.
| [辅助功能]
| resize | in_file | out_file | w | h |  |重设图像大小（缩放）.
| mirrorX | in_file | out_file | | | (m_x) | 图片X轴镜像（水平翻转）.
| mirrorY | in_file | out_file | | | (m_y) | 图片Y轴镜像（垂直翻转）.



##源码说明
本项目依赖 [ openCV 2.4.10 ](http://opencv.org/downloads.html)，构建于 Visual Studio 2013 可参考[ 这个配置说明 ](https://github.com/nullice/hinaLayer/tree/master/openCV_%E9%85%8D%E7%BD%AE)

`hinaLayer.h 与 hinaLayer.cpp` 中封装了对图片所有进行隐写操作的类

`hinaLayer_comd.h 与 hinaLayer_comd.cpp` 封装了直接调用的方法

`hinaLayer_Console.cpp` 是编译成 windows 下控制台程序的相关内容




#License
<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />本作品采用<a rel="license" href="http://creativecommons.org/licenses/by/4.0/">知识共享署名 4.0 国际许可协议</a>进行许可。
