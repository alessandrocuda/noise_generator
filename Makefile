#
# 'make depend' 				uses makedepend to automatically generate dependencies 
#               				(dependencies are added to end of Makefile)
# 'make'        				build executable file 'white_noise' and 'white_noise_utest'
# 'make white_noise'    		build executable file 'white_noise' 
# 'make brown_noise'    		build executable file 'brown_noise' 
# 'make white_noise_utest'     	build executable file 'white_noise_utest'

# 'make clean'  		removes all .o 
# 'make clean_all'  	removes all .o and executable files
#

# define C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS = -std=c99 -Wall -g

# define any directories containing header files other than /usr/include
#
INCLUDES =

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = 
LDFLAGS = -lm -lcmocka

# define the C source files
SOURCEDIR := ./noise_gen

#Detect system
OSFLAG 				:=
ifeq ($(OS),Windows_NT)
	OSFLAG += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSFLAG += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OSFLAG += -D IA32
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG += /usr/local/lib/libportaudio.a -lrt -lm -lasound -ljack
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG += /usr/local/opt/portaudio/lib/libportaudio.a  -framework CoreServices -framework CoreFoundation -framework AudioUnit -framework AudioToolbox -framework CoreAudio
	endif
		UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		#OSFLAG += -D AMD64
	endif
		ifneq ($(filter %86,$(UNAME_P)),)
	#OSFLAG += -D IA32
		endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		#OSFLAG += -D ARM
	endif
endif

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lpthread  



#COM_SOURCES := $(shell find $(SOURCEDIR) -name '*.c')
COM_SOURCES	:= $(SOURCEDIR)/randq/randq.c 
WNOISE_SRC	:= $(SOURCEDIR)/white_noise.c  $(SOURCEDIR)/noise_controller/noise_controller.c $(SOURCEDIR)/noise_model/noise_model.c
BNOISE_SRC	:= $(SOURCEDIR)/brown_noise.c  $(SOURCEDIR)/noise_controller/noise_controller.c $(SOURCEDIR)/noise_model/noise_model.c
WNOISEUTEST_SRC	:= $(SOURCEDIR)/white_noise_utest.c
# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
COM_OBJS = $(COM_SOURCES:.c=.o)
WNOISE_OBJS = $(WNOISE_SRC:.c=.o)
BNOISE_OBJS = $(BNOISE_SRC:.c=.o)
WNOISEUTEST_OBJS = $(WNOISEUTEST_SRC:.c=.o)
ALL_OBJ = $(COM_OBJS) $(WNOISE_OBJS) $(BNOISE_OBJS) $(WNOISEUTEST_OBJS)

# define the executable file 
WNOISE = white_noise
BNOISE = brown_noise
WNOISEUTEST = white_noise_utest

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean clean_all

all:    $(WNOISE) $(BNOISE) $(WNOISEUTEST)
		@echo white_noise, brown_noise and white_noise_utest are been compiled

$(WNOISE): $(COM_OBJS) $(WNOISE_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(WNOISE) $(COM_OBJS) $(WNOISE_OBJS) $(OSFLAG) $(LIBS)
$(BNOISE): $(COM_OBJS) $(BNOISE_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BNOISE) $(COM_OBJS) $(BNOISE_OBJS) $(OSFLAG) $(LIBS)
$(WNOISEUTEST): $(COM_OBJS) $(WNOISEUTEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(WNOISEUTEST) $(COM_OBJS) $(WNOISEUTEST_OBJS) $(LFLAGS) $(LIBS) $(LDFLAGS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
./log/log.o: ./log/log.c
	$(CC) $(CFLAGS) -DLOG_USE_COLOR -c $<  -o $@

clean:
#	$(RM) -v *.o *~ $(MAIN) $(ALL_OBJ)
	$(RM) -v $(ALL_OBJ)
clean_all:
	$(RM) -v $(MAIN) $(ALL_OBJ) $(WNOISE) $(BNOISE) $(WNOISEUTEST)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it