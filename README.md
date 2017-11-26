# A small example WebAssembly / Native SDL app

An example of creating a simple SDL app that can be cross compiled to WebAssembly.

Clonet the repo and install submodules, run `git submodule update --init --recursive`.

# To compile the WebAssembly version:

````
mkdir build
cd build
cmake ..
make
````

to run: `python -m SimpleHTTPServer` then open `http://localhost:8000`

# To compile natively (only tests on OS X)

````
mkdir build
cd build
cmake -DWASM=OFF ..
make
```

to run: `./main`


Example tiger image by Shane Gorski (https://www.flickr.com/photos/shanegorski/2515009456/in/photostream/)