#!/bin/sh

# see https://redmine.webtoolkit.eu/projects/wt/wiki/Installing_Wt_on_Ubuntu#From-the-Sources
g++ -std=c++14 -o main main.cpp -lwthttp -lwt -I/usr/local/include/ -L/usr/local/lib/
