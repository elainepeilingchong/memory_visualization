# Memory Visualization
This is a project for the Operating System Module which helps the student to visualize the memory management in operating system.

# Description
This project will perform address translation and use translation-lookaside buffer for faster translation. It will handle the exception (Page fault) when the memory is saved in disk. 

## Pseudo-randomise
The content of the physical memory is generated using ASCII to create a random character using the range 33 - 126 in the ASCII table. The initial value of the memory is NUL,  which is 0 in ASCII table.
<br /> 
The frame number that start to store the content is also randomised. It will continue to store the data until it reached the number of data needed. The function will deduct the number of frames needed to avoid insufficient memory to save all the data.

## Page Table Entry
The page table entry is storing the frame number, persent bit and valid bit.
<br /> 
Frame Number:  The frame number that the page number (index) mapped to.
<br /> 
Present Bit: Indicate what pages are currently present in physical memory or are on disk, and can indicate how to treat these different pages. For example, to load a page from disk if the present bit is 0, means the data is stored ont the disk.
<br /> 
Valid Bit: To check whether the address is valid.

## Exception Handler
Page Fault: Perform swapping (Eg. When the user try to access the memory that save on the disk)
<br /> 
Segmentation Fault: Raise Exception and continue the process (Eg. When the valid bit of the page table entry is 0
<br /> 

Out of Bound: Terminate the process (Eg. When the user enter 0xGGGG)


# Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

## Prerequisites
[VirtualBox](https://www.virtualbox.org/wiki/Downloads) or any other virtual machines.
<br /> 
[Ubuntu 18.04.](https://www.ubuntu.com/download/desktop/thank-you?country=IE&version=18.04.2&architecture=amd64)


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
