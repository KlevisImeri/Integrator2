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
    int width;
    int height;
    BitmapFileHeader fileHeader;
    BitmapInfoHeader imageHeader;
    int dpi;
    vector<rgb> pixels;
    int size; //pixel/entity
    double onePixel; //enity/pixel
    double x_start;
    double x_end;
    double y_start;
    double y_end;
public:
    //constructor
    BmpImage(string name = "bmpimage", int width = 2000, int height = 2000, int dpi=600, int size=300);
    
    //methods
    void pixel(int x, int y, rgb color);
    void point(double x, double y, rgb color);
    void backgroundcolor(rgb color);
    void rectangle(double x, double y, double width, double height, rgb color);
    void line(double slope, double displacement, rgb color);
    void horizontalLine(int y,rgb color);
    void verticalLine(int x,rgb color);
    void verticalLine(int x,rgb color, double size);
    void function(Tree& expression, rgb color);
    void create();
};  

#endif