# libvex
A library of helpful code to build faster and more robust VEX robots (using easyC).

# Usage
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