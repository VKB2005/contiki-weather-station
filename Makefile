CONTIKI = ../..

all: sensor-node base-station

CONTIKI_PROJECT = sensor-node base-station
include $(CONTIKI)/Makefile.include
