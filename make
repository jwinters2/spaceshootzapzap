all:
	g++ *.cpp -o game -lGL -lGLU -lglfw -lftgl -lopenal -lalut 
-I/usr/include/freetype2
