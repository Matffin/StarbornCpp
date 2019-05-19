# StarbornCpp
Little random spiral galaxy generator. Creates 100.000-star sprites and randomizes their position inside a given function, so it looks a bit like a galaxy. Uses the SFML library.

---
### Use the project
If you just want to test the project, use the .exe inside the "Starborn_Exe" folder. 
- You can move around the galaxy with the mouse. Click&Drag to move, use the mouse wheel to zoom. 
- **"WASD"** Keys can also be used to move 
- The "Return" key generates a new galaxy inside the parameters set for the galaxy. The set star amount is 100.000

Use the **"H"** key to activate the HUD
- In the lower right corner, the HUD displays if the "rotation system" or the "shader" is enabled. These are 2 different
methods for rotating the stars. Rotation system is purely on the CPU using the ECS structure. Shader uses a GPU shader to calculate the rotation on the GPU. 
- When the rotation system is selected, the **"Q"** and **"E"** buttons can be used to control the speed. When the speed is set to 0, the rotation system is disabled, resulting in a higher framerate. 
- To switch to the shader, press the **"J"** key. The shader method has a better framerate, but has a little center position bug :) 
- While using the shader, the **"U"** and **"M"** keys can be used to control the speed. 
- The "G" button switches the HUD helper elements 

To control the galaxy parameters like star amount, the project needs to be rebuilt, as with more stars, the parameters for the generation need to be adjusted.

---

### Build the project

Basically, the project uses CMake to compile the project and the given SFML library, and the MinGW compiler for the SFML library. 

To build the project you need [SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/) as well as the correct **(Link will start download directly)** 
[MinGW 7.3.0 Compiler](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download). 

The project can be opened with any IDE that can build using CMake. A "CMakeLists" text file is provided, where the instructions are written that CMake uses 
and passes to the compiler. The project is dependent on the SFML library. This should be located in the same directory 
as the project and named "SFML-2.5.1". The "CMakeLists" file searches in the parent directory for this 
"SFML_2.5.1" folder. If the SFML library is moved the: 
``` 
set(SFML_DIR ...)
``` 
line inside the "CMakeLists" file needs to be adjusted accordingly. You can also hard-code the path to your specific SFML folder. Just copy it from the windows explorer and paste it into the SFML Dir. 
Be sure to point it to the folder: **"SFML-2.5.1/lib/cmake/SFML"** inside your SFML 2.5.1 folder.

- On windows, the SFML library needs to be built with the MinGW compiler, version 7.3.0. The IDE needs to be set to use this compiler. Then the project can be build using CMake and the 
provided "CMakeLists" file. 
The project was initially build with CLion. Inside CLion, the project can just be loaded like usual. Then, inside "File>Settings" under "Build, Execution, Deployment>Toolchains" the MinGW compiler
has to be selected. Afterwards, the project can just be build using CLion. 
- On mac, the Clang frontend should be used. https://www.sfml-dev.org/download/sfml/2.5.1/
The project has not been build on a mac yet so there could be unknown errors.

---

With any questions, as this description is short and maybe confusing, please feel free to contact me: [contact@martinritt.de](mailto:contact@martinritt.de)
Credit for the shader goes to : [Frank](https://github.com/comentator) & [Marc](https://github.com/Marc-Paul)
 