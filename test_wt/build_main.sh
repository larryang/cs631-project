#!/bin/sh

# see https://redmine.webtoolkit.eu/projects/wt/wiki/Installing_Wt_on_Ubuntu#From-the-Sources
g++ -std=c++14 -o main main.cpp -lwthttp -lwt -I/usr/local/include/ -L/usr/local/lib/

# to execute ./main --docroot . --http-address 0.0.0.0 --http-port 9090
#    sent webbrowser to http://localhost:9090/
