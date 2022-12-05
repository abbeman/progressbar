cmake_minimum_required(VERSION 3.1...3.25)

project(
  ProgressBar
  VERSION 0.1
  LANGUAGES CXX)

set (SOURCES 
  progressbar.cc 
  )

add_executable(progressbar ${SOURCES})
