/*
 * This program is intended to make image manipulation in
 * which there are different function that deal with each 
 * conversion.
 * Author : Khalid.
 * Course : CSCI160.
 * Date : 1 Dec, 2019.
 */

#include "ImageType.hpp"
#include<sstream>
using std::istringstream;


void makeAscii(const ImageType &image, string outfile) {
		//making a copy of the original image 
		ImageType numbers = image;
		int rows = numbers.getHeight(); // getting its height
		int cols = numbers.getWidth(); // getting its width
		//int gs = numbers.getGrayscale();
		int text;
		ofstream grapper(outfile); // creating an object grapper that will write to a file
		// these two nested for loops will will get every pixel value
		// of the original image and change it to its corresponding character.
		for(int r = 0; r < rows; r++){   
 			for(int c = 0; c < cols; c++){
				text = image.getPixelVal(r, c);
				if (text <= 20){
					grapper << "M";}
				else if (text <= 40){
					grapper << "L";}
				else if (text <= 60){
					grapper << "I";}
				else if (text <= 80){
					grapper << "O";}
				else if (text <= 100){
					grapper << "|";}
				else if (text <= 120){
					grapper << "=";}
				else if (text <= 140){
					grapper << "*";}
				else if (text <= 160){
					grapper << ":";}
				else if (text <= 180){
					grapper << "-";}
				else if (text <= 200){
					grapper << ",";}
				else if (text <= 220){
					grapper << ".";}
				else{
					grapper << " ";}
			}
			grapper << "\n";
			
		}
       // To colse the filw after being filled 
        grapper.close();
}

ImageType invert(const ImageType &image) {
	// make a copy of the original
	ImageType inverted = image;

	// make changes to this image
	int rows = inverted.getHeight(); // rows of the original image
	int cols = inverted.getWidth(); //  cols of the original image
	int gs = inverted.getGrayscale();// greyscale values of the original image
	int **metrix = inverted.getPixels(); // creating apointer to a pointer to an int 
	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){
			metrix[r][c] = gs - metrix[r][c]; //creating the pixel value of the inverted image 
		}
		
	}

	return inverted;
}

ImageType verticalFlip(const ImageType &image) {
	// make a copy of the original
	ImageType flipped = image;

	// make changes to this image
	int rows = flipped.getHeight();// rows of the original image
	int cols = flipped.getWidth();//  cols of the original image
	//int gs = inverted.getGrayscale();
	int **metrix = flipped.getPixels();// creating apointer to a pointer to an int 
	int temp;//for the swap action
	for(int r = 0; r < rows/2; r++){ // it is done until row/2 and then the swap action stops
		for(int c = 0; c < cols; c++){
			temp = metrix[r][c]; //puting it in a temporary variable
			metrix[r][c] = metrix[rows-1-r][c]; // interchanging postions
			metrix[rows-1-r][c] = temp;
			
		}
	}
	return flipped;
}

ImageType horizontalFlip(const ImageType &image) {
	// make a copy of the original
	ImageType Hflipped = image;

	// make changes to this image
	int rows = Hflipped.getHeight();
	int cols = Hflipped.getWidth();
	//int gs = inverted.getGrayscale();
	int **metrix = Hflipped.getPixels();
	//int h = rows/2;
	int grid;
	
		
	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols/2; c++){ // the condition that stops the looping is when it gets cols/2
			grid = metrix[r][c];
			metrix[r][c] = metrix[r][cols-1-c];
			metrix[r][cols-1-c] = grid;
			
		}
	}

	return Hflipped;
}

ImageType rotate(const ImageType &image) {
    // grapping the original width and height of the image
	int cols= image.getHeight();
	int rows = image.getWidth();
	int find = image.getGrayscale();
	/*
     *Create a new image with rotated width and height
	 *the width of the original image becomes the height of the new image
	 *and the height of the original image becames the width of the new image
   */
	ImageType rotated (rows, cols, find);                                                                         
	int **newval = rotated.getPixels();
	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){ //
			newval[r][c] = image.getPixelVal(cols-1-c, r);
		
		}
	}
	


	return rotated;
}


ImageType scale(const ImageType &image, double scalefactor) {


	// Create a new image that is the required new size
	int rows= image.getHeight();
	int cols = image.getWidth();
	int find = image.getGrayscale();
    int sf = int(scalefactor);
    if (scalefactor > 1 ){
    	int nheight = image.getHeight() * sf;
    	int newwidth = image.getWidth() * sf;
    	ImageType scaled(nheight, newwidth, find);
		int **newscal = scaled.getPixels();
		int startcol, endcol;
		int startrow, endrow;
	
		for(int r = 0; r < rows; r++){
			for(int c = 0; c < cols; c++){
		    	startrow = r * sf;
		    	endrow = startrow + (sf);
		    	for(; startrow < endrow; startrow++){
		    	     startcol = c * sf;
		    	     endcol = startcol + (sf);
		    	     for(; startcol < endcol; startcol++){
		    	     	  newscal[startrow][startcol] = image.getPixelVal(r, c);
		    	     	 
		    	     }
		       }
		   }
	   } 
	   return scaled;
	}   
	
}		           
			
	// change this statement: it currently creates a useless image object.
	//ImageType scaled(0,0,0);



			
int main(int argc, char* argv[]) {

/********************************************/
// THiS PART IS ALL DONE FOR YOU:
	if (argc < 4) {
		cout << "Invalid program execution, please use:\n";
		cout << "./go <inputfile> <outputfile> <operation>\n";
		return(0);
	}

	string infile = argv[1];
	string outfile = argv[2];
	string task = argv[3];

	// Create an image object from a file
	ImageType image(infile);

//FOR DEBUG PURPOSES:
//image.print();

/****************** END ***********************/

// YOU WILL NEED TO ADD STATEMENTS TO THE CODE THAT FOLLOWS
// THE SET UP FOR TASK invert HAS BEEN SET UP FOR YOU.
// SIMILAR PROCEDURES ARE REQUIRED FOR THE REMAINING TASKS

	// Depending on the task, do what is necessary with the image,
	// by calling the appropriate function.
	if (task == "invert") {
		ImageType inverted = invert(image);
		inverted.writeToFile(outfile);}
	else if (task == "verticalFlip") {
		ImageType flipped = verticalFlip(image);
		flipped.writeToFile(outfile);}
	else if (task == "horizontalFlip") {
		ImageType Hflipped = horizontalFlip(image);
		Hflipped.writeToFile(outfile);}
	else if (task == "rotate") {
		ImageType rotated = rotate(image);
		rotated.writeToFile(outfile);}
	else if (task == "makeAscii") {
		makeAscii(image, outfile);}
	else if (task =="scale"){
		if(argc < 5){
			cout << "please add the scale factor at the end" << endl;
			return (0);
		}
		double scalefactor;
		istringstream(argv[4]) >> scalefactor;
		ImageType scaled = scale(image, scalefactor);
		scaled.writeToFile(outfile);
	}

	else {
		cout << "Error in the task: Do not know what " << task << " means.\n";
		return (0);}
	
	
	
	cout << "All done\n";
	return 0;
}
