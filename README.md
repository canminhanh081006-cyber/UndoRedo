\# UndoRedo



\## Build (MSYS2 / Git Bash)



```bash

cd /c/UndoRedo

mkdir -p build

g++ -std=c++17 -O2 -Ibaogom -Inguon -o build/undo.exe $(find nguon -name "\*.cpp")



