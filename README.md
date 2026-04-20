ECE365 Maze Project - Build & Run Instructions
Environment: Windows, Visual Studio 2019

BUILD :
1. Open: Start Menu → Developer Command Prompt for VS 2019
2. cd into the folder containing the unzipped .cpp and .h files
3. cl /EHsc /std:c++17 main.cpp maze2d.cpp path1d.cpp pathTraversal.cpp point2d.cpp /Fe:maze.exe

RUN via test batch files:
4. Copy maze.exe into the test\ directory (alongside the TestXX folders)
5. cd into any testcase folder (e.g. test\Test01_NormalCase_GOOD)
6. run.bat