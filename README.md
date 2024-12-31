# C BMP imageprocessor

## Directories

### `src/`

Contains the source `.c` and `.h` files.

### `dev/`

Contains files from development, not relevant to final code.

### `test/`

Contains files used for testing executable. For the shell script to work the executable must be names `imageprocessor` and be in the same directory as the `bmp_examples/` directory.

### `bmp_examples/`

Contains example BMP files, and the results of running different operations on them.

### `bin/`

Contains a executable compiled for Apple Silicon Macs.

## Compiling

To compile the code into an executable name `imageprocessor`, change your working directory to the base directory of the repository, and run:
`gcc src/main.c src/io.c src/process.c -o bin/imageprocessor`

Note: this will replace the existing executable in `bin/`, to make an executable with a different name, simply replace `imageprocessor` in the command with a name of your choice.

## Usage

### General Operations

#### `cat input.bmp | imageprocessor OPERATION > output.bmp`

#### HFLIP

`cat input.bmp | imageprocessor HFLIP > output.bmp`

#### VFLIP

`cat input.bmp | imageprocessor VFLIP > output.bmp`

#### GRAYSCALE

`cat input.bmp | imageprocessor GRAYSCALE > output.bmp`

### Other Operations

#### INFO

`cat input.bmp | imageprocessor INFO`

#### HELP

`imageprocessor HElP`

#### Note: To use the executable as `imageprocessor` instead of `./imageprocessor` you must copy it to `usr/local/bin`.
