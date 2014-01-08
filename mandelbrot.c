// THIS PROGRAM PLOTS THE MANDELBROT SET. A SUBSET OF THE COMPLEX PLANE IS 
// DIVIDED UP IN TO AN NxN GRID, AND AN ITERATIVE EQUATION IS APPLIED TO EACH
// POINT ON THIS GRID. IF, AFTER A PREDETERMINED NUMBER OF ITERATIONS, THE 
// OUTPUT NUMBER HAS NOT EXCEEDED A CERTAIN ABSOLUTE MAGNITUDE THEN THE POINT
// IS PLOTTED. OTHERWISE IT IS PLOTTED. 


// AUTHOR: LACHLAN STONEY



//CONSTANTS:

//MNI = Max # of iterations
//N = # of subdivisions of the plotting window.
//R = Max absolute magnitude of iteration
//XMIN, YMIN, ... = boundaries of plotting window.


#define MNI 500 
#define N 1000
#define R 3
#define XMIN -1.5
#define XMAX 0.5
#define YMIN -1.0
#define YMAX 1.0

//Includes

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cpgplot.h>


//The structure of a complex number is defined

struct cnum
  {
    double cx;       // x component
    double cy;       // y component
  };
  

  
  
//Declaration of Functions  
  
void CPRINT(struct cnum c);                                 // prints a complex number in coordinate form. (diagnostic tool)
struct cnum CPROD( struct cnum c1, struct cnum c2);         // multiplies two complex numbers c1 and c2;
struct cnum CADD( struct cnum c1, struct cnum c2);          // adds " " "
struct cnum FJULIA( struct cnum c1 );                       // iterative function for Julia Set
struct cnum FMANDEL( struct cnum z, struct cnum c );        // iteractive function for Mandelbrot Set




//Main program

void main()
{
   
   float RES = (XMAX - XMIN)/N;                          //resolution
   
   int i,j,p;
   
    
   
   //************************* PGPLOT CODE ***************************
  
  cpgbeg(0,"?",1,1);
  cpgpage();
  
  cpgsci(1);                                           // axis color
  
  cpgpap(0,1);
  
                                                      //axis limits
  cpgswin(XMIN,XMAX,YMIN,YMAX);
  
  cpgbox("BCN",1, 0, "BCN", 1, 0);                  // draw the axes
  
  cpgsci(1);                                          //data color

  cpgsch(0.00000000000001);                        //data point size
  
  
  
  //******************* GRID ALGORITHM AND PLOTTING ********************
  
  
  struct cnum z;                          // z = (0,0) = initial number 
  struct cnum c;                          // c is a complex variable
  z.cx = 0;
  z.cy = 0;
   
   
  for(i=0;i<N;i++)                     //look at every point on grid
  {
    for(j=0;j<N;j++)                       
    {
      
       c.cx = XMIN + i*RES;            //assign c = current point
       c.cy = YMIN + j*RES;            
       
       CPRINT(c);
       
       for(p=0;p<MNI;p++)                  //apply MNI iterations to z
       {                                   //using c = current point
	 z = FMANDEL(z,c);
	 
	 if ( z.cx*z.cx + z.cy*z.cy > R)    // if iteration "blows up"... 
	 {
	   z.cx = 0;
	   z.cy = 0;                       //stay at z=c=0
	   c.cx = 0;
	   c.cy = 0;	   
	 }
	   
       }                                  //end of interation. z = final number
           
           
       if (z.cx*z.cx + z.cy*z.cy < R)      //if iteration hasn't blown up...
       {
	 float X[1], Y[1];
	 X[0] = c.cx;
	 Y[0] = c.cy;
	 cpgpt(1,X,Y,17);                  // plot point c
       }
       
       
       
    }
    
   }
   
  printf("\n\n");                             
 
  cpgend();                       
  
  
 
}







//FUNCTIONS







//Iterative equation for the Mandelbrot Set

struct cnum FMANDEL( struct cnum z, struct cnum c)
{
  struct cnum value;
  value = CPROD(z,z);
  value = CADD(value,c);                // z = z^2 + c
  
  return value;
}





// Iterative equation for Julia Set

struct cnum FJULIA( struct cnum c1 )
{
  struct cnum C;                      //define constant C
  C.cx = 0.0;
  C.cy = 1.0;
  
  struct cnum value;
  value = CPROD(c1,c1);
  value = CADD(value,C);
  return value;
}





// Addition function

struct cnum CADD( struct cnum c1, struct cnum c2)
{
  double a = c1.cx;
  double b = c1.cy;
  double c = c2.cx;
  double d = c2.cy;
  
  struct cnum sum;
  sum.cx = a+c;
  sum.cy = b+d;
  
  return sum;
}





// Multiplication function

struct cnum CPROD( struct cnum c1, struct cnum c2)
{ 
  double a = c1.cx;
  double b = c1.cy;
  double c = c2.cx;
  double d = c2.cy;
  
  struct cnum product;
  product.cx = a*c - b*d; 
  product.cy = a*d + b*c;
  
  return product;
}





// print function

void CPRINT(struct cnum c)
{
  double cx = c.cx;
  double cy = c.cy;
  
  printf("\n( %0.3f , %0.3f )",cx,cy);
}
