Language: C++
Compiler: GNU g++
File Description:
	GlobalRouter.cpp: source code of main program
	parser.h: headerfile of parser
	parser.cpp: source code of parser.h
	router: executable binary (for unix)
Compile Description:
	on Unix/Linux:
		g++ GlobalRouter.cpp parser.cpp -o router
Usage: 
	./router [input_file_name] [output_file_name]

	ex. ./router gr4x4.in gr4x4.out
Result:
    The output file format is as follows:

   [net_id] [# of routes, k] 
   [x1,1] [y1,1] [x1,2] [y1,2] 
   [x2,1] [y2,1] [x2,2] [y2,2]

   ex.
   0 5
   2 3 1 3
   1 3 1 2
   1 2 0 2
   0 2 0 1
   0 1 0 0
   1 5
   0 2 1 2
   1 2 2 2
   2 2 2 1
   2 1 3 1
   3 1 3 0
   2 3
   1 0 1 1
   1 1 1 2
   1 2 1 3

	       
