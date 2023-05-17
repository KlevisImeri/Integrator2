#include "bmpimage.h"
#include <iomanip>

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
  	
	resize();

}
void BmpImage::resize(){
	//Resizing with the new values
	pixels.resize(width*height); 
	oneEntity = width/(2*size);
	onePixel = (double) (2*size)/width;
}
void BmpImage::resize(int _size){
	//Setting the values
	size =_size;
	//Resizing with the new values
	oneEntity = width/(2*size);
	onePixel = (double) (2*size)/width;
}
void BmpImage::resize(int _size, int _width, int _height){
	//Setting the values
	size=_size; width=_width; height=_height;
	//Resizing with the new values
	pixels.resize(width*height); 
	oneEntity = width/(2*size);
	onePixel = (double) (2*size)/width;
}
void BmpImage::pixel(int x, int y, rgb color){
	if(x>=width || x<0 || y>=height || y<0){
		// Out of bound
		return;
	}
	int a = y * width + x;
	pixels[a].r = color.r;
	pixels[a].g = color.g;
	pixels[a].b = color.b;
}
void BmpImage::point(double x, double y, rgb color, bool bold){
	// Resizing
	x *= oneEntity;
	y *= oneEntity;

	// Shifting in the middle
	x += width/2;
	y += height/2;
	
	// Draw the pixel
	pixel(x,y,color);
	pixel(x,y+1,color);
	pixel(x+1,y,color);

	// To make line bold
	if(bold){
		pixel(x+1,y+1,color);
		pixel(x-1,y-1,color);
		pixel(x-1,y,color);
		pixel(x,y-1,color);
		pixel(x+1,y-1,color);
		pixel(x-1,y+1,color);
	}
}
void BmpImage::backgroundcolor(rgb color){
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			pixel(x,y,color);
		}
	}
};
void BmpImage::rectangle(double x, double y, double width, double height, rgb color,rgb bordercolor){
	//Exaching becuase we only go up and right when coloring
	if(width < 0){
		x += width;
		width=abs(width);
	}
	if(height < 0){
		y += height;
		height=abs(height);
	}
	
	//Cordinates of the endings of the corners
	double W = x+width;
	double H = y+height;

	//Drawing the main square
	for(double i = x; i <= W; i+=onePixel){
		for(double j = y; j<=H; j+=onePixel){
			point(i,j, color);
		}		
	}

	// Vertical border lines
	for(double j = y; j<=H; j+=onePixel){
		point(x,j,bordercolor);
		point(W,j,bordercolor);
	}
	// Horizontal border lines
	for(double i = x; i <= W; i+=onePixel){
		point(i,y,bordercolor);
		point(i,H,bordercolor);
	}
}
void BmpImage::line(double slope, double displacement, rgb color){
	int y;
	for(double x = -size; x<size; x+=onePixel){
		y = slope*x + displacement;
		point(x, y, color);
	}
}
void BmpImage::horizontalLine(int y, rgb color){
	for(double x = -size; x<size; x+=onePixel){
		point(x, y, color);
	}
}void BmpImage::horizontalLine(int y, double size, rgb color){
	for(double x = -size; x<size; x+=onePixel){
		point(x, y, color);
	}
}
void BmpImage::verticalLine(int x,rgb color){
	for(double y = -size; y<size; y+=onePixel){
		point(x, y, color);
	}
}
void BmpImage::verticalLine(int x, double size, rgb color){
	for(double y = -size; y<size; y+=onePixel){
		point(x, y, color);
	}
}
void BmpImage::plane(rgb color){
	verticalLine(0, color);
	horizontalLine(0, color);
	for(int i=1; i<=size; i++){
		verticalLine(i,0.1,color);
    	verticalLine(-i,0.1,color);
		horizontalLine(i,0.1,color);
    	horizontalLine(-i,0.1,color);
	}		
}
void BmpImage::plane(int _resize,  rgb color){
	resize(_resize);
	verticalLine(0,color);
	horizontalLine(0,color);
	for(int i=1; i<=size; i++){
		verticalLine(i,0.1,color);
    	verticalLine(-i,0.1,color);
		horizontalLine(i,0.1,color);
    	horizontalLine(-i,0.1,color);
	}		
}
void BmpImage::function(Tree& expression, rgb color){
	int y;
	for(double x = -size; x<size; x+=onePixel){
		point(x,expression.evaluate(x),color);
	}
}
void BmpImage::integral(Tree& expression, double start, double end, double size , rgb color, rgb bordercolor){
	for(double i=start; i<=end; i+=size){
		rectangle(i, 0, size, expression.evaluate(i), color, bordercolor);
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
		unsigned char color[3] = { (unsigned char)i.r, (unsigned char)i.g, (unsigned char)i.b };
		image.write(reinterpret_cast<char*>(&color), sizeof(color));
	}
	
	// Close the file
	image.close();
}