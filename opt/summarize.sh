#! /bin/sh

# summarize.sh - summarize every program and header

awk "FNR == 2 {print}; FNR == 3 {nextfile};" ../doc/*
