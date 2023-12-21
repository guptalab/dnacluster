REM Compile the C++ program
g++ -o Main_implementation_duplicate Main_implementation_duplicate.cpp

REM Loop through thresold values from 1 to 150
for /L %%i in (70,1,150) do (
    echo Running program for thresold = %%i
    Main_implementation_duplicate %%i
)
