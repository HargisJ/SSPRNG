#Define modules
Module_1 := Linear
Module_2 := Square
Module_3 := MiddleSquare
Module_4 := MarsenneTwister
Module_5 := Multiplicative
Module_6 := ISAAC

#Compile changes
edit: $(Module_1).o $(Module_2).o $(Module_3).o $(Module_4).o $(Module_5).o $(Module_6).o archive
	
#Clean, then compile
all: clean $(Module_1).o $(Module_2).o $(Module_3).o $(Module_4).o $(Module_5).o $(Module_6).o archive docs
	
#Create module object files (.o)
$(Module_1).o:source/$(Module_1).cpp source/$(Module_1).h
		g++ -c source/$(Module_1).cpp -o object/$(Module_1).o

$(Module_2).o:source/$(Module_2).cpp source/$(Module_2).h
		g++ -c source/$(Module_2).cpp -o object/$(Module_2).o

$(Module_3).o:source/$(Module_3).cpp source/$(Module_3).h
		g++ -c source/$(Module_3).cpp -o object/$(Module_3).o

$(Module_4).o:source/$(Module_4).cpp source/$(Module_4).h
		g++ -c source/$(Module_4).cpp -o object/$(Module_4).o

$(Module_5).o:source/$(Module_5).cpp source/$(Module_5).h
		g++ -c source/$(Module_5).cpp -o object/$(Module_5).o

$(Module_6).o:source/$(Module_6).cpp source/$(Module_6).h
		g++ -c source/$(Module_6).cpp -o object/$(Module_6).o

#Build library (.a)
archive: $(Module_1).o $(Module_2).o $(Module_3).o \
	$(Module_4).o $(Module_5).o $(Module_6).o
	ar csrv lib/libSSPRNG.a object/$(Module_1).o object/$(Module_2).o object/$(Module_3).o \
	object/$(Module_4).o object/$(Module_5).o object/$(Module_6).o

docs: 
	doxygen source/Doxyfile

#Delete object files and archive
clean:
	rm -rf object/$(Module_1).o object/$(Module_2).o object/$(Module_3).o object/$(Module_4).o object/$(Module_5).o object/$(Module_6).o lib/libSSPRNG.a ./docs/html ./docs/latex


