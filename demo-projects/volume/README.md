[Lab 4: Volume](https://cs50.harvard.edu/college/2020/fall/labs/4/#lab-4-volume)
================================================================================

You are welcome to collaborate with one or two classmates on this lab, though it is expected that every student in any such group contribute equally to the lab.

Write a program to modify the volume of an audio file.

```
$ ./volume input.wav output.wav 2.0
```

## WAV Files

[WAV files](https://docs.fileformat.com/audio/wav/) are a common file format for representing audio. WAV files store audio as a sequence of "samples": numbers that represent the value of some audio signal at a particular point in time. WAV files begin with a 44-byte "header" that contains information about the file itself, including the size of the file, the number of samples per second, and the size of each sample. After the header, the WAV file contains a sequence of samples, each a single 2-byte (16-bit) integer representing the audio signal at a particular point in time.

Scaling each sample value by a given factor has the effect of changing the volume of the audio. Multiplying each sample value by 2.0, for example, will have the effect of doubling the volume of the origin audio. Multiplying each sample by 0.5, meanwhile, will have the effect of cutting the volume in half.

## Types

So far, we've seen a number of different types in C, including `int`, `bool`, `char`, `double`, `float`, and `long`. Inside a header file called `stdint.h` are the declarations of a number of other types that allow us to very precisely define the size (in bits) and sign (signed or unsigned) of an integer. Two types in particular will be useful to us in this lab.

-   `uint8_t` is a type that stores an 8-bit unsigned (i.e., not negative) integer. We can treat each byte of a WAV file's header as a `uint8_t` value.
-   `int16_t` is a type that stores a 16-bit signed (i.e., positive or negative) integer. We can treat each sample of audio in a WAV file as an `int16_t` value.

## Getting Started

1.  Log into [ide.cs50.io](https://ide.cs50.io/) using your GitHub account.
2.  In your terminal window, run `wget https://cdn.cs50.net/2020/fall/labs/4/lab4.zip` to download a Zip file of the lab distribution code.
3.  In your terminal window, run `unzip lab4.zip` to unzip (i.e., decompress) that Zip file.
4.  In your terminal window, run `cd lab4` to change directories into your `lab4` directory.

## Implementation Details

Complete the implementation of `volume.c`, such that it changes the volume of a sound file by a given factor.

-   The program accepts three command-line arguments: `input` represents the name of the original audio file, `output` represents the name of the new audio file that should be generated, and `factor` is the amount by which the volume of the original audio file should be scaled.
    -   For example, if `factor` is `2.0`, then your program should double the volume of the audio file in `input` and save the newly generated audio file in `output`.
-   Your program should first read the header from the input file and write the header to the output file. Recall that this header is always exactly 44 bytes long.
    -   Note that `volume.c` already defines a variable for you called `HEADER_SIZE`, equal to the number of bytes in the header.
-   Your program should then read the rest of the data from the WAV file, one 16-bit (2-byte) sample at a time. Your program should multiply each sample by the `factor` and write the new sample to the output file.
    -   You may assume that the WAV file will use 16-bit signed values as samples. In practice, WAV files can have varying numbers of bits per sample, but we'll assume 16-bit samples for this lab.
-   Your program, if it uses `malloc`, must not leak any memory.

### Hints

-   You'll likely want to create an array of bytes to store the data from the WAV file header that you'll read from the input file. Using the `uint8_t` type to represent a byte, you can create an array of `n` bytes for your header with syntax like

```
uint8_t header[n];
```

replacing `n` with the number of bytes. You can then use `header` as an argument to `fread` or `fwrite` to read into or write from the header.

-   You'll likely want to create a "buffer" in which to store audio samples that you read from the WAV file. Using the `int16_t` type to store an audio sample, you can create a buffer variable with syntax like

```
int16_t buffer;
```

You can then use `&buffer` as an argument to `fread` or `fwrite` to read into or write from the buffer. (Recall that the `&` operator is used to get the address of the variable.)

-   You may find the documentation for [`fread`](https://man.cs50.io/3/fread) and [`fwrite`](https://man.cs50.io/3/fwrite) helpful here.
    -   In particular, note that both functions accept the following arguments:
        -   `ptr`: a pointer to the location in memory to store data (when reading from a file) or from which to write data (when writing data to a file)
        -   `size`: the number of bytes in an item of data
        -   `nmemb`: the number of items of data (each of `size` bytes) to read or write
        -   `stream`: the file pointer to be read from or written to
    -   Per its documentation, `fread` will return the number of items of data successfully read. You may find this useful to check for when you've reached the end of the file!

### How to Test Your Code

Your program should behave per the examples below.

```
$ ./volume input.wav output.wav 2.0
```

When you listen to `output.wav` (as by control-clicking on `output.wav` in the file browser, choosing Download, and then opening the file in an audio player on your computer), it should be twice as loud as `input.wav`!

```
$ ./volume input.wav output.wav 0.5
```

When you listen to `output.wav`, it should be half as loud as `input.wav`!

Execute the below to evaluate the correctness of your code using `check50`. But be sure to compile and test it yourself as well!

```
check50 cs50/labs/2020/fall/volume
```

Execute the below to evaluate the style of your code using `style50`.

```
style50 volume.c
```

## How to Submit

1.  Download just your `volume.c` file by control-clicking or right-clicking on the file in CS50 IDE's file browser and choosing Download.
2.  Go to CS50's [Gradescope page](https://www.gradescope.com/courses/157004).
3.  Click "Lab 4: Volume".
4.  Drag and drop your `volume.c` file to the area that says "Drag & Drop". Be sure it has the correct filename!
5.  Click "Upload".

You should see a message that says "Lab 4: Volume submitted successfully!"
