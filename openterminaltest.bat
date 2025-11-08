windres bdOS.rc -O coff -o bdOS_res.o
g++ bdOS.cpp bdOS_res.o -o bdOS.exe
start bdOS.exe