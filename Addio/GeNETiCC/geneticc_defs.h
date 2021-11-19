#ifndef GENETICC_DEFS_H_
#define GENETICC_DEFS_H_

#include <stdarg.h>

#define ELEMENT_PTR		uint8_t*	//A pointer to any value

/*
*	Generic Pointer Cast
*
*	For casting non standard type pointers, so they are able to be passed to the generic macros.
*
*	*If you ever see the error "cast to union type from type not present in union,"
*	*you either passed a struct pointer or other value not included in "geneticc_union."
*	*If it was not a struct, you can add the value to the union(as long as it is under 64 bits),
*	*or simply cast to a value that is in the union(Which what this macro does).
*	*Unfortunately your IDE will not display the line which calls the macro, but the macro itself,
*	*which can be difficult to track down.
*
*	ex.
*
*	struct example* x;
*	struct example a[10];
*
*	Array_IndexOf(a, CAST_STRUCT x);
*	or
*	Array_IndexOf(a, (char*) x);
*/
#define CAST_STRUCT		(char*)

enum type{
	TYPE_I8,
	TYPE_U8,
	TYPE_I16,
	TYPE_U16,
	TYPE_I32,
	TYPE_U32,
	TYPE_I64,
	TYPE_U64,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_BOOL,
	TYPE_ENUM
};
typedef uint16_t type_t;

enum type_sized{
	TYPE_SIZED_I8 = -1,
	TYPE_SIZED_U8 = 1,
	TYPE_SIZED_I16 = -2,
	TYPE_SIZED_U16 = 2,
	TYPE_SIZED_I32 = -4,
	TYPE_SIZED_U32 = 4,
	TYPE_SIZED_I64 = -8,
	TYPE_SIZED_U64 = 8,
	TYPE_SIZED_FLOAT = 32,	//geneticc_get_sized_type_abs internally divides by 8 (anything over 16 is divided)
	TYPE_SIZED_DOUBLE = 64,	//geneticc_get_sized_type_abs internally divides by 8 (anything over 16 is divided)
	TYPE_SIZED_BOOL = 0
	//TYPE_SIZED_ENUM = 4
};
typedef int16_t type_sized_t;

/*
*	Used to describe a standard value's/type's size in bytes.
*	*For standard value types only.
*/
typedef uint8_t type_size_t;



/*
*	Used to describe the value/type size in bytes.
*
*	*If you see negative numbers, it indicates the type is signed.
*	*Positive value indicates the type is unsided.
*/
typedef int8_t signed_type_size_t;


/*
*	Used to describe the size of something in bytes.
*
*	Ex.	int[2]'s index_t = 8
*/
//typedef size_t byte_size_t;	Using size_t, array size represented as length_t

/*
*	Used to describe the size of an array.
*
*	Ex.	int[2]'s length_t = 2;
*/
typedef uint32_t length_t;

/*
*	Used to describe an offset(byte index) from an array, using bytes.
*
*	Ex.	int[2]'s byte_offset_t = 8
*/
typedef uint32_t byte_offset_t;

/*
*	Used to describe an index in an array.
*
*	Ex.	int[2]'s index_t = 2
*/
typedef uint32_t index_t;


typedef size_t capacity_size_t;		//Signifies size as bytes

typedef uint32_t capacity_count_t;	//Signifies element count

#pragma region Function Pointers

typedef void (*ACTION)(ELEMENT_PTR element);

/*
*	Function pointer used for selecting values in an array with a custom set of conditions.
*
*	*Value must be cast to the array's values types.
*/
typedef bool (*PREDICATE)(const ELEMENT_PTR value);

/*
*	Function pointer used for selecting values in an array with a custom set of conditions.
*
*	*Value must be cast to the array's values types.
*/
typedef bool (*PREDICATE_ARGS)(const ELEMENT_PTR value, int arg_count, va_list ap);

/*
*	Function pointer used for comparing 2 elements.
*
*	/returns 0 : a equal to b | < 0 : a is less than b | > 0 : a is greater than b
*/
typedef int (*COMPARISON)(const ELEMENT_PTR a, const ELEMENT_PTR b);

/*
*	Function pointer used for converting an element to a different type.
*
*	/returns	The converted element.
*/
typedef ELEMENT_PTR (*CONVERTER)(ELEMENT_PTR element);

#pragma endregion Function Pointers

#endif /* GENETICC_DEFS_H_ */