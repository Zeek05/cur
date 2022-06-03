@echo off
echo cur.exe - manipulate the cursor in CMD

echo.

echo !! Warning!!
echo.
echo This demonstration may be cluttered due to the use of screen manipulation. Please seek the official documentation on GitHub for usage.
echo.
pause
cls
echo Welcome to the demonstration.
echo This plugin allows for various cursor related functions to be executed in the shell.
echo First, let's get our cursor position:
pause
cur get
echo You should see the exact screen coordinates (in x y format) on the screen.
echo This can be directed to files, variables or other commands.
pause
echo Now, let's set the cursor back to beginning. It will look messy until you continue.
pause
cur set 0 0
pause
cls
echo I've cleared the screen for you.
echo.
echo Now, let's toggle the cursor blink:
cur blink off
echo You should see that there is no blinking cursor to the right of the prompt now.
pause
echo Let's change the size of the blink to the full character cell (100)
cur blink on 100
echo It should be huge now!
pause
echo This is the end of the demonstration.
pause