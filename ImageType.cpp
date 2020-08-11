 #include "ImageType.hpp"

// constructor
ImageType::ImageType(int h, int w, int gs) {
	setImageInfo(h,w,gs);
}

// constructor from file source.
ImageType::ImageType(string filename) {

	ifstream reader(filename);
	string imagecode;
	getline(reader,imagecode);
	if (imagecode != "P2") {
		cout << "Not the correct image type.\n";
		cout << "Got "<<imagecode<<", expected P2.\n";
		// create a default object
		setImageInfo(0,0,0);
		return;
	}
	// The next two integers are the width and height in pixels
	// width is number of columns.
	// height is number of rows.
	// grayscale is the range of black to white (usually 256)
	int h, w, gs;
	reader >> w;
	reader >> h;
	if (!reader) {
		cout << "Cannot pick out the width and height values.\n";
		setImageInfo(0,0,0);
		return;
	}
	reader >> gs;
	
	setImageInfo(h,w,gs);

	int value;
	for (int r=0; r<height; r++) {
		for (int c=0; c<width; c++) {
			reader >> value;
			setPixelVal(r,c,value);
		}
	}
}

// copy constructor
ImageType::ImageType(const ImageType &image) {
	int h = image.height;
	int w = image.width;
	int gs = image.grayscale;
	setImageInfo(h, w, gs);
	for (int r=0; r<height; r++) {
		for (int c=0; c<width; c++) {
			pixelValues[r][c] = image.getPixelVal(r,c);
		}
	}
}

// initializes the memory for the array, but doesn't fill it.
void ImageType::setImageInfo(int h, int w, int gs) {
	if (h < 0) {
		height = 0;
	} else {
		height = h;
	}
	if (w < 0) {
		width = 0;
	} else {
		width = w;
	}
	if (gs < 0) {
		grayscale = 0;
	} else {
		grayscale = gs;
	}
	pixelValues = new int*[height];
	for (int r=0; r<height; r++) {
		pixelValues[r] = new int[width];
	}
}

void ImageType::writeToFile(string filename) {
	ofstream writer(filename);
	writer << "P2\n";
	writer << width << " " << height << endl;
	writer << grayscale << endl;

	for (int r=0; r<height; r++) {
		for (int c=0; c<width; c++) {
			writer << getPixelVal(r,c) << endl;
		}
	}
}

void ImageType::print() {
	cout << height << " X " << width << endl;
	for (int r=0; r < height; r++) {
		for (int c=0; c < width; c++) {
			cout<<pixelValues[r][c]<<" ";
		}
		cout << endl;
	}
}
