#class Cio
cp io/io.* sio/ -f
cp io/io.* gpio/ -f
cp io/io.* serial/ -f
#class Csio
cp sio/sio.* gpio/ -f
#class CAllotMem
cp allotMem/AllotMEM.* serial/ -f
cp allotMem/AllotMEM.* testEngine/src/ -f
