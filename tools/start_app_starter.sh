#!/bin/bash

screen -d -m -t AppStarter -S AppStarter bash -i -c "python ${BCI_MODULES}/ApplicationControl/app_starter.py localhost:7111"
