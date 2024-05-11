DIR=`pwd`
if [ -d build ];then
  rm -r build
fi

if [ -d output ];then
  rm -r output
fi
mkdir build
cd build
cmake ..
make -j8
make install
cd $DIR


# make sample
cd sample
if [ -d build ];then
  rm -r build
fi 
mkdir build
cd build
cmake ..
make -j8