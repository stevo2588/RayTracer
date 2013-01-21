//-------------------------------------------------
//------------- RAYGUN.H --------------------------
//-------------------------------------------------
#pragma once
#ifndef RAYTRACER_RAYGUN_H_
#define RAYTRACER_RAYGUN_H_

#include <vector>
#include <iostream> // remove me
#include <include/Utility.h>
#include <include/Shapes.h>

// forward declarations go here

struct renderParams {
	enum sampleType {FixedInner, FixedOuter, Adaptive};

	double gridWidth;
	double gridHeight;
	int pixPerRow;
	int pixPerCol;
	sampleType sampling;
	int numRays;
};

class Grid {
private:
	struct PixCell {
		Color color;
		PixCell() : color(0,0,0) {}
	};

	Matrix3D worldSpace;
	double width;
	double height;
	int rowLength;
	int columnLength;
	std::vector<PixCell> pix;

public:
	Grid(Matrix3D m, double w, double h, int rl, int cl);
	Grid(double w, double h, int rl, int cl);

	Matrix3D getMatrix() const {return worldSpace;}
	int getWidth() const {return width;}
	int getHeight() const {return height;}
	double getRowLength() const {return rowLength;}
	double getColLength() const {return columnLength;}
	int getSize() const { return rowLength * columnLength; }
	Color getColor(int index) const {return pix[index].color;}

	void setMatrix(Matrix3D m) {worldSpace = m;}
	void setColor(int index, Color c) {pix[index].color = c;}
};

class Sampler { // abstract base class for samplers
protected:
	std::vector<int> toSample; // vector of indices specifying the pixels to sample
	std::vector<std::vector<Vector3D> > rayPts; // vector holding vectors for each pixels world space ray points
	std::vector<std::vector<Color> > colors; // vector holding vectors for each pixels sampled colors

	Sampler(const renderParams& rp);
	//~Sampler(); // TODO!
public:
	// rayAllocator() is responsible for:
	//    -setting the ray points on each pixel
	virtual void rayAllocator(const Grid& g) =0;

	// processor() is responsible for:
	//    -setting which pixels will be (re)sampled
	//    -deciding a final color for the pixel
	// it returns true when more sampling is required
	virtual void processor(Grid& g) =0;

	friend class RayGun;
};

class FixedInner : public Sampler {
private:
	int numRays;
public:
	FixedInner(const renderParams& rp): Sampler(rp) {this->numRays = rp.numRays;}

	void rayAllocator(const Grid& g);
	void processor(Grid& g);
};

class RayGun {
private:
	Matrix3D worldSpace;
	Vector3D pos;
	Grid pixGrid;
	Sampler* samp;

public:
	RayGun(Matrix3D space, double d, const renderParams& rp, Sampler* s);

	Matrix3D getMatrix() {return worldSpace;}
	int getPixRayPts(int index, std::vector<Vector3D>& vArray); // puts pos vectors in the array and returns number of vectors
	Color getColor(int index) {return pixGrid.getColor(index);} // gets color from grid pixel at specified index
	void start(const std::vector<Shape*> allObjects);
	void fire(const std::vector<Shape*> allObjects); // raytrace on all eligible pixels

private:
	void rayTrace(const Ray& r, Color& c, const std::vector<Shape*> allObjects); // add depth as arg later
};

#endif // RAYTRACER_RAYGUN_H_
