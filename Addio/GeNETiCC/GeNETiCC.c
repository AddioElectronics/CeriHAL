#include "geneticc.h"

#include <utils_assert.h>

type_size_t geneticc_get_sized_type_abs(type_sized_t type)
{
	if(type > 8 )
	return type / 8;
	else if(type >= 0 )
	return type;
	else if(type == 0)
	return sizeof(_Bool);
	else
	return type * -1;
}

signed_type_size_t geneticc_get_signed_sized_type_abs(type_sized_t type)
{
	if(type == TYPE_SIZED_BOOL)
	return sizeof(bool);
	else
	return (signed_type_size_t)type;
}

#warning untested
generic_union_t geneticc_cast_pointer(uint8_t* value, uint32_t index, type_sized_t type, type_sized_t cast_to)
{
	int8_t old_elem_size = geneticc_get_sized_type_abs(type);
	int8_t new_elem_size = geneticc_get_sized_type_abs(cast_to);
	
	byte_offset_t offset = index * old_elem_size;
	
	generic_union_t castVal = (generic_union_t)(*((uint64_t*)(value + offset)));
	
	return geneticc_cast(castVal, type, cast_to, old_elem_size, new_elem_size);
}

generic_union_t geneticc_cast_b(generic_union_t value, type_sized_t type, type_sized_t cast_to)
{
	int8_t old_elem_size = geneticc_get_sized_type_abs(type);
	int8_t new_elem_size = geneticc_get_sized_type_abs(cast_to);
	
	return geneticc_cast(value, type, cast_to, old_elem_size, new_elem_size);
}

#warning super tired, there must be a better way to accomplish this. Also, change to geneticc_t?
#warning untested

