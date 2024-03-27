# PointSortAlgorithm
## What it does:
  The Program takes in a file containing coordiantes x and y in that order split into lines.
  Everything extra each line will be disregarded.
  And returned will be those coordiantes normalized an sorted from x = 1 to x = 0 with positive y-values and then x = 0 to x = 1 with negative y-values.

## How it works:
  1. Select the file input (does not matter which file extension, as long as it is utf-8 encoded text)
  2. Press the calculate Button
  3. Select a file in which the output data will be stored
  4. Press the Save Button

## Limitations
  * The program uses boost::multiprecision::cpp_dec_float_100 as datatype for the input values and will be precise for 8 floating points
