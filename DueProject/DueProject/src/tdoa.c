/*
* tdoa.c
* Calculates an (x,y,z)-coordinate in a room using the algorithm from [1].
*
* Created: 2018-04-13
* Author: Danial Mahmoud and Jonas Eiselt
*
* [1] A Synthesizable Low Power VHDL Model of the Exact Solution of
* Three Dimensional Hyperbolic Positioning System
*/

#include <asf.h>
#include <inttypes.h>
#include <stdio.h>
#include "tdoa.h"
#include <complex.h>
#include <machine\fastmath.h>
#include <math.h>

uint32_t fs = 500000;

struct transmitter_coord
{
	double xi, xj, xk, xl;
	double yi, yj, yk, yl;
	double zi, zj, zk, zl;
}coord_t;

struct tdoa{
	double tij, tik, tkj, tkl;
}tdoa_t;

void tdoa_init()
{
	coord_t.xi = 0;
	coord_t.xj = 2;
	coord_t.xk = 0;
	coord_t.xl = 2;

	coord_t.yi = 0;
	coord_t.yj = 0;
	coord_t.yk = 2;
	coord_t.yl = 2;

	coord_t.zi = 2;
	coord_t.zj = 2;
	coord_t.zk = 2;
	coord_t.zl = 2;

}

void set_tdoa(double ti, double tj, double tk, double tl){

    tdoa_t.tij = ti-tj; //0.00085; tj = 1, ti = 1.00085, tk = 0.9956, tl = 0.99397
    tdoa_t.tik = ti-tk; //0.00525;
    tdoa_t.tkj = tk-tj; //-0.0044;
    tdoa_t.tkl = tk-tl; //0.00163;
}

/*
void set_sdoa(double sample_i, double sample_j, double sample_k, double sample_l)
{
    
	tdoa_t.tij = (sample_i-sample_j)/fs;
	tdoa_t.tik = (sample_i-sample_k)/fs;
	tdoa_t.tkj = (sample_k-sample_j)/fs;
	tdoa_t.tkl = (sample_k-sample_l)/fs;

}
*/
void calculate_position(double *x, double *y, double *z)
{
	double v = 343;
	/*
	double di = 1.939;
	double dj = 3.4264;
	double dk = 2.7821;
	double dl = 3.9674;
	
	double di = 4.2308;
	double dj = 3.9370;
	double dk = 2.4290;
	double dl = 1.8708;
	*/

	/*
	double Rik = v*tdoa_t.tik;
	double Rij = v*tdoa_t.tij;
	double Rkl = v*tdoa_t.tkl;
	double Rkj = v*tdoa_t.tkj;
	*/
	double Rik = v*tdoa_t.tik;
	double Rij = v*tdoa_t.tij;
	double Rkl = v*tdoa_t.tkl;
	double Rkj = v*tdoa_t.tkj;

	double xji = coord_t.xj - coord_t.xi;
	double xki = coord_t.xk - coord_t.xi;
	double xjk = coord_t.xj - coord_t.xk;
	double xlk = coord_t.xl - coord_t.xk;

	double yji = coord_t.yj - coord_t.yi;
	double yki = coord_t.yk - coord_t.yi;
	double yjk = coord_t.yj - coord_t.yk;
	double ylk = coord_t.yl - coord_t.yk;

	double zji = coord_t.zj - coord_t.zi;
	double zki = coord_t.zk - coord_t.zi;
	double zjk = coord_t.zj - coord_t.zk;
	double zlk = coord_t.zl - coord_t.zk;


	double A = (Rik*xji-Rij*xki)/(Rij*yki-Rik*yji);
	double B = (Rik*zji-Rij*zki)/(Rij*yki-Rik*yji);
	double C = (Rik*(Rij*Rij + (coord_t.xi*coord_t.xi) - (coord_t.xj*coord_t.xj) + (coord_t.yi*coord_t.yi) - (coord_t.yj*coord_t.yj) + (coord_t.zi*coord_t.zi) -
	(coord_t.zj*coord_t.zj)) - (Rij*(Rik*Rik + (coord_t.xi*coord_t.xi) - (coord_t.xk*coord_t.xk) + (coord_t.yi*coord_t.yi) - (coord_t.yk*coord_t.yk) +
	(coord_t.zi*coord_t.zi) - (coord_t.zk*coord_t.zk))))/(2*(Rij*yki-Rik*yji));
	double D = (Rkl*xjk-Rkj*xlk)/(Rkj*ylk-Rkl*yjk);
	double E = (Rkl*zjk-Rkj*zlk)/(Rkj*ylk-Rkl*yjk);
	double F = (Rkl*(Rkj*Rkj + (coord_t.xk*coord_t.xk) - (coord_t.xj*coord_t.xj) + (coord_t.yk*coord_t.yk) - (coord_t.yj*coord_t.yj) + (coord_t.zk*coord_t.zk) -
	(coord_t.zj*coord_t.zj))-(Rkj*(Rkl*Rkl + (coord_t.xk*coord_t.xk) - (coord_t.xl*coord_t.xl) + (coord_t.yk*coord_t.yk) -
	(coord_t.yl*coord_t.yl) + (coord_t.zk*coord_t.zk) - (coord_t.zl*coord_t.zl))))/(2*(Rkj*ylk-Rkl*yjk));
	double G = (E-B)/(A-D);
	double H = (F-C)/(A-D);
	double W = A*G + B;
	double J = A*H + C;
	double K = Rik*Rik + (coord_t.xi*coord_t.xi) - (coord_t.xk*coord_t.xk) + (coord_t.yi*coord_t.yi) - (coord_t.yk*coord_t.yk) +
	(coord_t.zi*coord_t.zi) - (coord_t.zk*coord_t.zk) + 2*xki*H+2*yki*J;
	double L = 2*(xki*G+yki*W+2*zki);
	double M = 4*Rik*Rik*(G*G+W*W+1)-L*L;
	double N = 8*Rik*Rik*(G*(coord_t.xi-H) + W*(coord_t.yi-J) + coord_t.zi) + (2*L*K);
	double O = 4*Rik*Rik*(((coord_t.xi-H)*(coord_t.xi-H)) + ((coord_t.yi-J)*(coord_t.yi-J)) + coord_t.zi*coord_t.zi) - K*K;

	//z1 = (N/(2*M))+sqrt((N/(2*M))^2-(O/M))
	double complex Imz = (N/(2*M))+csqrt((N/(2*M))*(N/(2*M))-(O/M));
	double complex Imx = G*(Imz) + H;
	double complex Imy = W*(Imz) + J; 
	*z = crealf(Imz); //crealf(Imz);
	*x = crealf(Imx);
	*y = crealf(Imy);
}

