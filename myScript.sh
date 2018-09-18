#!/bin/sh
mkdir a1part1
mkdir a1part1/dir1
mkdir a1part1/dir2
touch a1part1/file1
touch a1part1/dir1/dir1file1
touch a1part1/dir2/dir2file1
ln -s dir2/dir2file1 a1part1/link1
ls -l > a1part1/dir1/dir1file1
ls -l > a1part1/dir2/dir2file1
ls -l > a1part1/file1
find . -type f -exec chmod 600 {} \;
chmod 744 a1part1/dir1/*
chmod 755 a1part1/dir2/*
