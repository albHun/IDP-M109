# IDP M109 Software Documentation

## Setup and Compilation Instructions
1. Login to the Linux (CentOS) system on a workstation in EIETL.
2. Put all source code in one directory (e.g. ```src```), and name the main program (the file that contains the main() function) ```main.cpp```.
3. Select ```main.cpp``` and all header files (```*.hpp``` and ```*.h```, if any) in the directory.

![main_algorithm](img/flowchart.png)
![modules](img/modules.png)
![rlink_class](img/rlink_class.png)

How to login to the microcomputer:

1. Open terminal
2. Type lg9, hit ENTER
3. When ask for password, use the one on the side of the microcomputer.


How to upload a file to the microcomputer:
1. Drag the souce .cpp file to Geany-arm on Desktop
2. In the build menu, click Make
3. In the folder, right click and choose Open in Terminal
4. If the file name is main.arm, type uploadT9 and hit ENTER, skip step 5
5. Type scp FILENAME team@wlan-robot7.private:FILENAME, replace FILENAME with the real file name
6. When ask for password, use the one on the side of the microcomputer.
