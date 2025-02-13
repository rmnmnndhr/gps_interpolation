# GPS Interpolation Project

## Description

This project is a GPS-related application that interpolates GPS coordinates from the x and y pixel coordinates. The system processes data from input files, performs calculations, and outputs the results in CSV format.

## Features

- Reads input data files for GPS coordinates.
- Performs interpolation using different algorithms.
- Calculates error metrics between actual and interpolated GPS positions.
- Generates output CSV files with the calculated errors and statistics.

## Input File Format
The input file for the reference points (e.g., `all_points.txt`) should be in the following format:

Latitude Longitude X Y

The input file for the validation points (e.g. `points.txt`) should be in the following format:

X Y

Where:
- `Latitude` and `Longitude` are GPS coordinates.
- `X` and `Y` represent the pixel position in the image.

Each line should contain a set of values representing a single reference point.

Example:
54.3354263 10.1574859 2011 40



## Requirements

- CMake version 3.16 or higher.
- C++23 compatible compiler.

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/rmnmnndhr/gps_interpolation
   cd gps
   ```

2. Create a build directory:
    ```
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```
    cmake ..
    ```

4. Build the project:
    ```
    make
    ```

5. Run the executable:
    ```
    ./gps
    ```