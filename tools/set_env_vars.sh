export BCI_ROOT=/home/vr/rp3/tmp/BCI

export BCI_INCLUDE=${BCI_ROOT}/message_definitions
export BCI_COMMON=${BCI_ROOT}/modules/Common
export BCI_MODULES=${BCI_ROOT}/modules
export BCI_CONFIG=${BCI_ROOT}/app_configs
export BCI_DATA=${BCI_ROOT}/data

export PYTHONPATH=$PYTHONPATH:${BCI_INCLUDE}:${BCI_COMMON}/python

export PATH=$PATH:${BCI_ROOT}/tools
