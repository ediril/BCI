
global DF;
ButtonData = DF.MDF.PS3_BUTTON_PRESS;
ButtonData.whichButton = int32(DF.defines.PS3_B_R1);
SendMessage( 'PS3_BUTTON_PRESS', ButtonData);
pause(0.5);
SendMessage( 'PS3_BUTTON_RELEASE', ButtonData);