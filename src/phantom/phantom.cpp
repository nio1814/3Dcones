#include "phantom.h"

extern "C"
{
#include "arrayops.h"
}

#include <math.h>

/*
 * SheppLogan3D.java
 *
 * Created on January 7, 2007, 8:46 PM
 */

/**
 *
 * Three-dimensional Shepp-Logan Phantom in both the Fourier and image domains.
 *
 * This is a class called SheppLogan3D. It can be used to generate Fourier domain
 * signal (or k-space) as well as image domain signal based on a 3-dimensional
 * analytical phantom in both domains. Please refer to the source code or
 * the article referenced below for further information.
 *
 * <br>
 * <br> The image below is a 3D rendering of the phantom in the image domain</p>
 * <p><p align="center"><img src="threed.png" width="285" height="345"></p><br></p>
 *
 *
 * <br>
 * The reconstructed images from the Fourier domain signals are shown below as animated gif:
 *
 * <p><p align="center"><img src="reconmovie.gif" width="345" height="345"></p><br></p>
 *
 * <br>
 *
 *
 * <br>
 * Please refer to
 * <br>
 * Koay CG, Sarlls JE, &#214zarslan E.
 * Three Dimensional Analytical Magnetic Resonance Imaging Phantom in the Fourier Domain. Magn Reson Med. 58: 430-436 (2007)
 * <br>
 * for further information.
 *
 * <br>
 * @see <a href=http://dx.doi.org/10.1002/mrm.21292>Ref</a>
 * @author  Cheng Guan Koay
 * @since 07/25/2007
 *
 * @version &#8722&#8734.
 */

/** Creates a new instance of SheppLogan3D */
Phantom::Phantom()
{
	m_ellipsoids.push_back(Ellipsoid(0,       0,       0,     0.69,    0.92,     0.9,              0,      0,    0,      2.));
	m_ellipsoids.push_back(Ellipsoid(0,       0,       0,   0.6624,   0.874,    0.88,              0,      0,    0,    -0.8));
	m_ellipsoids.push_back(Ellipsoid( -0.22,      0.,   -0.25,     0.41,    0.16,    0.21, (3*M_PI)/5.,      0,    0,    -0.2));
	m_ellipsoids.push_back(Ellipsoid(0.22,      0.,   -0.25,     0.31,    0.11,    0.22, (2*M_PI)/5.,      0,    0,    -0.2));
	m_ellipsoids.push_back(Ellipsoid(0,    0.35,   -0.25,     0.21,    0.25,     0.5,              0,      0,    0,     0.2));
	m_ellipsoids.push_back(Ellipsoid(0,     0.1,   -0.25,    0.046,   0.046,   0.046,              0,      0,    0,     0.2));
	m_ellipsoids.push_back(Ellipsoid(-0.08,   -0.65,   -0.25,    0.046,   0.023,    0.02,              0,      0,    0,     0.1));
	m_ellipsoids.push_back(Ellipsoid(0.06,   -0.65,   -0.25,    0.046,   0.023,    0.02,              0,      0,    0,     0.1));
	m_ellipsoids.push_back(Ellipsoid(0.06,  -0.105,   0.625,    0.056,    0.04,     0.1,     M_PI/2.,      0,    0,     0.2));
	m_ellipsoids.push_back(Ellipsoid( 0.,     0.1,   0.625,    0.056,   0.056,     0.1,     M_PI/2.,      0,    0,    -0.2));


		// number of ellipsoids
		/*NE = SheppLogan3D.ellipsoids.length;

		RT = new double[NE][3][3]; //transposed rotation matrices

		d = new double[NE][3]; //displacement vectors

		abc = new double[NE][3]; //The length of the principal axes

		rho = new double[NE]; // signal intensity

		for(int i=0; i<NE; i++){

		d[i][0] = ellipsoids[i][0]; // delta_x
		d[i][1] = ellipsoids[i][1]; // delta_y
		d[i][2] = ellipsoids[i][2]; // delta_z


		abc[i][0] = ellipsoids[i][3]; // a
		abc[i][1] = ellipsoids[i][4]; // b
		abc[i][2] = ellipsoids[i][5]; // c

		RT[i] = MAT.transpose(
					MAT.dot(
					MAT.dot( SheppLogan3D.Rz(ellipsoids[i][6]),
							 SheppLogan3D.Ry(ellipsoids[i][7])
						   ),SheppLogan3D.Rz(ellipsoids[i][8])
						   )
						   );

		rho[i]  = ellipsoids[i][9];

		}//end for*/
}



	/**
	 *  User may add new ellipsoids and change their properties with this constructor.
	 *
	 *  @param ellipsoids is a two dimensional matrix arranged according to the following convention:
	 *  <PRE>
		  delta_x, delta_y, delta_z,        a,       b,       c,            phi,  theta,  psi,     rho
	   {{       0,       0,       0,     0.69,    0.92,     0.9,              0,      0,    0,      2. },
		{       0,       0,       0,   0.6624,   0.874,    0.88,              0,      0,    0,    -0.8 },
		{   -0.22,      0.,   -0.25,     0.41,    0.16,    0.21, (3*M_PI)/5.,      0,    0,    -0.2 },
		{    0.22,      0.,   -0.25,     0.31,    0.11,    0.22, (2*M_PI)/5.,      0,    0,    -0.2 },
		{       0,    0.35,   -0.25,     0.21,    0.25,     0.5,              0,      0,    0,     0.2 },
		{       0,     0.1,   -0.25,    0.046,   0.046,   0.046,              0,      0,    0,     0.2 },
		{   -0.08,   -0.65,   -0.25,    0.046,   0.023,    0.02,              0,      0,    0,     0.1 },
		{    0.06,   -0.65,   -0.25,    0.046,   0.023,    0.02,              0,      0,    0,     0.1 },
		{    0.06,  -0.105,   0.625,    0.056,    0.04,     0.1,     M_PI/2.,      0,    0,     0.2 },
		{      0.,     0.1,   0.625,    0.056,   0.056,     0.1,     M_PI/2.,      0,    0,    -0.2 }};
	   </PRE>
	 *  <br>
	 *
	 *  Please to the paper mentioned above for further information on the notations.
	 *
	 */
