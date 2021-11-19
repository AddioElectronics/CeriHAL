#ifndef PRINT_GENETICC_INTERNAL_FUNCTIONS_H_
#define PRINT_GENETICC_INTERNAL_FUNCTIONS_H_

/*
*	Gets the modulo's divisor value used in the print_data_base functions.
*/
static uint8_t internal_get_base_padding(uint8_t base)
{
	switch(base)
	{
		case 2:		return 8;
		case 8:		return 3;
		case 10:	return 3;
		case 16:	return 2;
		case 64:	return 4;
	}
	
	return "";
}



#endif /* PRINT_GENETICC_INTERNAL_FUNCTIONS_H_ */