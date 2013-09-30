#!/bin/bash

screen -d -m -t AppmanGui -S AppmanGui  bash -i -c "python ${BCI_MODULES}/ApplicationControl/appman_gui.py localhost:7111"
