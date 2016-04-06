1. 學號：B02502094
2. 姓名：蔡秉璇
3. 使用之程式語言：< C++ >
4. 使用之編譯器：< GNU g++ >
5. 檔案壓縮方式: <tar cvfz b02502094-p3-v1.tgz.gz b02502094-p3-v1>
6. 各檔案說明：
	 GlobalRouter.cpp: source code of main program
	 parser.h: headerfile of parser
	 parser.cpp: source code of parser.h
	 router: executable binary (for unix)
           . . . . . .  
7. 編譯方式說明：        	
	on Unix/Linux:
		g++ GlobalRouter.cpp parser.cpp -o router
8. 執行、使用方式說明： 
	./router [input_file_name] [output_file_name]

	ex. ./router gr4x4.in gr4x4.out
           . . . . . .         
9. 執行結果說明（說明執行結果的觀看方法，及解釋各項數據等）：
    The output file format is as follows:

   [net_id] [# of routes, k] 
   [x1,1] [y1,1] [x1,2] [y1,2] 
   [x2,1] [y2,1] [x2,2] [y2,2]
               ...

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

	       
