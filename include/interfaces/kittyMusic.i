#ifndef KITTYMUSIC_INTERFACE_DEF_H
#define KITTYMUSIC_INTERFACE_DEF_H
/*
** This file is machine generated from idltool
** Do not edit
*/ 

#include <exec/types.i>
#include <exec/exec.i>
#include <exec/interfaces.i>

STRUCTURE kittyMusicIFace, InterfaceData_SIZE
	    FPTR IkittyMusic_Obtain
	    FPTR IkittyMusic_Release
	    FPTR IkittyMusic_Expunge
	    FPTR IkittyMusic_Clone
	    FPTR IkittyMusic_makeLookupTable
	    FPTR IkittyMusic_FreeLookupTable
	    FPTR IkittyMusic_makeContext
	    FPTR IkittyMusic_FreeContext
	LABEL kittyMusicIFace_SIZE

#endif
