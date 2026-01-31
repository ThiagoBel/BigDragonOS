windres storage/configs/sub_configs/bdOS.rc -O coff -o storage/configs/sub_configs/bdOS_res.o
g++ bdOS.cpp storage/configs/sub_configs/bdOS_res.o -o bdOS.exe -lwinmm
start bdOS.exe
