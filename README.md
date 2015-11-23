Heavy XLSX processing using Python and C++
=====
Example of handling huge (over a million lines) xlsx data using Python and C++

Table of Contents
-----------------

- [Introduction](#introduction)
- [Dependencies](#dependencies)
- [Acknowledgments](#Acknowledgments)

##Introduction

###Motivation
This is part of a real life project where I needed to handle some pre-processed results of a mechanical testing.
Basically, a machine would spit output in sine wave form with each line representing a point in time. Unfortunatly, these waves would have a propagating phase difference due to information being acquired in different frequencies and ocasionally some noise. 

###What does it do?
For the purpose of these tests, my solution attempts to sync peaks and valleys by applying some crude criteria (number of points, min/max criteria until next peak or valley can be detected...)

###How does it do?
A Python script is used for handling user input trough a (gooey) gui, converting data to csv with xlsx2csv and passing it to a C++ program that does the processing.

##Dependencies
[Python 2.7](https://www.python.org/) (because gooey only works on it!)
recommended way of installing deps is by using [pip](https://pypi.python.org/pypi/pip)
- [Gooey](https://github.com/chriskiehl/Gooey)
- [wxPython](http://www.wxpython.org/download.php)
- [xlsx2csv](https://github.com/dilshod/xlsx2csv) (included)
- [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser) (included)

##Acknowledgments
Performance is all thanks to the awesome work of
-  Ben Strasser at [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser)
-  Dilshod Temirkhodjaev at [xlsx2csv] (https://github.com/dilshod/xlsx2csv)