Phantom::Phantom(std::vector<Ellipsoid> ellipsoids)
{
		// number of ellipsoids
/*
		RT = new double[NE][3][3]; //transposed rotation matrices

		d = new double[NE][3]; //displacement vectors

		abc = new double[NE][3]; //The length of the principal axes

		rho = new double[NE]; // signal intensity

		for(int i=0; i<NE; i++){

		d[i][0] = ellipsoids[i][0]; // delta_x
		d[i][1] = ellipsoids[i][1]; // delta_y
		d[i][2] = ellipsoids[i][2]; // delta_z


		abc[i][0] = ellipsoids[i][3]; // a
		abc[i][1] = ellipsoids[i][4]; // b
		abc[i][2] = ellipsoids[i][5]; // c

		RT[i] = MAT.transpose(
					MAT.dot(
					MAT.dot( SheppLogan3D.Rz(ellipsoids[i][6]),
							 SheppLogan3D.Ry(ellipsoids[i][7])
						   ),SheppLogan3D.Rz(ellipsoids[i][8])
						   )
						   );

		rho[i]  = ellipsoids[i][9];

		}//end for

*/

	for(size_t n=0; n<m_ellipsoids.size(); n++)
		m_ellipsoids.push_back(ellipsoids[n]);
}


	/**
	  *  Given a list of position vectors, i.e. {{x1,y1,z1},{x2,y2,z2},...},
	  *  the image domain signals at those locations are returned.
	  *
	  */
