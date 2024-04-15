# About

This serves as a pre-requisite repository and installation for the ARGoS-Crazyflie Python Wrapper that is based from the work of Daniel H. Stolfi and Gregoire Danoy.

Please **cite the works of Stolfi and Danoy** using this paper: **https://arxiv.org/abs/2401.16948**
To use and view the original gitlab repository: **https://gitlab.uni.lu/adars/crazyflie**

This was developed in order to easily link the ARGoS-Crazyflie Python Wrapper with additional sensors and actuators developed by **Marck Herzon Barrion.**

# Compiling the code

Make sure you have ARGoS >= 3.0.0-beta52 installed!

Commands:

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../src
make
sudo make install
```

If ARGoS does not find the new robot, try:

```shell
cmake -DCMAKE_BUILD_TYPE=Release ../src -DCMAKE_INSTALL_PREFIX=/usr/local
```

For Debug builds:

```shell
cmake -DCMAKE_BUILD_TYPE=Debug
```
