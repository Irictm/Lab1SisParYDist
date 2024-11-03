main: main.cpp util/Position.cpp util/Ellipse.cpp util/FitsReader.cpp
	g++ main.cpp util/Position.cpp util/Ellipse.cpp util/FitsReader.cpp -lcfitsio -o main
