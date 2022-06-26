#! /bin/sh

# summarize.sh - summarize the descriptions of programs and headers

awk "FNR == 2 {print}; FNR == 3 {nextfile};" ../doc/*