/*
*	nasty
*/
generic_union_t geneticc_cast(generic_union_t value, type_sized_t type, type_sized_t cast_to, signed_type_size_t old_elem_size, signed_type_size_t new_elem_size)
{

	switch(type)
	{
		case TYPE_SIZED_I8:
			switch(cast_to)
			{
				case TYPE_SIZED_I8:		return value;
				case TYPE_SIZED_U8:		return (generic_union_t)((uint8_t)value.s8);
				case TYPE_SIZED_I16:	return (generic_union_t)((int16_t)value.s8);
				case TYPE_SIZED_U16:	return (generic_union_t)((uint16_t)value.s8);
				case TYPE_SIZED_I32:	return (generic_union_t)((int32_t)value.s8);
				case TYPE_SIZED_U32:	return (generic_union_t)((uint32_t)value.s8);
				case TYPE_SIZED_I64:	return (generic_union_t)((int64_t)value.s8);
				case TYPE_SIZED_U64:	return (generic_union_t)((uint64_t)value.s8);
				case TYPE_SIZED_FLOAT:	return (generic_union_t)((float)value.s8);
				case TYPE_SIZED_DOUBLE:	return (generic_union_t)((double)value.s8);
				case TYPE_SIZED_BOOL:	return (generic_union_t)((_Bool)value.s8);
			}
			break;
		case TYPE_SIZED_U8:
			switch(cast_to)
			{
				case TYPE_SIZED_I8:		return (generic_union_t)((int8_t)value.u8);
				case TYPE_SIZED_U8:		return value;
				case TYPE_SIZED_I16:	return (generic_union_t)((int16_t)value.u8);
				case TYPE_SIZED_U16:	return (generic_union_t)((uint16_t)value.u8);
				case TYPE_SIZED_I32:	return (generic_union_t)((int32_t)value.u8);
				case TYPE_SIZED_U32:	return (generic_union_t)((uint32_t)value.u8);
				case TYPE_SIZED_I64:	return (generic_union_t)((int64_t)value.u8);
				case TYPE_SIZED_U64:	return (generic_union_t)((uint64_t)value.u8);
				case TYPE_SIZED_FLOAT:	return (generic_union_t)((float)value.u8);
				case TYPE_SIZED_DOUBLE:	return (generic_union_t)((double)value.u8);
				case TYPE_SIZED_BOOL:	return (generic_union_t)((_Bool)value.u8);
			}
			break;
		case TYPE_SIZED_I16:
		switch(cast_to)
			{
				case TYPE_SIZED_I8:		return (generic_union_t)((int8_t)value.s16);
				case TYPE_SIZED_U8:		return (generic_union_t)((uint8_t)value.s16);
				case TYPE_SIZED_I16:	return value;
				case TYPE_SIZED_U16:	return (generic_union_t)((uint16_t)value.s16);
				case TYPE_SIZED_I32:	return (generic_union_t)((int32_t)value.s16);
				case TYPE_SIZED_U32:	return (generic_union_t)((uint32_t)value.s16);
				case TYPE_SIZED_I64:	return (generic_union_t)((int64_t)value.s16);
				case TYPE_SIZED_U64:	return (generic_union_t)((uint64_t)value.s16);
				case TYPE_SIZED_FLOAT:	return (generic_union_t)((float)value.s16);
				case TYPE_SIZED_DOUBLE:	return (generic_union_t)((double)value.s16);
				case TYPE_SIZED_BOOL:	return (generic_union_t)((_Bool)value.s16);
			}
			break;
		case TYPE_SIZED_U16:
			switch(cast_to)
			{
				case TYPE_SIZED_I8:		return (generic_union_t)((int8_t)value.u16);
				case TYPE_SIZED_U8:		return (generic_union_t)((uint8_t)value.u16);
				case TYPE_SIZED_I16:	return (generic_union_t)((int16_t)value.u16);
				case TYPE_SIZED_U16:	return value;
				case TYPE_SIZED_I32:	return (generic_union_t)((int32_t)value.u16);
				case TYPE_SIZED_U32:	return (generic_union_t)((uint32_t)value.u16);
				case TYPE_SIZED_I64:	return (generic_union_t)((int64_t)value.u16);
				case TYPE_SIZED_U64:	return (generic_union_t)((uint64_t)value.u16);
				case TYPE_SIZED_FLOAT:	return (generic_union_t)((float)value.u16);
				case TYPE_SIZED_DOUBLE:	return (generic_union_t)((double)value.u16);
				case TYPE_SIZED_BOOL:	return (generic_union_t)((_Bool)value.u16);
			}
			break;
		case TYPE_SIZED_I32:
			switch(cast_to)
			{
				case TYPE_SIZED_I8:		return (generic_union_t)((int8_t)value.s32);
				case TYPE_SIZED_U8:		return (generic_union_t)((uint8_t)value.s32);
				case TYPE_SIZED_I16:	return (generic_union_t)((int16_t)value.s32);
				case TYPE_SIZED_U16:	return (generic_union_t)((uint16_t)value.s32);
				case TYPE_SIZED_I32:	return value;
				case TYPE_SIZED_U32:	return (generic_union_t)((uint32_t)value.s32);
				case TYPE_SIZED_I64:	return (generic_union_t)((int64_t)value.s32);
				case TYPE_SIZED_U64:	return (generic_union_t)((uint64_t)value.s32);
				case TYPE_SIZED_FLOAT:	return (generic_union_t)((float)value.s32);
				case TYPE_SIZED_DOUBLE:	return (generic_union_t)((double)value.s32);
				case TYPE_SIZED_BOOL:	return (generic_union_t)((_Bool)value.s32);
			}
			break;
		case TYPE_SIZED_U32:
			switch(cast_to)
			{
				case TYPE_SIZED_I8:		return (generic_union_t)((int8_t)value.u32);
				case TYPE_SIZED_U8:		return (generic_union_t)((uint8_t)value.u32);
				case TYPE_SIZED_I16:	return (generic_union_t)((int16_t)value.u32);
				case TYPE_SIZED_U16:	return (generic_union_t)((uint16_t)value.u32);
				case TYPE_SIZED_I32:	return (generic_union_t)((int32_t)value.u32);
				case TYPE_SIZED_U32:	return value;
				case TYPE_SIZED_I64:	return (generic_union_t)((int64_t)value.u32);
				case TYPE_SIZED_U64:	return (generic_union_t)((uint64_t)value.u32);
				case TYPE_SIZED_FLOAT:	return (generic_union_t)((float)value.u32);
				case TYPE_SIZED_DOUBLE:	return (generic_union_t)((double)value.u32);
				case TYPE_SIZED_BOOL:	return (generic_union_t)((_Bool)value.u32);
			}
			break;
		case TYPE_SIZED_I64:
			switch(cast_to)
			{
				case TYPE_SIZED_I8:		return (generic_union_t)((int8_t)value.s64);
				case TYPE_SIZED_U8:		return (generic_union_t)((uint8_t)value.s64);
				case TYPE_SIZED_I16:	return (generic_union_t)((int16_t)value.s64);
				case TYPE_SIZED_U16:	return (generic_union_t)((uint16_t)value.s64);
				case TYPE_SIZED_I32:	return (generic_union_t)((int32_t)value.s64);
				case TYPE_SIZED_U32:	return (generic_union_t)((uint32_t)value.s64);
				case TYPE_SIZED_I64:	return value;
				case TYPE_SIZED_U64:	return (generic_union_t)((uint64_t)value.s64);
				case TYPE_SIZED_FLOAT:	return (generic_union_t)((float)value.s64);
				case TYPE_SIZED_DOUBLE:	return (generic_union_t)((double)value.s64);
				case TYPE_SIZED_BOOL:	return (generic_union_t)((_Bool)value.s64);
			}
			break;
		case TYPE_SIZED_U64:
			switch(cast_to)
			{
				case TYPE_SIZED_I8:		return (generic_union_t)((int8_t)value.u64);
				case TYPE_SIZED_U8:		return (generic_union_t)((uint8_t)value.u64);
				case TYPE_SIZED_I16:	return (generic_union_t)((int16_t)value.u64);
				case TYPE_SIZED_U16:	return (generic_union_t)((uint16_t)value.u64);
				case TYPE_SIZED_I32:	return (generic_union_t)((int32_t)value.u64);
				case TYPE_SIZED_U32:	return (generic_union_t)((uint32_t)value.u64);
				case TYPE_SIZED_I64:	return (generic_union_t)((int64_t)value.u64);
				case TYPE_SIZED_U64:	return value;
				case TYPE_SIZED_FLOAT:	return (generic_union_t)((float)value.u64);
				case TYPE_SIZED_DOUBLE:	return (generic_union_t)((double)value.u64);
				case TYPE_SIZED_BOOL:	return (generic_union_t)((_Bool)value.u64);
			}
			break;
	
		case TYPE_SIZED_FLOAT:
			switch(cast_to)
			{
				case TYPE_SIZED_I8:		return (generic_union_t)((int8_t)value.f);
				case TYPE_SIZED_U8:		return (generic_union_t)((uint8_t)value.f);
				case TYPE_SIZED_I16:	return (generic_union_t)((int16_t)value.f);
				case TYPE_SIZED_U16:	return (generic_union_t)((uint16_t)value.f);
				case TYPE_SIZED_I32:	return (generic_union_t)((int32_t)value.f);
				case TYPE_SIZED_U32:	return (generic_union_t)((uint32_t)value.f);
				case TYPE_SIZED_I64:	return (generic_union_t)((int64_t)value.f);
				case TYPE_SIZED_U64:	return (generic_union_t)((uint64_t)value.f);
				case TYPE_SIZED_FLOAT:	return value;
				case TYPE_SIZED_DOUBLE:	return (generic_union_t)((double)value.f);
				case TYPE_SIZED_BOOL:	return (generic_union_t)((_Bool)value.f);
			}
			break;
		
		case TYPE_SIZED_DOUBLE:
			switch(cast_to)
			{
				case TYPE_SIZED_I8:		return (generic_union_t)((int8_t)value.d);
				case TYPE_SIZED_U8:		return (generic_union_t)((uint8_t)value.d);
				case TYPE_SIZED_I16:	return (generic_union_t)((int16_t)value.d);
				case TYPE_SIZED_U16:	return (generic_union_t)((uint16_t)value.d);
				case TYPE_SIZED_I32:	return (generic_union_t)((int32_t)value.d);
				case TYPE_SIZED_U32:	return (generic_union_t)((uint32_t)value.d);
				case TYPE_SIZED_I64:	return (generic_union_t)((int64_t)value.d);
				case TYPE_SIZED_U64:	return (generic_union_t)((uint64_t)value.d);
				case TYPE_SIZED_FLOAT:	return (generic_union_t)((float)value.d);
				case TYPE_SIZED_DOUBLE:	return value;
				case TYPE_SIZED_BOOL:	return (generic_union_t)((_Bool)value.d);
			}
			break;
		case TYPE_SIZED_BOOL:
			switch(cast_to)
			{
				case TYPE_SIZED_I8:		return (generic_union_t)((int8_t)value.b);
				case TYPE_SIZED_U8:		return (generic_union_t)((uint8_t)value.b);
				case TYPE_SIZED_I16:	return (generic_union_t)((int16_t)value.b);
				case TYPE_SIZED_U16:	return (generic_union_t)((uint16_t)value.b);
				case TYPE_SIZED_I32:	return (generic_union_t)((int32_t)value.b);
				case TYPE_SIZED_U32:	return (generic_union_t)((uint32_t)value.b);
				case TYPE_SIZED_I64:	return (generic_union_t)((int64_t)value.b);
				case TYPE_SIZED_U64:	return (generic_union_t)((uint64_t)value.b);
				case TYPE_SIZED_FLOAT:	return (generic_union_t)((float)value.b);
				case TYPE_SIZED_DOUBLE:	return (generic_union_t)((double)value.b);
				case TYPE_SIZED_BOOL:	return value;
			}
			break;
		default:
		ASSERT(false);	//Invalid type.
		break;

	}

}