#ifndef READER_CONFIG_H_
#define READER_CONFIG_H_


#if __has_include("../../../timing/system_timer/system_timer.h")
#define READER_USE_TIMER //Comment if using your systems timer for something else, or if the board is unsupported.
#endif



#endif /* READER_CONFIG_H_ */