# [SCZR] Real-time hand gesture recognition

## Build and run
```
mkdir build
cd build
cmake ..
make
../run.sh
```

## Prerequisites
### Install OpenCV
```
sudo apt install libopencv-dev
```

### Install gtkmm
```
sudo apt install libgtkmm-3.0-dev
```

### Install libtorch
```
cd ~
wget https://download.pytorch.org/libtorch/cpu/libtorch-win-shared-with-deps-debug-1.7.0%2Bcpu.zip
unzip libtorch-cxx11-abi-shared-with-deps-1.7.0+cpu.zip
export Torch_DIR=~/libtorch
```
