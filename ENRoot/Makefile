# MAKE FILE FOR ENROOT
OBJ = ENConvert
#sourcefile = ENMain.cxx TENUnpack.cxx TENDumptxt.h TENDumptxt.cxx TENUnpack.h TENPPAC_Sort.cxx TENPPAC_Sort.h TENPla_Sort.cxx TENPla_Sort.h TENNaI_Sort.cxx TENNaI_Sort.h TENIonChamb_Sort.cxx TENIonChamb_Sort.h TENSSD_Sort.cxx TENSSD_Sort.h TENTS_Sort.cxx TENTS_Sort.h 

sourcefile = ENMain.cxx ENMain.h ENPPAC_Calibration.cxx ENPPAC_Calibration.h ENFiberCal.cxx ENFiberCal.h

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

CFLAGS = -Wall -O2 -I$(TARTSYS)/include -I$(ROOTSYS)/include -L$(TARTSYS)/lib -lXMLParser -lanacore

GXX = g++ -std=c++0x

all:$(OBJ)

$(OBJ): $(sourcefile)
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ $(filter %.cxx ,$(sourcefile)) 

clean:
	rm -f *~ *.o $(OBJ)
