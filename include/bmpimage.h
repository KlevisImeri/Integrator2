#ifndef bmpimage_h
#define bipimage_h
#include <string>
#include <fstream>
#include <vector>
#include "tree.h"
using namespace std;

struct rgb{
    unsigned int r, g, b;
};

struct BitmapFileHeader {
    unsigned char   bitmap_type[2];     // 2 bytes
    int             file_size;          // 4 bytes
	short           reserved1;          // 2 bytes
	short           reserved2;          // 2 bytes
	unsigned int    offset_bits;        // 4 bytes
};

struct BitmapInfoHeader {
    unsigned int    size_header;        // 4 bytes
    unsigned int    width;              // 4 bytes
    unsigned int    height;             // 4 bytes
    short int       planes;             // 2 bytes
    short int       bit_count;          // 2 bytes
    unsigned int    compression;        // 4 bytes
    unsigned int    image_size;         // 4 bytes
    unsigned int    ppm_x;              // 4 bytes
    unsigned int    ppm_y;              // 4 bytes
    unsigned int    clr_used;           // 4 bytes
    unsigned int    clr_important;      // 4 bytes
};

class BmpImage{
private:
    string name;
    int width;          //widht of the image  (px)
    int height;         //height if the image (px)
    BitmapFileHeader fileHeader;
    BitmapInfoHeader imageHeader;
    int dpi;
    vector<rgb> pixels;
    int size;           //Numbers in number line
    int oneEntity;      //pixel/entity
    double onePixel;    //enity/pixel
public:
    //constructor
    BmpImage(string name = "bmpimage", int width = 2000, int height = 2000, int dpi=600, int size=3);
    
    //methods
    void resize();
    void resize(int size);
    void resize(int size, int width, int height);
    void pixel(int x, int y, rgb color={255, 255, 255});
    void point(double x, double y, rgb color={255, 255, 255}, bool bold = true);
    void backgroundcolor(rgb color);
    void rectangle(double x, double y, double width, double height, rgb color={222, 159, 78}, rgb bordercolor={255,77,77});
    void line(double slope, double displacement, rgb color={255, 255, 255});
    void horizontalLine(int y, rgb color={255, 255, 255});
    void horizontalLine(int y, double size, rgb color={255, 255, 255});
    void verticalLine(int x, rgb color={255, 255, 255});
    void verticalLine(int x, double size, rgb color={255, 255, 255});
    void plane(rgb color={255, 255, 255});
    void plane(int resize, rgb color={255, 255, 255});
    void function(Tree& expression, rgb color={255, 255, 255});
    void integral(Tree& expression, double start, double end, double size, rgb color={222, 159, 78}, rgb bordercolor={255,77,77});
    void create();
};  

#endif