#!/bin/sh

echo "+---------------------------------------------+"
echo "| Exit GLUT Program with  pushing 'ESC' key!  |"
echo "| Exit Shell program with '^C'                |"
echo "+---------------------------------------------+"
./build/a.out&
pushd mobile_website
exec node app.js

