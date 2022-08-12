#pragma once

#include "Globals.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

//  NULL just in case ----------------------

#ifdef NULL
#undef NULL
#endif
#define NULL  0

// Deletes a buffer
#define RELEASE( x ) \
    {                        \
    if( x != NULL )        \
	    {                      \
      delete x;            \
	  x = NULL;              \
	    }                      \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
    {                              \
    if( x != NULL )              \
	    {                            \
      delete[] x;                \
	  x = NULL;                    \
	    }                            \
                              \
    }

#define IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )
#define TO_BOOL( a )  ( (a != 0) ? true : false )

typedef unsigned int uint;
typedef unsigned char uchar;

template <class VALUE_TYPE> void SWAP(VALUE_TYPE& a, VALUE_TYPE& b)
{
	VALUE_TYPE tmp = a;
	a = b;
	b = tmp;
}

// Standard string size
#define SHORT_STR	32
#define MID_STR		255
#define HUGE_STR	8192

// Joins a path and file
inline const char* const PATH(const char* folder, const char* file)
{
	static char path[MID_STR];
	snprintf(path, MID_STR, "%s/%s", folder, file);
	return path;
}

inline const char* const PATH_EXISTS(const char* section_subdir, const char* file)
{
	char prefix[MID_STR];
	snprintf(prefix, MID_STR, "%s/%s/", "data", section_subdir);
	char* rel_path = strdup(PATH(prefix, file));
	char* abs_path = strdup(PATH(DATADIR, rel_path));
	char* path = abs_path;
	struct stat sb;
	if(stat(path, &sb) == -1)
	{
		if(stat(rel_path, &sb) == -1)
		{
			LOG("Could not locate filename: %s", rel_path);
			return NULL;
		}
		free(abs_path);
		path = rel_path;
	}
	return path;
}
