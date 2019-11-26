#include "FPToolkit.c"

#define SWIDTH 800
#define SHEIGHT 800
#define ARR_LENGTH 800

void 
system_solver(int m, int n, double a[m][n], double x[n - 1]) 
{
  for(int i = 0 ; i < m - 1 ; i++) {
    for(int k = i + 1 ; k < m ; k++) {
      if(fabs(a[i][i]) < fabs(a[k][i])){
        for(int j = 0 ; j < n ; j++){                
          double t = a[i][j];
          a[i][j] = a[k][j];
          a[k][j] = t;
        }
     	}
  	}
  
    for(int k = i + 1 ; k < m ; k++){
    	double t = a[k][i] / a[i][i];
      for(int j = 0 ; j < n ; j++){
      	a[k][j] = a[k][j] - t * a[i][j];
    	}
  	}
  }
  
  for(int i = m - 1 ; i >= 0 ; i--) {
    x[i] = a[i][n-1];
    for(int j = i + 1 ; j < n - 1 ; j++){
      x[i] = x[i] - a[i][j] * x[j];
    }
    x[i] = x[i] / a[i][i];
  }
}

double
poly_solver(double A[], int degree, float X_CORD) 
{
	float p;
	p = A[degree];
	
	for(int i = degree ; i >= 1 ; i--) {
		p = (A[i - 1] + X_CORD * p);
	}
	return p;
}

int
main(int argc, char **argv)
{
	int degree;
	int swidth, sheight;
	int lowleftx, lowlefty, width, height;
	int n = 0;
	double p[2]; //POINTS
	double x[ARR_LENGTH], y[ARR_LENGTH]; //X-CORD AND Y-CORD
	double X_CORD, Y_CORD; //USED FOR SCREEN INPUT WHEN SOLVING POLYNOMIAL

	printf("Enter Degree of Polynomial: ");
	scanf("%d", &degree);
	printf("\n");
	
	G_init_graphics (SWIDTH, SHEIGHT);
	G_rgb (0.3, 0.3, 0.3);
	G_clear ();

	G_rgb(0.0, 0.0, 0.0);
	lowleftx = 700; lowlefty = 0; width = 100; height = 800;
	G_fill_rectangle(lowleftx, lowlefty, width, height);
	G_rgb(1, 1, 0);

	for(int i = 0; i < ARR_LENGTH; ++i) {
		G_wait_click(p);
		G_fill_circle(p[0], p[1], 2);
		if(p[0] >= 700)
			break;
		x[i] = p[0];
		y[i] = p[1];
		++n;
	}
	
	for(int i = 0; i < n; i++)
		printf(" %f , %f\n", x[i], y[i]);

	double X[2 * degree + 1];
	for(int i = 0; i <= 2 * degree; i++) {
		X[i] = 0;
		for(int j = 0; j < n; j++) {
			X[i] = X[i] + pow(x[j], i);
		}
	}

	double B[degree + 1][degree + 2];
	double Y[degree + 1];

	for(int i = 0; i <= degree; i++) {
		Y[i] = 0;
		for(int j = 0; j < n; j++) {
			Y[i] = Y[i] + pow(x[j], i) * y[j];
		}
	}

	for(int i = 0; i <= degree; i++) {
		for(int j = 0; j <= degree; j++) {
			B[i][j] = X[i+j];
		}
	}

	for(int i = 0; i <= degree; i++)
		B[i][degree + 1] = Y[i];

	double A[degree + 1];
	system_solver(degree + 1, degree + 2, B, A);
	printf("\nFitted Polynomial : \ny = ");
	for (int i = degree; i >= 0; i--) {
		printf(" + (%.17lf)x^%d", A[i], i);
	}
		
	printf("\n");

	G_rgb(1,0,0);
	
	for (X_CORD = 0; X_CORD < 750; X_CORD += 0.01) {
		Y_CORD = poly_solver(A, degree, X_CORD);
		G_point(X_CORD, Y_CORD);
	}	


	G_wait_key();
}
