#! /bin/sh

# summarize.sh - summarize the descriptions of programs and libraries

awk "FNR == 2 {print}; FNR == 3 {nextfile};" ../doc/*
