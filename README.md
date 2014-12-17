# libvex documentation
The documentation is located on this branch (to keep the master branch clean).

## Viewing without Cloning
That's what [this](http://karimsa.github.io/libvex) is for.

## Compiling from Scratch
libvex documentation is generated with Doxygen and hosted by Github Pages.
To compile documentation for your own fork, run `doxygen` (or `make doc`) in the root directory of the master branch.

For example:
```
$ git clone -b master https://github.com/karimsa/libvex.git
.. clones ..
$ cd libvex
$ git submodule update
.. clones documentation branch ..
$ make doc
.. compiles documentation ...
```

After this, updated documentation will be available in `doc/html`.
