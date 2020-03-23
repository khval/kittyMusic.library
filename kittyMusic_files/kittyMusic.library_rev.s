VERSION = 53
REVISION = 1

.macro DATE
.ascii "23.3.2020"
.endm

.macro VERS
.ascii "kittyMusic.library 53.1"
.endm

.macro VSTRING
.ascii "kittyMusic.library 53.1 (23.3.2020)"
.byte 13,10,0
.endm

.macro VERSTAG
.byte 0
.ascii "$VER: kittyMusic.library 53.1 (23.3.2020)"
.byte 0
.endm
