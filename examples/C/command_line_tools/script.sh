#!/bin/bash
echo "--------------------------------------------------------------------"
echo " "
echo "§ Testing utiluty 'cp.c'"
echo " "
gcc cp.c


echo ">> Test 1: correct call, creating copy"
echo "* calling cp.c ./dir1/file1.txt ./dir1/new_file_1.txt"
./a.out ./dir1/file1.txt ./dir1/new_file_1.txt
echo "* let's check, if everything is fine"
echo "* let's call ls ./dir1"
echo " "
echo " "
ls ./dir1
cmp ./dir1/file1.txt ./dir1/new_file_1.txt

echo " "
echo " "
echo ">> Test 2: trying to create already existing file"
echo "* calling cp.c ./dir1/file1.txt ./dir1/new_file_1.txt"
echo " "
echo " "
./a.out ./dir1/file1.txt ./dir1/new_file_1.txt

echo " "
echo " "
echo ">> Test 3: trying to call cp with same arguments"
echo "* calling cp.c ./dir1/file1.txt ./dir1/file1.txt"
echo " "
echo " "
./a.out ./dir1/file1.txt ./dir1/file1.txt

echo " "
echo " "
echo ">> Test 4: trying to call cp with only parameter"
echo "* calling cp.c ./dir1/file1.txt"
echo " "
echo " "
./a.out ./dir1/file1.txt

echo " "
echo " "
echo ">> Test 5: trying to call cp with more, then two parameters"
echo "* calling cp.c ./dir1/file1.txt a.txt b.txt c.txt"
echo " "
echo " "
./a.out ./dir1/file1.txt a.txt b.txt c.txt

echo " "
echo " "
echo ">> Test 6: trying to open not existing file"
echo "* calling cp.c file2.txt ./dir1/file2_new.txt"
echo " "
echo " "
./a.out file2.txt ./dir1/file2_new.txt
echo " "
echo " "

echo "§ Testing cp.c finished"
echo " "
echo "--------------------------------------------------------------------"
echo " "
echo "§ Testing utility 'cmp.c'"
echo " "
gcc cmp.c

echo " "
echo ">> Test 1: correct call, different files"
echo "* calling cmp.c ./dir2/file1.txt ./dir2/file2.txt"
echo " "
echo " "
./a.out ./dir2/file1.txt ./dir2/file2.txt

echo " "
echo " "
echo ">> Test 2: correct call, identic files"
echo "* calling cmp.c ./dir2/file1.txt ./dir2/file1.txt"
echo " "
echo " "
./a.out ./dir2/file1.txt ./dir2/file1.txt

echo " "
echo " "
echo ">> Test 3: trying to call cmp with only one parameter"
echo "* calling cmp.c ./dir2/file1.txt"
echo " "
echo " "
./a.out ./dir2/file1.txt

echo " "
echo " "
echo ">> Test 4: trying to call cmp with more, then two parameters"
echo "* calling cmp.c ./dir2/file1.txt a.txt b.txt c.txt"
echo " "
echo " "
./a.out ./dir2/file1.txt a.txt b.txt c.txt

echo " "
echo " "
echo ">> Test 5: trying to open not existing file"
echo "* calling cmp.c ./dir2/nope.txt ./dir2/file1.txt"
echo " "
echo " "
./a.out ./dir2/nope.txt ./dir2/file1.txt

echo " "
echo " "
echo "§ Testing cmp.c finished"
echo " "
echo "--------------------------------------------------------------------"
echo " "


echo "§ Testing utility 'cat.c'"
gcc cat.c

echo " "
echo ">> Test 1: correct call, one file, without flag"
echo "* calling cat.c ./dir3/file1.txt"
echo " "
echo " "
./a.out ./dir3/file1.txt

echo " "
echo " "
echo ">> Test2: correct call, several files, without flag"
echo "* calling cat.c ./dir3/file1.txt ./dir3/file2.txt ./dir3/file3.txt"
echo " "
echo " "
./a.out ./dir3/file1.txt ./dir3/file2.txt ./dir3/file3.txt

echo " "
echo " "
echo ">> Test3: correct call, several files, with flag"
echo "* calling cat.c -n ./dir3/file1.txt ./dir3/file2.txt ./dir3/file3.txt"
echo " "
echo " "
./a.out -n ./dir3/file1.txt ./dir3/file2.txt ./dir3/file3.txt

echo " "
echo " "
echo ">> Test 4: trying to call with less parameters then required"
echo "* calling cat.c"
echo " "
echo " "
./a.out

echo " "
echo " "
echo ">> Test 5: trying to open not existing file"
echo "* calling cat.c ./dir3/nope.txt"
echo " "
echo " "
./a.out ./dir3/nope.txt
echo " "
echo " "

echo "§ Testing cat.c finished"

echo " "
echo "* let's delete a.out and created file dir1/new_file_1.txt"
rm ./a.out
rm ./dir1/new_file_1.txt

echo "Testing finished!"
echo " "
echo "--------------------------------------------------------------------"
