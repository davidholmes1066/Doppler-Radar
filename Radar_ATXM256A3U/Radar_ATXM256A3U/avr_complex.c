#include "avr_complex.h"



uint16_t avr_log2(uint16_t input)										//quick solution to math.h in avrgcc not having a log2()....
{
	uint16_t i = 0;
	uint16_t res = 1;
	
	while(res < input)
	{
		res *= 2;
		i++;
	}
	
	return i;															//return log2
}



complexfloat cf_multiply(complexfloat A, complexfloat B)
{
    complexfloat C;                                                     //Creates a complex struct to return

    C.im = (A.im * B.re) + (A.re * B.im);                               //Calculate complex part
    C.re = (-1*(A.im * B.im))+(A.re * B.re);                            //Calculate real part

    return C;                                                           //Returns complex struct
}



complexfloat cf_multiply_rf(complexfloat A, float B)
{
    complexfloat C;                                                     //Creates a complex struct to return

    C.im = A.im * B;                                                    //Calculates complex part
    C.re = A.re * B;                                                    //Calculates real part

    return C;                                                           //Returns complex struct
}



complexfloat cf_exp(float phi)
{
    complexfloat C;                                                     //Creates a complex struct to return

    if(phi > 0)                                                         //positive exponent return cos(phi) + Isin(phi)
    {
        C.re = cosf(phi);
        C.im = sinf(phi);
    }

    else                                                                //negative exponent return cos(phi) - Isin(phi)
    {
        C.re = cosf(phi);
        C.im = (sinf(phi));
    }

    return C;                                                           //return complex exponent
}



complexfloat cf_plus(complexfloat A, complexfloat B)
{
    complexfloat C;

    C.im = A.im + B.im;                                                 //Add complex components
    C.re = A.re + B.re;                                                 //Add real components

    return C;                                                           //Return complex struct
}



complexfloat cf_minus(complexfloat A, complexfloat B)
{
    complexfloat C;

    C.im = A.im - B.im;                                                 //Subtract complex components
    C.re = A.re - B.re;                                                 //Subtract real components

    return C;                                                           //Return complex struct
}