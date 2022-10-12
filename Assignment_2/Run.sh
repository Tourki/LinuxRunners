#!/bin/bash
red=`tput setaf 1`
reset=`tput sgr0`

echo -e "${red}compiling the programs${reset}"
gcc echo.c -o myecho
gcc pwd.c -o mypwd
gcc cp.c -o mycp
gcc mv.c -o mymv
echo -e "${red}compiling the programs completed${reset}"

#test echo
echo -e "${red}testing myecho${reset}"
./myecho hellow there, how are you doing?
#test pwd
echo -e "${red}testing mypwd${reset}"
./mypwd
echo -e "${red}testing mypwd error at passing any argument${reset}"
./mypwd 1
#test copy
echo -e "${red}testing mycp error at passing no argument${reset}"
./mycp
echo "${red}testing mycp error at passing few argument${reset}"
./mycp cp.c
echo -e "${red}testing mycp error at passing a source file that doesn't exist${reset}"
./mycp NAFIle cp_copy.c
echo -e "${red}testing mycp normal operation${reset}"
./mycp cp.c cp_copy.c
echo -e "${red}Cat the copyed file${reset}"
cat cp_copy.c
#test mv
echo -e "${red}testing mymv error at passing no argument${reset}"
./mymv
echo -e "${red}testing mymv error at passing few argument${reset}"
./mymv cp_copy.c
echo -e "${red}testing mymv error at passing a source file that doesn't exist${reset}"
./mymv NAFIle mv_cut.c
echo -e "${red}testing mycp normal operation${reset}"
./mymv cp_copy.c mv_cut.c
echo -e "${red}Cat the source file expecting file doesn't exist${reset}"
cat cp_copy.c 
echo -e "${red}Cat the moved file${reset}"
cat mv_cut.c
