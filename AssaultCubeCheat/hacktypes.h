#pragma once
#include "stdafx.h"

//Error & Success codes.
#define BAD_MEM							-0xF;
#define GOOD_MEM						0;
#define EXIT_SUCCESS					0;

/*Use for altering game-functions, or anything that does not belong to game-variables.*/
typedef char							byte;
typedef unsigned short					word;
typedef unsigned long					dword;
typedef unsigned long long				qword;
typedef byte*							bytearray;
typedef byte*							byteptr;	//Generally use for addresses.

typedef void*							voidptr;	//Need an implicit data-type for a function-parameter? Use me.

/*Use signed integer types for altering game-variables only.*/
typedef signed char						int8;
typedef signed short					int16;
typedef signed int						int32;
typedef signed long						int64;

/*Use unsigned integer types for altering game-variables only (i.e Player Health, Player Ammo, Player Armor, etc.)*/
typedef unsigned char					uint8;
typedef unsigned short					uint16;
typedef unsigned int					uint32;
typedef unsigned long					uint64;


//Miscellaneous, general purpose data-types.
typedef HANDLE							handle;
typedef uint32							uint32ptr;	//Generally use for pointers.
typedef std::string						string;
typedef char							boolean;
