main: main.cpp util/Position.cpp util/Ellipse.cpp util/FitsReader.cpp util/HoughTransform.cpp
	g++ main.cpp util/Position.cpp util/Ellipse.cpp util/FitsReader.cpp util/HoughTransform.cpp -lcfitsio -fopenmp -o main
