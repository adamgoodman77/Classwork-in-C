#include <stdio.h>
#include <math.h>

int main(void){

// Variable declaration
double res_Area; // reservoir surface area
double Ein; // Energy into system
double n_s; // system efficiency
double fill_Time; // time to fill reservoir
double empty_Time; // time to empty reservoir
double n_p = 0; // pump efficiency
double n_t = 0; // turbine efficiency
double D; // pipe diameter
double L; // pipe length
double f; // pipe friction factor
double res_Depth; // reservoir depth
double H; // elevation from bottom of reservoir 
double Qpump; // volumetric flow rate of pump
double QTurbine; // volumetric flow rate of turbine
double pipe_Area, V_Up, V_Down, head_Loss_Up, head_Loss_Down;
double fit_Loss_Up, fit_Loss_Down; 
double E_Out_J, E_LossUp_J, res_Vol, K1, K2, m_Water = 0, Ein_J;


// Constants
double const E_Out = 120; // MWh
double const g = 9.8; // m/s^2 
int const water_Row = 1000; // kg/m^3
double const PI= 4*atan(1);

// inputs

printf("Please enter desired pump efficiency: ");
scanf("%lf", &n_p);
printf("Please enter desired turbine efficiency: ");
scanf("%lf", &n_t);
printf("Please enter pipe diameter in meters: ");
scanf("%lf", &D);
printf("Please enter pipe length in meters: ");
scanf("%lf", &L);
printf("Please enter bend coefficient 1: ");
scanf("%lf", &K1);
printf("Please enter bend coefficient 2: ");
scanf("%lf", &K2);
printf("Please enter pipe friction factor: ");
scanf("%lf", &f);
printf("Please enter reservoir depth in meters: ");
scanf("%lf", &res_Depth);
printf("Please enter elevation of bottom of reservoir in meters: ");
scanf("%lf", &H);
printf("Please enter volumetric flow rate of pump: ");
scanf("%lf", &Qpump);
printf("Please enter volumetric flow rate of turbine: ");
scanf("%lf", &QTurbine);

E_Out_J = E_Out * 3600000000; // MWH to joules


// intermediate calculations
pipe_Area = PI* pow((D / 2), 2);

V_Up = Qpump / (PI* pow(D / 2.0, 2));
V_Down = QTurbine / (PI* pow(D / 2.0 , 2));

head_Loss_Up = f * (L / D) * (pow(V_Up, 2) / (2 * g));

head_Loss_Down = f * (L / D) * (pow(V_Down, 2) / (2 * g));
	
fit_Loss_Up = 2 * K1 * pow(V_Up, 2) / (2 * g);
	
fit_Loss_Down = 2 * K2 * pow(V_Down, 2) / (2 * g);


//printf("Head loss down = %lf\n", head_Loss_Down); // error checking
//printf("Fit loss down = %lf\n", fit_Loss_Down); // error checking

// Important intermediate calculation
m_Water = (E_Out_J / n_t) / 
	(g * (H + (res_Depth / 2.0) - head_Loss_Down - fit_Loss_Down));
//m_Water = 1070000000;
// Res Area needed 

res_Vol = m_Water / water_Row;
res_Area = res_Vol / res_Depth;

double E_Necessary;
E_LossUp_J = ((fit_Loss_Up + head_Loss_Up)) * m_Water * g;
E_Necessary = m_Water * g * (H + (res_Depth / 2));
Ein_J = (E_Necessary + E_LossUp_J) / n_p;
Ein = Ein_J / 3600000000.0;
n_s = E_Out / Ein;
fill_Time = res_Vol / Qpump / 3600.0;
empty_Time = res_Vol / QTurbine / 3600.0;

//Displaying intermediate calulations
/*
printf("The pipe area is %.2lf m^2", pipe_Area);
printf("\nThe velocity on the way up is %.2lf m/s", V_Up);
printf("\nThe velocity on the way down is %.2lf m/s", V_Down);
printf("\nThe energy output in joules is %.2lf J.", E_Out_J);
printf("\nThe mass stored in reservoir is %.2lf kg.", m_Water);
*/

// outputs
printf("\nThe reservoir surface area is %.2lf m^2.\n", res_Area);
printf("The input energy is %.2lf MWH.\n", Ein);
printf("The system efficiency is %.2lf\n", n_s);
printf("The time to fill the reservoir is %.2lf hours.\n", fill_Time);
printf("The time to empty the reservoir is %.2lf hours.\n", empty_Time);



return 0;
}

