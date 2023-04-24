#include <math.h>



float temp(float adcVal){
	
	float U_th, R_th, R_1 = 10000.0, U = 3.3, B = 3950.0, R_0 = 10000.0, T_0 = 298.0, T_inv, T;
	
	// Beregner temperatur til termistor, T
	U_th = adcVal * U/1023.0;
	R_th = (R_1*U_th)/(U - U_th);
	T_inv = (1.0/T_0) + ((1.0/B)*log(R_th/R_0));
	T = 1.0/T_inv-273.0;
	
	return T;
}