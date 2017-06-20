sh sync.sh

cd gpio
#make
make main=intel
make main=ast
cd ..

cd serial
make
cd ..

cd sio
make
cd ..

cd testEngine
make
cd ..
