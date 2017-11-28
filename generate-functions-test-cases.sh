#!/bin/bash
for i in *-functions-test.m
do
    vim $i +'source mat2m.vim'
done
