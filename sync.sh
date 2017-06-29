
#class Cio
cp io/io.* sio/ -f
cp io/io.* gpio/ -f
cp io/io.* serial/ -f

#class Csio
cp sio/sio.* gpio/ -f

#class CAllotMem
cp allotMem/AllotMEM.* serial/ -f
cp allotMem/AllotMEM.* testEngine/src/ -f

#class Cregister
cp register/register.* io/ -f
cp register/register.* memory/ -f
cp register/register.* gpio/ -f
cp register/register.* serial/ -f
cp register/register.* sio/ -f
cp register/register.* pin/ -f

#class Cbits  sync class Cregister 
cp bits/bits.* io/ -f
cp bits/bits.* memory/ -f
cp bits/bits.* gpio/ -f
cp bits/bits.* serial/ -f
cp bits/bits.* sio/ -f
cp bits/bits.* pin/ -f
cp bits/bits.* register/ -f

#class Cpin
cp pin/pin.* gpio/ -f
