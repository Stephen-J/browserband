an experiment to get angband variants running locally in the browser.  

## Project Layout

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
2. **Building**
    1. be in project root
    2. gn gen out/browserband
    3. cd out/browserband
    4. ninja
3. **running**
    1. copy files from out/browserband and web into another directory
    2. serve the files created in step 1
    3. open up a browser and goto http://localhost:8080/angband.html

