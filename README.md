# [SCZR] Real-time hand gesture recognition

## Build and run
```
mkdir build
cd build
cmake ..
make

./configure

# not stressed
../run_not_stressed.sh

# simulate cpu workload stress
../run_stressed.sh

# simulate cpu workload stress and run all programs in SCHED_FIFO mode
sudo ../run_stressed_fifo_all.sh

# simulate cpu workload stress and run converter in SCHED_FIFO mode
sudo ../run_stressed_fifo_conv.sh
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
