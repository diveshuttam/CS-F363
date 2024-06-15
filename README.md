# CS-F363
Compiler Construction Group 34

# INSTRUCTIONS (for Linux)

- clone this repo: `git clone https://github.com/diveshuttam/CS-F363`
- `cd CS-F363`
- create a folder named `build` in the above directory: `mkdir build` 
- run `make deubg` for running with debug output (runs always automatically with file `a.mylang` to save time during debugging)
- run `make all` for output without debug statements (asks for which file to compile)

# Graphics output
- run `make graphics` to print graphics output
- create json file for tree using `./visualize_exe ./testcases/testcase1.txt ./testcases/testcase1.json`
- open visualize/visualize.html in a browser
- select the json file (here testcases1.json) to visualize the tree output

One can also visualize a json file at https://diveshuttam.github.io/CS-F363/graphics/visualize

<img width="1437" alt="AST" src="https://github.com/diveshuttam/CS-F363/assets/20728015/0050f786-ca5f-4ebc-9929-f9b376acf979">


# Notes:
 - Remember to free whatever is malloc'ed else  we get random malloc errors
