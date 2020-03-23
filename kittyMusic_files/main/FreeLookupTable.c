/* :ts=4
 *  $VER: FreeLookupTable.c $Revision$ (16-Mar-2020)
 *
 *  This file is part of kittycraft.
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


#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/kittycraft.h>
#include <proto/kittycraft.h>
#include <stdarg.h>

/****** kittycraft/main/FreeLookupTable ******************************************
*
*   NAME
*      FreeLookupTable -- Description
*
*   SYNOPSIS
*      void FreeLookupTable(void * table);
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

void _kittymusic_FreeLookupTable(struct kittyMusicIFace *Self,
       void * table)
{
	FreeVec( table );
}

