# dokun-ui

# Install dependencies
```bash
sudo apt install build-essential cmake git libx11-dev libgl1-mesa-dev libglu1-mesa-dev libvulkan-dev libglfw3-dev libopenal-dev
```


# Building dokun-ui
**To build dokun-ui as a library:**
```bash
git clone https://github.com/sidtheprince/dokun-ui.git
cd dokun-ui

mkdir build && cd build
cmake ..
make libdokun-ui -j4 && make main -j4
```

**To build the dokun-ui [Lua](https://www.lua.org/) interpreter:**
```bash
cmake -DDOKUN_BUILD_LUA_CONSOLE=1 ..
```

**To disable building the tests:**
```bash
cmake -DDOKUN_BUILD_TESTS=0 ..
```

# Using dokun-ui in your C++ project(s)
```cpp
#include <dokun_ui.hpp>
//using namespace dokun;
```

[//]: # (git checkout -b dev)
[//]: # (git add .gitignore cmake/ external/ include/ src/ test/ CMakeLists.txt README.md todo.txt)
[//]: # (git commit -m"...")
[//]: # (git push -u origin dev)
