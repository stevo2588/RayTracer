//-------------------------------------------------
//------------- SHAPES.CPP ------------------------
//-------------------------------------------------
//#include "stdafx.h"
#include <cmath>
#include <include/Shapes.h>

/*
Equation of a sphere with center at (x0,y0,z0) and radius r:
(x - x0)^2 + (y - y0)^2 _ (z - z0)^2 = r^2
*/
bool Sphere::intersection(const Ray& r, double* t) const {
	/*
	 * optimize by using * instead of /
	 * should check for all intersections but only return Color from the one closest to ray's origin
	 * assumes center always at 0.. change?
	 */

	//transform ray into sphere's object space
	Vector3D rd = m_mult_dirVec(inverse, r.dirPos); // Transform direction vector: World -> Object
	Vector3D rs = inverse * r.srcPos; // Transform position vector: World -> Object

	//Compute A, B and C coefficients
	double A = rd.dotProduct(rd); // calculate norm (length) of rd using dot product
	double B = 2 * (rd.dotProduct(rs));
	double C = rs.dotProduct(rs) - (radius * radius);

	// Note: If |Rd|=1 then A=1, So we can compute radius^2 once

    //Find discriminant
    double disc = B*B - 4*A*C;

    // if discriminant is negative there are no real roots, so return false as ray misses sphere
    if (disc < 0) {
		//t = NULL; // TODO: TEMPORARY!!!!!!!!!!!!!
		return false;
	}

	// TODO: What if ray intersects in its negative direction??????!!!!!!!!!!
	// ----------------------------------------------------------------------

	// precompute to avoid possibility of calculating twice
    double discSqrt = sqrt(disc);
	double denom = 2*A;

	//*t = (-B - discSqrt)/denom; // TODO: Temporary!!!!!!!!!!!!!!!!
	//if( *t < 0 ) *t = (-B + discSqrt)/denom; // TODO: Temporary!!!!!!!!!!!!!!!!

	return true;


	/*
	// old way
	// compute q
    double discSqrt = sqrt(disc);
    double q;

	// determine whether we use + or - based on whether B is + or -
    if(B < 0) q = (-B - discSqrt)/2.0;
    else q = (-B + discSqrt)/2.0;

    // compute t0 and t1
    double t0 = q / A;
    double t1 = C / q;

    // make sure t0 is smaller than t1
    if (t0 > t1) {
        // if t0 is bigger than t1 swap them around
        double temp = t0;
        t0 = t1;
        t1 = temp;
    }

    // if t1 is less than zero, the object is in the ray's negative direction
    // and consequently the ray misses the sphere
    if (t1 < 0) return Color(0,0,0);

    // if t0 is less than zero, the intersection point is at t1
    if (t0 < 0) {
        //t = t1;
		//std::cout << "hit!\n";
		//std::cout << tex.r << std::endl;
        return tex;
    }
    // else the intersection point is at t0
    else {
        //t = t0;
		//std::cout << "hit!\n";
		//std::cout << tex.r << std::endl;
        return tex;
    }
	*/
}
