# Classroom-OpenGL
YOLO

Classroom Model using OpenGL

Maths is the king when using OpenGL, Used the contents of the syllabus of Computer Graphics in this project.
YES!!!!, the matrices, matrices and a lot of matrices and their minglings, scuffles and everything!

Setup:
1. Have the Include, DLL and Lib folders from this repo in your project soln folder. Use them:( at the courtesy of OPENGLDEV the og)
!!!(always make sure the config and platform is setup as you require)
2. Make sure the dll is understood by setting up Project Properties> General Configs> Debugging>Environment : PATH=%PATH%;..\DLL 
3. Have the necessary libs defined in the linker setting: Linker>Input>Additional Dependencies
4. Define the additional lib directory in Linker>General: ../Lib if it is in the project soln folder
5. Define the additional include directory in c/c++>General : ../Include if it is in the project soln folder
6. Have the assets in your project soln directory

Used Dependencies:
freeglut(or glfw) 
glew
assimp//--obj loader
stb_image//--lighting
OGLDEV (THE GUY!!)//--basic opengl classes

PS: 
the model is basic but maths is used for most of the aspects of the program as accord to computer graphics syllabus IOE 5th sem.
You can always use Blender, Maya and other modelling softwares for more professional and extensive modelling purpose.
With Programming Graphics, you can always go a little in depth and maybe way more in depth, and maybe even create your our engine or even  garphics languague:)
Good Luck!
