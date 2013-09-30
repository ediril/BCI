
global DF;
ButtonData = DF.MDF.PS3_BUTTON_PRESS;
ButtonData.whichButton = int32(DF.defines.PS3_B_X);
SendMessage( 'PS3_BUTTON_PRESS', ButtonData);
