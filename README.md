# sound-explorer-for-picosystem
A small tool for experimenting with sound parameters on the Pimoroni PicoSystem.

Sound explorer allows you to adjust the various parameters associated with the 
`voice` function:

| Parameter             | Minimum | Maximum | Starting Value | Default Change |
| --------------------- | ------: | ------: | -------------: | -------------: |
| attack duration (ms)  |       0 |    1000 |            100 |             50 |
| decay duration (ms)   |       0 |    1000 |             50 |             50 |
| sustain percentage    |       0 |     100 |             80 |             10 |
| release duration (ms) |       0 |    1000 |            250 |             50 |
| bend frequency (hz)   |    -100 |     100 |              0 |             10 |
| bend duration (ms)    |       0 |    1000 |            100 |             50 |
| reverb duration (ms)  |       0 |    2000 |              0 |             50 |
| noise percentage      |       0 |     100 |              0 |             10 |
| distort percentage    |       0 |     100 |              0 |             10 |

As well as the parameters associated with the `play` function:

| Parameter             | Minimum | Maximum | Starting Value | Default Change |
| --------------------- | ------: | ------: | -------------: | -------------: |
| frequency (hz)        |       0 |    8000 |            440 |             50 |
| duration (ms)         |       0 |    1000 |            500 |             50 |
| volume percentage     |       0 |     100 |            100 |             10 |


The user interface uses the following controls:

| Button | Usage                                                          |
| ------ | -------------------------------------------------------------- |
| Up     | Move the selection row up                                      |
| Down   | Move the selection row down                                    |
| Left   | Lower the value for the currently selected row                 |
| Right  | Raise the value for the currently selected row                 |
| B      | Play a note based on the displayed values                      |
| Y      | Fine grained adjustment if held while pressing left or right   |
| A      | Course grained adjustment if held while pressing left or right |
| X      | Reset to original default values                               |



# Pico SDK Build Environment
```
git clone https://github.com/raspberrypi/pico-sdk.git ~/pico-sdk
cd ~/pico-sdk
git submodule update --init
export PICO_SDK_PATH="~/pico-sdk"
```

# PicoSystem SDK Build Environment
```
git clone https://github.com/pimoroni/picosystem.git ~/picosystem
mkdir ~/picosystem/build

cd ~/picosystem/build && \
cmake -DPICOSYSTEM_DIR:PATH=~/picosystem .. && \
make
```

# Building Sound Explorer
```
git clone git@github.com:dmalec/sound-explorer-for-picosystem.git
cd sound-explorer-for-picosystem
mkdir build
cd build
cmake -DPICOSYSTEM_DIR:PATH=~/picosystem ..
make
```
