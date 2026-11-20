# Building on Windows

This fork builds with **Visual Studio 2022 (MSVC) + CMake + Ninja**. That is the
setup the `windows-build` GitHub Actions workflow uses, so it is the one that is
known to work. You need about 15 GB of free disk space.

## 1. Install the tools

- [Visual Studio 2022](https://visualstudio.microsoft.com/vs/) (Community is fine)
  with the **Desktop development with C++** workload. This includes CMake and Ninja.
- [Git for Windows](https://git-scm.com/download/win)

You do **not** need to install Qt, FFmpeg or the Vulkan SDK. CMake downloads
Qt for you on the first configure, and the Vulkan headers and shader compiler are
bundled as submodules.

## 2. Get the source

```bat
git config --global core.autocrlf input
git clone --recursive https://github.com/nallison1115/3ds-emulator.git
cd 3ds-emulator
```

If you already cloned without `--recursive`, run
`git submodule update --init --recursive`.

## 3. Build

Open **x64 Native Tools Command Prompt for VS 2022** from the Start menu, `cd`
to the repo, then:

```bat
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DENABLE_FFMPEG=OFF
cmake --build build
cmake --build build --target bundle
```

The first configure takes a few minutes because it downloads Qt. The first build
takes a while too (roughly 20 to 60 minutes depending on your CPU). Later builds
are incremental.

The finished emulator is in `build\bundle\`. Run `azahar.exe` from there. That
folder is self-contained and can be zipped and copied to another PC.

`-DENABLE_FFMPEG=OFF` drops the frame/video dumping feature, which is the only
thing that needs FFmpeg. Leave it off unless you need video recording.

### Using the Visual Studio IDE instead

Open the repo folder with **File > Open > Folder**. Visual Studio picks up
`CMakeLists.txt` automatically. Set `ENABLE_FFMPEG` to `OFF` in
**Project > CMake Settings**, pick an `x64-Release` configuration and build.

### Faster rebuilds (optional)

Install [ccache](https://ccache.dev/) and add
`-DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache`
to the configure command.

## Running tests

```bat
ctest --test-dir build -C Release --output-on-failure
```

## Alternative: MSYS2 Clang64 (not covered by CI yet)

This toolchain is not yet checked by CI, so expect rough edges.

1. Install [MSYS2](https://www.msys2.org/) and open the **CLANG64** shell.
2. Install dependencies:
   ```sh
   pacman -S --needed git mingw-w64-clang-x86_64-{clang,cmake,ninja,qt6-base,qt6-multimedia,qt6-tools}
   ```
3. Configure with the system Qt (the bundled Qt download only targets MSVC and GCC MinGW):
   ```sh
   cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DUSE_SYSTEM_QT=ON -DENABLE_FFMPEG=OFF
   cmake --build build
   ```

## Game files

This repository does not include, and the build does not download, any games or
console keys. You need to dump your own from hardware you own.
