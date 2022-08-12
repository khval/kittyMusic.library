/* :ts=4
 *  $VER: FreeContext.c $Revision$ (22-Mar-2020)
 *
 *  This file is part of kittyCraft.
 *
 *  Copyright (c) 2020 LiveForIt Software.
 *  MIT License..
 *
 * $Id$
 *
 * $Log$
 *
 *
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/kittycraft.h>
#include <proto/kittyCraft.h>
#include <stdarg.h>

/****** kittyCraft/main/FreeContext ******************************************
*
*   NAME
*      FreeContext -- Description
*
*   SYNOPSIS
*      void FreeContext(void * table);
*
*   FUNCTION
*
*   INPUTS
*       table - 
*
*   RESULT
*       This function does not return a result
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*
*****************************************************************************
*
*/

extern void free_mod( struct context *context );

void _kittymusic_FreeContext(struct kittyMusicIFace *Self,
       void * context)
{
	free_mod(context);
	free(context);
}

