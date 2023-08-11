/*
*	Includes all sub-components of Addio/Geneticc
*/
#ifndef USING_GENETICC_H_
#define USING_GENETICC_H_

#if __has_include("Addio/GeNETiCC/GeNETiCC.h")

#include "Addio/GeNETiCC/config/geneticc_config.h"
#include "Addio/GeNETiCC/GeNETiCC.h"

#include "using_geneticc_collections.h"
//#include "using_geneticc_io.h"
#include "Addio/GeNETiCC/DMA/geneticc_dma.h"

#else
#error Library does not exist.
#endif

#endif /* USING_GENETICC_H_ */