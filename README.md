
This repo provides several software modules you can use to setup your own BCI experiments.
We use these modules in our own experimental setups at [Motorlab](http://schwartzlab.neurobio.pitt.edu) and we are releasing them so you 
can get a head start and not have to build your own modules from scratch which would take a long time.

## Prerequisites

1. Install [Dragonfly](https://github.com/dragonfly-msg/dragonfly)

2. Several of the python modules require `numpy`, `scipy`, `matplotlib`, `traits`, `traitsui`, `pyface` and `wxPython`

3. Install `PyQt` from [here](http://www.riverbankcomputing.com/software/pyqt/download). 
You need py2.7 version and make sure you install the one that matches your python build (32-bit or 64-bit)

4. On Linux, scripts in `tools` folder use `screen` so make sure you have it installed (sudo apt-get install screen)

## Installation

#### Linux

Clone the repository and set the following environment variables in a permanent place like .bashrc
and make sure you export them:

 - Set `BCI_ROOT` to the where you placed your BCI folder
 - Set `BCI_INCLUDE` to `${BCI_ROOT}/message_definitions`
 - Set `BCI_COMMON` to `${BCI_ROOT}/modules/Common`
 - Set `BCI_MODULES` to `${BCI_ROOT}/modules`
 - Set `BCI_CONFIG` to `${BCI_ROOT}/app_configs`
 - Set `BCI_DATA` to `${BCI_ROOT}/data`
 - Append `${BCI_INCLUDE}` and `${BCI_COMMON}/python` to `PYTHONPATH` environment variable

For reference, see `set_env_vars.sh` in `tools` folder.

#### Windows

Use the [installer](https://github.com/ediril/BCI-binaries/blob/master/bci_windows_setup.exe?raw=true) which will also set all the necessary environment variables.

## After Installation

To play with the example configuration in `${BCI_ROOT}/app_configs`, run the following scripts from `${BCI_ROOT}/tools` in the 
order shown below. Note that scripts for windows have `.bat` extensions while scripts for linux have `.sh` extensions

1. start_message_manager
2. start_quick_logger
3. start_watcher
4. start_app_starter
5. start_appman_gui

When Appman GUI window pops up, select the configuration for your system, click `START` and the virtual experiment will start running.

