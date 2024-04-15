# About

This serves as a pre-requisite repository and installation for the ARGoS-Crazyflie Python Wrapper that is based from the work of Daniel H. Stolfi and Gregoire Danoy.

Please **cite the works of Stolfi and Danoy** using this paper: **https://arxiv.org/abs/2401.16948**
To use and view the original gitlab repository: **https://gitlab.uni.lu/adars/crazyflie**

This was developed in order to easily link the ARGoS-Crazyflie Python Wrapper with additional sensors and actuators developed by **Marck Herzon Barrion.**

# New Additions:
1. Proximity Sensor (Multi-ranger Deck)
2. Ground Sensor (IR-based sensor)


# Compiling the code

Make sure you have ARGoS >= 3.0.0-beta52 installed!

1. Proceed to root directory of the project.

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
or alternatively,

```shell
cmake -DCMAKE_BUILD_TYPE=Release ../src -DCMAKE_INSTALL_PREFIX=/usr
```

For Debug builds:

```shell
cmake -DCMAKE_BUILD_TYPE=Debug
```
2. Go to /examples directory
   
```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
# Running Examples

To run the examples, go to the /examples directory of the project and run any of the codes below.

1. Proximity Sensor

```shell
argos3 -c src/experiments/crazyflie_proximity.argos
```
2. Battery Sensor and Model

```shell
argos3 -c src/experiments/crazyflie_battery.argos
```

3. Position Actuator and Sensor
```shell
argos3 -c src/experiments/crazyflie_position.argos
```

4. Speed Actuator and Sensor
```shell
argos3 -c src/experiments/crazyflie_speed.argos
```

5. LED Actuator
```shell
argos3 -c src/experiments/crazyflie_led.argos
```

6. Crazyflie LUA
```shell
argos3 -c src/experiments/crazyflie_lua.argos
```


