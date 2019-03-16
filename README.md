an experiment to get angband variants running locally in the browser.  

#### Note : this is a work in progress , still setting up


## Project Layout
###### /bin
dart tools for development
###### /bands
submodules for angband variants
###### /build
build files for gn including build files specific to angband variants
###### /src
code for angband variants specific to running in the browser
###### /web
web files

## Building

1. **Requirements**
    * gn build tool - [gn](https://gn.googlesource.com/gn/)
    * dart sdk - [sdk](https://www.dartlang.org/tools/sdk)
    * ninja build tool - [ninja](https://ninja-build.org/)
    * emscripten - [emscripten](https://emscripten.org/)
2. **Building**
    * **Linux**
        1. source emsdk_env.sh
        2. be in project root
        3. gn gen out/browserband
        4. cd out/browserband
        5. ninja
    * **Windows**
        * not supported yet
3. **running**
    * **Linux**
        1. dart bin/dev_server.dart
    * **Windows**
        * not supported yet

