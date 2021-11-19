#ifndef USING_GENETICC_COLLECTIONS_H_
#define USING_GENETICC_COLLECTIONS_H_

#if __has_include("../GeNETiCC/GeNETiCC.h")


#include "../GeNETiCC/geneticc.h"

#include "../GeNETiCC/collections/array/array_geneticc.h"
#include "../GeNETiCC/collections/list/list_geneticc.h"
//#include "../GeNETiCC/collections/dictionary/dictionary_geneticc.h"
//#include "../GeNETiCC/collections/enumerator/enumerator_geneticc.h"

#else
#error Library does not exist.
#endif

#endif /* USING_GENETICC_COLLECTIONS_H_ */