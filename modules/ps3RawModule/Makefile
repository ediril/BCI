CC		= gcc
CXX 		= g++
CFLAGS		= -g  -Wall -I../linux/include $(PS3MODDIR)
CFLAGS	       += -I$(DRAGONFLY)/include -I$(BCI_INCLUDE) -D_USE_UNIX -DUSE_LINUX  -DTESTING -DUSERTMA
CXXFLAGS        = $(CFLAGS)
LDFLAGS         = -L$(DRAGONFLY)/lib -lDragonfly

install: ps3Module
	ln -fs `pwd`/ps3Module $(BCI_BIN)/ps3RawModule
	#ln -fs `pwd`/ps3RawDefines.h $(BCI_INCLUDE)/modules/
	#ln -fs `pwd`/ps3Defines.h $(BCI_INCLUDE)/modules/	
	$(BCI_INCLUDE)/hlink

compile: ps3Module

ps3Module: jsfunc.o main.o ParamLoader.o DragonflyThread.o
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -lm $^ -o $@

clean:
	$(RM) *.o *.swp jstest *.orig *.rej map *~

jstest: jstest.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -lm $^ -o $@

