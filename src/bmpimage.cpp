#include "bmpimage.h"

BmpImage::BmpImage(string name, int width, int height, int dpi, int size):name(name),width(width),height(height),dpi(dpi),size(size){
    int image_size = width * height;
	int file_size = 54 + 4 * image_size;
	int ppm = dpi * 39.375;

	fileHeader.bitmap_type[0]  ='B';
	fileHeader.bitmap_type[1]  ='M';
	fileHeader.file_size       = file_size;
	fileHeader.reserved1       = 0;
	fileHeader.reserved2       = 0;
	fileHeader.offset_bits     = 0;

	imageHeader.size_header     = sizeof(imageHeader);
	imageHeader.width           = width;
	imageHeader.height          = height;
	imageHeader.planes          = 1;
	imageHeader.bit_count       = 24;
	imageHeader.compression     = 0;
	imageHeader.image_size      = file_size;
	imageHeader.ppm_x           = ppm;
	imageHeader.ppm_y           = ppm;
	imageHeader.clr_used        = 0;
	imageHeader.clr_important   = 0;
  	
	
	pixels.resize(width*height); 
	x_start = - width/(2*size);
	x_end = width/(2*size);
	y_start = - height/(2*size);
	y_end = height/(2*size);
	onePixel = 1/(double) size;
}
void BmpImage::pixel(int x, int y, rgb color){
	if(x>=width || x<0 || y>=height || y<0){
		//out of bound
		return;
	}
	int a = y * width + x;
	pixels[a].r = color.r;
	pixels[a].g = color.g;
	pixels[a].b = color.b;
}
void BmpImage::point(double x, double y, rgb color){
	//resizing
	x *= size;
	y *= size;

	//shifting in the middle
	x += width/2;
	y += height/2;
	
	pixel(x,y,color);
	pixel(x+1,y+1,color);
	pixel(x-1,y-1,color);
	pixel(x,y+1,color);
	pixel(x+1,y,color);
	pixel(x-1,y,color);
	pixel(x,y-1,color);
	pixel(x+1,y-1,color);
	pixel(x-1,y+1,color);
}
void BmpImage::backgroundcolor(rgb color){
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			pixel(x,y,color);
		}
	}
};
void BmpImage::rectangle(double x, double y, double width, double height, rgb color){
	for(double i = x; x <= width; i+=onePixel){
		if(height>=0){
			for(double j = y; j<=height; j+=onePixel){
				//for the line surronding the squares
				if(j==height || i==width || i==x ){
					point(i,j,{255,77,77});
				}else{
					point(i,j,color);
				}	
			}	
		}else{		
			for(double j = y; j>=height; j-=onePixel){
				if(j==height || i==width || i==x){
					point(i,j,{255,77,77});
				}else{
					point(i,j,color);
				}	
			}
		}	
	}
}
void BmpImage::line(double slope, double displacement, rgb color){
	int y;
	for(double x = x_start; x<x_end; x+=onePixel){
		y = slope*x + displacement;
		point(x, y, color);
	}
}
void BmpImage::horizontalLine(int y,rgb color){
	for(double x = x_start; x<x_end; x+=onePixel){
		point(x, y, color);
	}
}
void BmpImage::verticalLine(int x,rgb color){
	for(double y = y_start; y<y_end; y+=onePixel){
		point(x, y, color);
	}
}
void BmpImage::verticalLine(int x,rgb color, double size){
	for(double y = -size; y<size; y+=onePixel){
		point(x, y, color);
	}
}
void BmpImage::function(Tree& expression, rgb color){
	int y;
	for(double x = x_start; x<x_end; x+=onePixel){
		point(x,expression.evaluate(x),color);
	}
}
void BmpImage::create(){
	ofstream image(name + ".bmp");
	if (!image) {
		cout << "Error: Failed to create image file." << endl;
		return;
	}
	
	// Write the bitmap file header
    image.write(reinterpret_cast<char*>(&fileHeader.bitmap_type), sizeof(fileHeader.bitmap_type));
    image.write(reinterpret_cast<char*>(&fileHeader.file_size), sizeof(fileHeader.file_size));
    image.write(reinterpret_cast<char*>(&fileHeader.reserved1), sizeof(fileHeader.reserved1));
    image.write(reinterpret_cast<char*>(&fileHeader.reserved2), sizeof(fileHeader.reserved2));
    image.write(reinterpret_cast<char*>(&fileHeader.offset_bits), sizeof(fileHeader.offset_bits));
    
    // Write the bitmap image header
    image.write(reinterpret_cast<char*>(&imageHeader.size_header), sizeof(imageHeader.size_header));
    image.write(reinterpret_cast<char*>(&imageHeader.width), sizeof(imageHeader.width));
    image.write(reinterpret_cast<char*>(&imageHeader.height), sizeof(imageHeader.height));
    image.write(reinterpret_cast<char*>(&imageHeader.planes), sizeof(imageHeader.planes));
    image.write(reinterpret_cast<char*>(&imageHeader.bit_count), sizeof(imageHeader.bit_count));
    image.write(reinterpret_cast<char*>(&imageHeader.compression), sizeof(imageHeader.compression));
    image.write(reinterpret_cast<char*>(&imageHeader.image_size), sizeof(imageHeader.image_size));
    image.write(reinterpret_cast<char*>(&imageHeader.ppm_x), sizeof(imageHeader.ppm_x));
    image.write(reinterpret_cast<char*>(&imageHeader.ppm_y), sizeof(imageHeader.ppm_y));
    image.write(reinterpret_cast<char*>(&imageHeader.clr_used), sizeof(imageHeader.clr_used));
    image.write(reinterpret_cast<char*>(&imageHeader.clr_important), sizeof(imageHeader.clr_important));


	// Write pixel data
	for (auto i : pixels){
		// cout<<'|'<<i.r<<i.g<<i.b<<"|";
		unsigned char color[3] = { i.r, i.g, i.b };
		image.write(reinterpret_cast<char*>(&color), sizeof(color));
	}
	
	// Close the file
	image.close();
}