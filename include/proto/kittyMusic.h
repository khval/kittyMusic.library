#ifndef PROTO_KITTYMUSIC_H
#define PROTO_KITTYMUSIC_H

/*
**	$Id$
**
**	Prototype/inline/pragma header file combo
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_KITTYMUSIC_H
#include <libraries/kittyMusic.h>
#endif

/****************************************************************************/

#ifndef __NOLIBBASE__
 #ifndef __USE_BASETYPE__
  extern struct Library * kittyMusicBase;
 #else
  extern struct Library * kittyMusicBase;
 #endif /* __USE_BASETYPE__ */
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/kittyMusic.h>
 #ifdef __USE_INLINE__
  #include <inline4/kittyMusic.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_KITTYMUSIC_PROTOS_H
  #define CLIB_KITTYMUSIC_PROTOS_H 1
 #endif /* CLIB_KITTYMUSIC_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  extern struct kittyMusicIFace *IkittyMusic;
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_KITTYMUSIC_PROTOS_H
  #include <clib/kittyMusic_protos.h>
 #endif /* CLIB_KITTYMUSIC_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/kittyMusic.h>
  #else /* __PPC__ */
   #include <ppcinline/kittyMusic.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/kittyMusic_protos.h>
  #endif /* __PPC__ */
 #else /* __GNUC__ */
  #include <pragmas/kittyMusic_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_KITTYMUSIC_H */
