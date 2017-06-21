sh sync.sh

cd io
make
cd ..

cd memory
make
cd ..

cd sio
make
cd ..

cd gpio
#make
make main=intel
make main=ast
cd ..

cd serial
make
cd ..

cd testEngine/src
make
cd ../..
