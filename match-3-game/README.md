## Match 3 Game 
A Match 3 Game made using Raylib 

Requirements:
- Raylib (version 6.0)

### Install `raylib` on Ubuntu 26.04 LTS

```bash
sudo apt install build-essential git cmake \
    libasound2-dev libx11-dev libxrandr-dev libxi-dev \
    libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev \
    libxinerama-dev libwayland-dev libxkbcommon-dev

git clone --depth 1 https://github.com/raysan5/raylib.git

cd raylib

mkdir build && cd build

cmake ..

make

sudo make install

sudo ldconfig
```
