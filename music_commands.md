n=Mubase 

n=Vumeter(n)

	Returns volume of audio channel [n], 
	should only work with music, not samples.

Voice n

Music Off

Music Stop 

Tempo n

	Set playback tempo

Music [n]

	play music [n] from the bank

Noise To [n]

	Play noise on audio channel [n]

Boom 

	Play boom sound.

Shoot 

	Play shoot sound.

Sam Bank [bank]

	set default samplebank

Sam Loop On 

	Turn on sample loop on all voices/channels.

Sam Loop On [voice]

	Enable sample loop on voices defined.

	voice 1 audio channel 0
	voice 2 audio channel 1
	voice 4 audio channel 2
	voice 8 audio channel 3

	Sam Loop On 1+2

	enable sound on channel 0 and 1

	Sam loop On 4+8

	enable sound on channel 4 and 8

	(This version of the command is only for Amos Kittens, 
	does not work on Amos Pro.)

Sam Loop Off 

	Turn off sample loop on all voices/channels.

Sam Loop Off [voice]

	Enable sample loop on voices defined.

	Voice 1 audio channel 0
	Voice 2 audio channel 1
	Voice 4 audio channel 2
	Voice 8 audio channel 3

	Sam Loop Off 1+2

	Disable sound on channel 0 and 1

	Sam loop Off 4+8

	Disable sound on channel 4 and 8

	(This version of the command is only for Amos Kittens, 
	does not work on Amos Pro.)

Sample n To n

Sam Play [sample]

Sam Play [voices],[sample]

	Plays a 8bit sample from the abk sample bank.

	Samples can 8svx sound can be made with "Audacity" on windows.
	You can then import the sound into the sample bank.

Sam Play n,n,n

Sam Raw n,n,n,n

Bell 

	play a bell sound

Bell n

Play Off 

Play Off n

Play n,n

Play n,n,n

Set Wave [n],[string$]

	Make a synth sound [n] from [string$]

Del Wave n

	Delete wave [n], waves are synth-sounds.

Set Envel n,n To n,n

	Create envel on a synth-sound.

Mvolume n

Volume [value]

	Set volume on all channels to [value]

Volume n,n

Wave n To n

Led On 

	Enable loudness filter, (lowpass filter)

Led Off 

	Disable loudness filter, (lowpass filter)

Say s$

Say s$,n

Set Talk n,n,n,n

Sload n To n,n

n=Sam Swapped(n

Sam Swap n To n,n

Sam Stop 

Sam Stop n

Track Stop 

Track Loop On 

Track Loop Of 

Track Play 

Track Play n

Track Play n,n

Track Load s$,n

n=Mouth Width 

n=Mouth Height 

Mouth Read 

Talk Stop 

Talk Misc n,n

Ssave n,n To n

Med Load s$,n

Med Play 

Med Play n

Med Play n,n

Med Stop 

Med Cont 

Med Midi On 

