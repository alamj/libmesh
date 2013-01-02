libMesh-specific configuration options
======================================

For generic installation instructions refer also to the file INSTALL.

Build Process
-------------
   (0) ./bootstrap
       (optional, needed if you will modify the GNU autotools build system)
       
   (1) ./configure --prefix=/path/to/libmesh/install
   
   (2) make
   
   (3) make check
       (optional, runs the example programs and unit tests when possible)
       
   (4) make install


METHODS
-------

libMesh supports the notion of multiple methods - that is, compilation
settings used to build the library.  The major methods supported by
the library are:

    opt: Fully Optimized mode, with little to no error checking. No debugging
         symbols are included in the resulting library.  Agressive optimization
	 flags are used.
    
    dbg: Full debugging mode - all useful compiler warnings are enabled,
         as well as robust internal state checking.
	 
  devel: Use high levels of compiler optimization, but also enable internal
         state checking.  Debugging symbols are included, but the resulting
	 code is not always easy to navigate in a debugger because of
	 compiler optimizations.

    pro: Optimized code path with compiler flags suitable for use with gprof.

  oprof: Optimized code path with compiler flags suitable for use with oprofile.


To select a set of methods, you can pass them to configure in one of two ways:

$ ./configure --with-methods="opt dbg devel"

or

$ ./configure METHODS="devel oprof"

If unspecified, the three METHODS="opt dbg devel" are default.


Multiple Builds with Different Compilers
----------------------------------------

libMesh fully supports out-of-tree builds, and users are encouraged to use this
feature when needed to support multiple compilers. For example, on a system
where multiple compilers are availble and accessible via modules, you can share
the same source tree by creating a subdirectory for each compiler build:

$ export LIBMESH_SRC=/local/libmesh
$ cd $LIBMESH_SRC
$ module load gcc/4.6
$ cd $LIBMESH_SRC && mkdir gcc-4.6 && cd gcc-4.6 && ../configure && make && make install
$ module swap gcc intel/12.1
$ cd $LIBMESH_SRC && mkdir intel-12.1 && cd intel-12.1 && ../configure && make && make install

[![githalytics.com alpha](https://cruel-carlota.pagodabox.com/52c0727babae956821cca66c19c68908 "githalytics.com")](http://githalytics.com/libMesh/libmesh)
