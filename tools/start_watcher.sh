gnome-terminal --geometry=85x29+0+0 --zoom=0.8 --window-with-profile=watchers -e "python ${BCI_ROOT}/tools/screenmon.py" --title "screens" &
gnome-terminal --geometry=60x23+680+0 --zoom=0.8 --window-with-profile=watchers -e "python ${BCI_MODULES}/MessageWatcher/MessageWatcher.py ${BCI_CONFIG}/default/message_watcher.conf" --title "messages" &