std::vector<float> Phantom::imageDomainSignal(const std::vector<float>& coordinates)
{
	 int points = coordinates.size()/3;
	 std::vector<float> data(points);

	 for(int i=0; i<points; i++)
	{
		 data[i] = imageDomainSignal(coordinates[3*i], coordinates[3*i+1], coordinates[3*i+2]);

	 }

	 return data;
}


	/**
	 * returning real value of the image intensity at (x,y,z).
	 *
	 */
	float Phantom::imageDomainSignal(float x, float y, float z)
	{

		float position[3] = {x,y,z};

		double signal = 0.0;

		double sum = 0.0;

		for(size_t i=0; i<m_ellipsoids.size(); i++){ // loop through each of the ellipsoids
			Ellipsoid& ellipse = m_ellipsoids.at(i);
//			 p = MAT.dot(RT[i],new double[] {x-d[i][0], y-d[i][1], z-d[i][2]});
			float relativePosition[3];
			ellipse.relativePosition(position, relativePosition);
			 for(int d=0; d<3; d++)
			 {
				 float projection = relativePosition[d]/ellipse.m_principalAxes[d];
				sum += projection*projection;
//			 sum = powf(p[0]/abc[i][0],2) + powf(p[1]/abc[i][1],2) + powf(p[2]/abc[i][2],2);

			 signal += (sum<=1.0) ? ellipse.m_intensity : 0;
			 }
		}

		return signal;
	}

	 /**
	  *  Given a list of (kx,ky,kz), the k-space signals at those locations are returned.
	  *  The return array is of dimension kList.length by 2.
	  *  The first column of the array is the real part of the complex signal and the second is
	  *  the imaginary part of the complex signal.
	  */
	 std::vector<complexFloat> Phantom::fourierDomainSignal(const std::vector<float>& coordinates)
	 {
		 int points = coordinates.size();
		 std::vector<complexFloat> data(points);

		 for(int i=0; i<points; i++)
		 {
			 data[i] = fourierDomainSignal(coordinates[3*i], coordinates[3*i+1], coordinates[3*i+2]);
		 }

		 return data;
	 }


	/**
	 * returning the complex signal evaluated at ( kx, ky, kz) in an array of length 2, i.e. {Re, Im}.
	 */
	complexFloat Phantom::fourierDomainSignal(float kx, float ky, float kz)
	{
		float k[3] = {kx,ky,kz};

		complexFloat signal; // {Re, Im} , real and imaginary signals

//		double K = 0.0;
		double arg = 0.0;

		float coordinatesRotated[3];
		for(size_t i=0; i<m_ellipsoids.size(); i++)
		{
			Ellipsoid& ellipsoid = m_ellipsoids.at(i);
//			 K = MAT.norm( MAT.multiply(MAT.dot(RT[i],k), ellipsoid.m_principalAxes) );
			ellipsoid.rotatedCoordinates(k, coordinatesRotated);
			float K = norm2(coordinatesRotated, 3);

			 arg = 2.0 * M_PI * K;

			 if(K==0.0){ // if K = 0

				 if( norm2(ellipsoid.m_displacement,3)==0.0 ){ // if displacement vector is zero

					 signal.real() +=(4./3.)*M_PI* ellipsoid.m_intensity*ellipsoid.m_principalAxes[0]*ellipsoid.m_principalAxes[1]*ellipsoid.m_principalAxes[2];

				 }else{ // displacement vector is not zero
					 double kd = dot(k, ellipsoid.m_displacement, 3);
					 double temp = (4./3.)*M_PI* ellipsoid.m_intensity*ellipsoid.m_principalAxes[0]*ellipsoid.m_principalAxes[1]*ellipsoid.m_principalAxes[2];
					 signal.real() += temp * cosf(2.0 * M_PI * kd);
					 signal.imag() -= temp * sinf(2.0 * M_PI * kd);
				 }

			 }else if (K<=0.002){  // if K<=0.002


				 if( norm2(ellipsoid.m_displacement,3)==0.0 ){ // if displacement vector is zero

					 double temp = 4.1887902047863905 - 16.5366808961599*powf(K,2) + 23.315785507450016*powf(K,4);
					 signal.real() += ellipsoid.m_intensity*ellipsoid.m_principalAxes[0]*ellipsoid.m_principalAxes[1]*ellipsoid.m_principalAxes[2]*temp;

				 }else{  // if displacement vector is not zero
					 double kd = dot(k, ellipsoid.m_displacement, 3);
					 double temp1 = 4.1887902047863905 - 16.5366808961599*powf(K,2) + 23.315785507450016*powf(K,4);
					 double temp2 = ellipsoid.m_intensity*ellipsoid.m_principalAxes[0]*ellipsoid.m_principalAxes[1]*ellipsoid.m_principalAxes[2]*temp1;

					 signal.real() += temp2 * cosf(2.0 * M_PI * kd);
					 signal.imag() -= temp2 * sinf(2.0 * M_PI * kd);
				 }


			 }else{ // K>0.002

				 if( norm2(ellipsoid.m_displacement,3)==0.0 ){ // if displacement vector is zero

					 double temp = sinf(arg)-arg*cosf(arg);
							temp /= (2.0*powf(M_PI,2)*powf(K,3));

					 signal.real() += ellipsoid.m_intensity*ellipsoid.m_principalAxes[0]*ellipsoid.m_principalAxes[1]*ellipsoid.m_principalAxes[2]*temp;

				 }else{  // displacement vector is not zero
					 double kd = dot(k, ellipsoid.m_displacement, 3);
					 double temp = sinf(arg)-arg*cosf(arg);
							temp /= (2.0*powf(M_PI,2)*powf(K,3));

							temp *= ellipsoid.m_intensity*ellipsoid.m_principalAxes[0]*ellipsoid.m_principalAxes[1]*ellipsoid.m_principalAxes[2];

					 signal.real() += temp * cosf(2.0 * M_PI * kd);
					 signal.imag() -= temp * sinf(2.0 * M_PI * kd);
				 }


			 }//end

		}

		return signal;
	}
