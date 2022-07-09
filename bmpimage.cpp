//
// Created by duke on 2022/7/9.
//

#include "bmpimage.h"
#include <iostream>

BMPImage::BMPImage(int w, int h): width(w), height(h){
    //per line the number of bytes must be a multiple of 4
    line_align_bytes = (width*3) % 4;
    if (line_align_bytes != 0){
        line_align_bytes = 4 - line_align_bytes;
        buf_size = width * height * 3 + height * line_align_bytes;
    } else{
        buf_size = width * height * 3;//per pixel is 3 byte
    }
    bfType = 0x4d42;//'MB'
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfSize = 2 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + buf_size;//bfType is 2byte
    bfh.bfOffBits = 0x36;//40+14byte

    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = width;
    bih.biHeight = height;
    bih.biPlanes = 1;
    bih.biBitCount = 24;//3byte 3*8
    bih.biCompression = 0;
    bih.biSizeImage = 0;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;

    data = new unsigned char[buf_size];
    memset(data, 0, buf_size);
}

bool BMPImage::write_bmp_file(const char *filename){
    FILE *file = fopen(filename, "wb");
    if (!file){
        printf("file not exist\n");
        return false;
    }
    fwrite(&bfType, sizeof(bfType), 1, file);
    fwrite(&bfh, sizeof(bfh), 1, file);
    fwrite(&bih, sizeof(bih), 1, file);

    fwrite(data, buf_size, 1, file);
    fclose(file);
    return true;
}

bool BMPImage::set(int x, int y, BMPColor c){
    int index = get_index(x, y);
    unsigned char *p = &data[index];
    p[0] = c.b;
    p[1] = c.g;
    p[2] = c.r;
}

int BMPImage::get_index(int x, int y){
    if (x > width-1){
        throw std::invalid_argument("error argument x");
    }
    if (y > height-1){
        throw std::invalid_argument("error argument y");
    }
    return 3*(y*width + x) + line_align_bytes*y;
}

int BMPImage::get_width(){
    return width;
}
int BMPImage::get_height(){
    return height;
}
void BMPImage::clear(){
    memset(data, 0, buf_size);
}