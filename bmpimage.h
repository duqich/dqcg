//
// Created by duke on 2022/6/29.
//
#ifndef __BMPIMAGE_H__
#define __BMPIMAGE_H__

typedef struct
{
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;
} BITMAPFILEHEADER;

typedef struct
{
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BITMAPINFOHEADER;

struct BMPColor {
    unsigned char b, g, r;
    BMPColor(unsigned char B, unsigned char G, unsigned char R): b(B), g(G), r(R){}
};

class BMPImage {
protected:
    int width;
    int height;
    int buf_size;
    unsigned short bfType;
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    unsigned char* data;
    int line_align_bytes;
public:
    BMPImage(int w, int h);
    bool write_bmp_file(const char *filename);
    bool set(int x, int y, BMPColor c);
    int get_width();
    int get_height();
    void clear();

    int get_index(int x, int y);
};

#endif //__BMPIMAGE_H__