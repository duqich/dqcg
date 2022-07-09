//
// Created by duke on 2022/6/29.
//

#include "bmpimage.h"


int main() {
    BMPImage bmp(49, 81);
    const BMPColor red = BMPColor(0,0,255);
    bmp.set(48, 80, red);
    bmp.write_bmp_file("out.bmp");
    return 0;
}

