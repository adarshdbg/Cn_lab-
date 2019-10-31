

# Installing ns-3

for ubuntu 18.04 and ns-3 version 3.29  

**first step - update**
```diff
+ sudo apt-get update
```
**second step - install prerequisites**  

    For ns-3:
    1. gcc
    2. g++
    3. python
    4. python-dev

    For NetAnim:
    1. qt4-dev-tools

    For PyViz:
    1. libgtk-3-dev
    2. python-pygoocanvas
    3. python-pygraphviz

    For Wireshark and Gnuplot:
    1. wireshark
    2. gnuplot

    For TraceMetrics:
    1. openjdk-7-jdk (install openjdk-8-jdk if you're using Ubuntu 16.04 or higher)

```diff
- For Ubuntu 18.04, python-pygoocanvas is no longer provided. The ns-3.29 release and later upgrades the support to GTK+ version 3, and requires these packages:
```
```diff
+ sudo apt-get install gir1.2-goocanvas-2.0 python-gi python-gi-cairo python-pygraphviz python3-gi python3-gi-cairo python3-pygraphviz gir1.2-gtk-3.0 ipython ipython3
```

rest of them ->

```diff
+ sudo apt-get install gcc g++ python python-dev qt4-dev-tools libgtk-3-dev python-pygraphviz wireshark gnuplot openjdk-8-jdk**
```

*Wireshark and Gnuplot will be ready to use after this command! TraceMetrics does not require installation.*


Steps to install ns-3.29:

1. Download [ns-allinone-3.29.tar.bz2](https://www.nsnam.org/releases/ns-3-29/) and unzip it.

2. Go to ns-allinone-3.29 folder and give the following command:  
This command will install ns-3, NetAnim and PyViz.

```diff
+ ./build.py --enable-examples --enable-tests
```


3. Once the installation completes, go to ns-allinone-3.29/ns-3.29 and give the following command:

```diff
+ ./test.py -c core
```

If it works correctly then you'll see some files

You are done with it!

Hope it helps.
