# CapOneAutomationChallenge

## Abstract
This is a coding challenge for Capital One.

## How to use:
Run this from the bin directory:
```
./processing.out {file-to-be-tested}
```
Example
```
./processing.out ../testing/test.py
```


## In This Repository
`bin/`: Compiled version of source code.

`src/`: The source code for this project written in C++. Function descriptions can be found in `processing.h`. Add additional languages in `langConfig.cpp`.

`testing/`: Sample test files can be found in this directory.

## Efficiency and Modularity
- Languages can easily be added by including their commenting symbols in the `langConfig` file.
- The program only requires memory for a single line of code.
- Additional code check-in automation features can be added easily in the processing.h file.
