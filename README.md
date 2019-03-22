# Memory Visualization
This is a project for the Operating System Module which helps the student to visualize the memory management in operating system.

# Description
This project will perform address translation and use translation-lookaside buffer for faster translation. It will handle the exception (Page fault) when the memory is saved in disk. 

## Pseudo-randomise
The content of the physical memory is generated using ASCII to create a random character using the range 33 - 126 in the ASCII table. The initial value of the memory is NUL,  which is 0 in ASCII table.
The frame number that start to store the content is also randomised. It will continue to store the data until it reached the number of data needed. The function will deduct the number of frames needed to avoid insufficient memory to save all the data.

## Page Table Entry
The page table entry is storing the frame number, persent bit and valid bit.
Frame Number:  
Present Bit: Indicate what pages are currently present in physical memory or are on disk, and can indicate how to treat these different pages. For example, to load a page from disk if the present bit is 0, means the data is stored ont the disk.
Valid Bit: To check whether the address is valid.

## Exception Handler
Page Fault: Perform swapping (Eg. When the user try to access the memory that save on the disk)
Segmentation Fault: Raise Exception and continue the process (Eg. When the valid bit of the page table entry is 0)
Out of Bound: Terminate the process (Eg. When the user enter 0xGGGG)


# Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

## Prerequisites
[VirtualBox](https://www.virtualbox.org/wiki/Downloads) or any other virtual machines.
<br /> 
[Ubuntu 18.04.](https://www.ubuntu.com/download/desktop/thank-you?country=IE&version=18.04.2&architecture=amd64)

<!-- 
Give examples
##Installing

A step by step series of examples that tell you how to get a development env running


```bash
make
```
Give the example
And repeat

until finished
End with an example of getting some data out of the system or using it for a little demo

# Running the tests

Explain how to run the automated tests for this system

## Break down into end to end tests

Explain what these tests test and why

Give an example
## And coding style tests

Explain what these tests test and why

Give an example


# Built With

Dropwizard - The web framework used
Maven - Dependency Management
ROME - Used to generate RSS Feeds
Contributing -->


# Deployment
To compile the project, run
```bash
make
```
To start the project, run
```bash
./dist/stimulate
```

# Authors

Elaine Pei Ling Chong


# Acknowledgments

[Mechanism: Address Translation](http://pages.cs.wisc.edu/~remzi/OSTEP/vm-mechanism.pdf)
<br /> 
[Paging: Faster Translations (TLBs)](http://pages.cs.wisc.edu/~remzi/OSTEP/vm-tlbs.pdf)
