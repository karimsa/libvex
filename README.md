# libvex [![Build Status](http://img.shields.io/travis/karimsa/libvex.svg?style=flat)](https://travis-ci.org/karimsa/libvex)

latest version: 0.0.2

A library of helpful code to build faster and more robust VEX robots (using easyC).

## Reference (Documentation)
The latest documentation can be found online [here](http://karimsa.github.io/libvex) ([(ugly) source code](http://github.com/karimsa/libvex/tree/gh-pages)).

## Usage
libvex comes prebuilt on the repository, but if you make any changes to the source, remember to build it using the batch file provided:

```
C:\> make.bat
*does stuff and builds stuff*
```

Once you have compiled sources (`libvex.h` and `libvex.c`), go into easyC, right-click the 'Header Files' in the 'Project Explorer', and choose 'Add Existing Item':

![](https://raw.githubusercontent.com/karimsa/libvex/images/IMG-0.png)

Browse over to the file `libvex.h` and click 'Add'. Now that the header has been added, you need to add the source file. To do this, simply repeat the steps using 'Source Files' and `libvex.c`:

![](https://raw.githubusercontent.com/karimsa/libvex/images/IMG-1.png)

Once the code has been added, it's time to properly include the header to be able to make use of the code. Double-click 'UserInclude.h' under the 'Header Files' section (in the 'Project Explorer'), and add the include:

![](https://raw.githubusercontent.com/karimsa/libvex/images/IMG-2.png)

And voila! Now the libvex helper functions should be available for use to your code.

## Updating
The latest code will always be available in the master branch of this repository, so to update, simply run:

```
C:\> make.bat update
*downloads latest code via git*
```

And then simply re-import the new code files in easyC.
