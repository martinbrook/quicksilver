# quicksilver

The port generally aims follow upstream chromium checkout procedures. It
means you need to have chromium depot_tools checked out somewhere and
added to your PATH
(https://www.chromium.org/developers/how-tos/install-depot-tools). If
you have that, to get the code it should be enough to run the following
commands:

$ mkdir chromium-qs
$ cd chromium-qs
$ gclient config --name src/qt_port
https://github.com/tworaz/quicksilver.git
$ gclient sync

The checkout may take a while. After it's finished you need to apply
some patches to the chromium source tree:

$ cd src
$ git am qt_port/patches/*

To build the code on desktop it should be enough to run:

$ ./qt_port/configure
$ ninja -C out.qt.x86_64/Debug content_shell quicksilver_shell

To run it just execute:
$ ./out.qt.x86_64/Debug/content_shell --no-sandbox
or
$ ./out.qt.x86_64/Debug/quicksilver_shell

On desktop the code needs at least qt 5.4 to run under X11. For wayland
support you need to upgrade to 5.5, or patches to qtwayland a bit.

Building the code for SailfishOS is a little bit more problematic. First
you need to patch Qt a bit (I'll need some time to cleanup the patches
and push them somewhere), second you need custom Sailfish SDK build
which provides gcc 4.8. Unfortunately the default GCC 4.6 is too old to
compile chromium m44, or even m40. From what stskeeps told me Jolla
plans to move to 4.8 in the near future.
