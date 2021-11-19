#ifndef GENETICC_CONFIG_H_
#define GENETICC_CONFIG_H_

#define GENETICC_OPTIMIZATION_LEVEL_SIZE		0	//Only one tested
#define GENETICC_OPTIMIZATION_LEVEL_SPEED_1	1 
#define GENETICC_OPTIMIZATION_LEVEL_SPEED_2	2 
#define GENETICC_OPTIMIZATION_LEVEL_SPEED_3	3

#define GENETICC_OPTIMIZATION_LEVEL			GENETICC_OPTIMIZATION_LEVEL_SIZE

#define GENETICC_ALWAYS_INCLUDE_TYPE_SPECIFIC true

#if GENETICC_OPTIMIZATION_LEVEL != GENETICC_OPTIMIZATION_LEVEL_SIZE

#define GENOPTI_INLINE			inline
#define GENOPTI_ATT_FORCE_INLINE		__attribute__((__always_inline__))

#else

#define GENOPTI_INLINE				
#define GENOPTI_ATT_FORCE_INLINE	

#endif
/*
*	Should DMA be used instead of standard memory functions (memcpy, memmove)
*
*	*Calling geneticc_dma_init() is required before use.
*/
#define GENETICC_USE_DMA			true



#endif /* GENETICC_CONFIG_H_ */