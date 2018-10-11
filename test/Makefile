all: doTest doCopy doExecTest

doCopy: doCopy.cpp doCat
	g++ -g -o doCopy -std=c++11 doCopy.cpp

doCat: doCat.cpp
	g++ -g -o doCat -std=c++11 doCat.cpp

testread: testread.cpp
	g++ -g -o testread -std=c++11 testread.cpp

testwrite: testwrite.cpp
	g++ -g -o testwrite -std=c++11 testwrite.cpp

doExecTest: doExecTest.cpp doCat
	g++ -g -o doExecTest -std=c++11 doExecTest.cpp

doTest: doTest.cpp testread testwrite
	g++ -g -pthread -o doTest -std=c++11 doTest.cpp

clean:
	rm -f doTest doCopy doCat doExecTest testread testwrite