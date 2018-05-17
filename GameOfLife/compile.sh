#!/bin/bash

g++ ./GameOfLife.cpp -o life `pkg-config --static --libs glfw3` `pkg-config --static --libs gl`
