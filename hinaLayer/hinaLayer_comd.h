#ifndef HINALAYER_COMD_H
#define HINALAYER_COMD_H

#include <string>


/// <summary>
/// 在图片奇偶位上写入水印.
/// </summary>
/// <param name="in_file">要写入水印的图片文件.</param>
/// <param name="mask_file">作为水印的图片文件.</param>
/// <param name="out_file">保存结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int en_eo_mask(char* in_file, char* mask_file, char* out_file, int rgb = 3);

/// <summary>
/// 在图片奇偶位上写入文件.
/// </summary>
/// <param name="in_file">要写入文件的图片文件.</param>
/// <param name="info_file">作为写入信息的文件.</param>
/// <param name="out_file">保存结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int en_eo_file(char* in_file, char* info_file, char* out_file, int rgb = 3);

/// <summary>
/// 在图片像素低位上写入文件.
/// </summary>
/// <param name="in_file">要写入文件的图片文件.</param>
/// <param name="info_file">作为写入信息的文件.</param>
/// <param name="out_file">保存结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int en_lsb_file(char* in_file, char* info_file, char* out_file, int rgb = 3);

/// <summary>
/// 在图片DTF频域上写入水印.
/// </summary>
/// <param name="in_file">要写入水印的图片文件.</param>
/// <param name="mask_file">作为水印的图片文件.</param>
/// <param name="out_file">保存结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int en_dtf_mask(char* in_file, char* mask_file, char* out_file, int rgb = 3);

/// <summary>
/// 导出图片奇偶位水印.
/// </summary>
/// <param name="in_file">要导出水印的图片文件.</param>
/// <param name="out_file">保存导出结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int de_eo_mask(char* in_file, char* out_file, int rgb = 3);

/// <summary>
/// 导出图片奇偶位文件.
/// </summary>
/// <param name="in_file">要导出文件的图片文件.</param>
/// <param name="out_file">保存导出结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int de_eo_file(char* in_file, char* out_file, int rgb = 3);

/// <summary>
/// 导出图片像素低位文件.
/// </summary>
/// <param name="in_file">要导出文件的图片文件.</param>
/// <param name="out_file">保存导出结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int de_lsb_file(char* in_file, char* out_file, int rgb = 3);

/// <summary>
/// 导出图片DTF频域水印.
/// </summary>
/// <param name="in_file">要导出水印的图片文件</param>
/// <param name="out_file">保存导出结果的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int de_dtf_mask(char* in_file, char* out_file, int rgb = 3);

/// <summary>
/// 重设图像大小（缩放）.
/// </summary>
/// <param name="in_file">要进行处理图片文件.</param>
/// <param name="out_file">保存处理结果的图片文件.</param>
/// <param name="w">图片新的宽度.</param>
/// <param name="h">图片新的高度.</param>
void resize(char* in_file, char* out_file, int w, int h);

/// <summary>
/// 图片Y轴镜像（垂直翻转）.
/// </summary>
/// <param name="in_file">要进行处理图片文件.</param>
/// <param name="out_file">保存处理结果的图片文件.</param>
void mirrorY(char* in_file, char* out_file);

/// <summary>
/// 图片X轴镜像（水平翻转）.
/// </summary>
/// <param name="in_file">要进行处理图片文件.</param>
/// <param name="out_file">保存处理结果的图片文件.</param>
void mirrorX(char* in_file, char* out_file);

/// <summary>
/// 在图片中隐写文件(LSB).
/// </summary>
/// <param name="in_file">要写入内容的图片文件.</param>
/// <param name="info_file">欲写入图片的文件.</param>
/// <param name="out_file">保存处理结果的图片文件.</param>
/// <param name="rgb">用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int steg_write_file_lsb(char* in_file, char* info_file, char* out_file, int rgb = 3);

/// <summary>
/// 获取图片中隐写的文件的文件名(LSB).
/// </summary>
/// <param name="in_file">图片文件.</param>
/// <param name="rgb">用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>string.</returns>
std::string steg_get_name_lsb(char* in_file, int rgb = 3);

/// <summary>
/// 导出图片中隐写的文件(LSB).
/// </summary>
/// <param name="in_file">图片文件.</param>
/// <param name="out_file">保存导出内容的文件夹或文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道）.</param>
/// <returns>int.</returns>
int steg_out_file_lsb(char* in_file, char* out_file, int rgb = 3);

/// <summary>
/// 在窗口中预览图片的奇偶位图像.
/// </summary>
/// <param name="in_file">要查看的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道).</param>
void read_eo(char* in_file, int rgb = 3);

/// <summary>
/// 在窗口中预览图片的 DTF频域 图像.
/// </summary>
/// <param name="in_file">要查看的图片文件.</param>
/// <param name="rgb">使用色彩通道（012顺序BGR，3为使用全部通道).</param>
void read_dtf(char* in_file, int rgb = 3);

/// <summary>
/// 判断文件类型，返回-1为不存在，0为文件，1为文件夹.
/// </summary>
/// <param name="filename">文件名.</param>
/// <returns>int.</returns>
int file_test(const char* filename);

#endif