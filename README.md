### Setup TK1

#### 1. [Jetson TK1 Development pack 2.0](https://developer.nvidia.com/embedded/jetson-development-pack)
Nvidia Linux4Tegra software packages for TK1/TX1

* OS(Ubuntu 14.04)
* Libraries
 + CUDA toolkit(6.0)
 + OpenCVTegra
 + VisionWorks
 + cuDNN
* Debeloper Tools

[Follow this Documentation to install](http://docs.nvidia.com/jetpack-l4t/2_0/index.html#developertools/mobile/jetpack/jetpack_l4t/2.0/jetpack_l4t_install.htm%3FTocPath%3DJetPack%2520L4T%7C_____3)
*default userid, password is * `ubuntu` 


#### 2. [QT5](http://www.qt.io/)
cross platform GUI frame work,
An official installer download support for common x86 linux, but ARM based TK1/TX1 need a [source compile](http://download.qt.io/official_releases/qt/5.5/5.5.1/single/qt-everywhere-opensource-src-5.5.1.tar.gz)

**command**
> $ cd `download path`
> $ ./configure -release -opensource -confirm-license -nomake tests -nomake examples -qreal float
> $ sudo make -j4 all
> $ sudo make install

* see also
  [CUDA ZONE: QT Anyone?](https://devtalk.nvidia.com/default/topic/752892/jetson-tk1/qt-anyone-/1)
  [QT official documentation: Qt for linux - building from source](http://doc.qt.io/qt-5/linux-building.html)
  


#### 3. QT creator
IDE for QT

* if you can use network
> $ sudo apt-get install qtcreator

* or 
build [qt-creator source again](http://download.qt.io/official_releases/qtcreator/3.6/3.6.0/qt-creator-opensource-src-3.6.0.zip), 
Before building, you need to revise some code. [see this page](https://codereview.qt-project.org/#/c/79728/1)
> $ cd `download path`
> $ mkdir build && cd $_
> $ qmake -r ../qtcreator.pro
> $ make
> $ sudo make install

+ see also
[QT wiki: building QT creator](https://wiki.qt.io/Building_Qt_Creator_from_Git)

#### Others.
if you want to use wireless LAN or other device that's not supported, you will install [**grinch custom kernal**](https://devtalk.nvidia.com/default/topic/906018/jetson-tk1/-customkernel-the-grinch-21-3-4-for-jetson-tk1-developed/)

----

### Build 

1. download attached source and unpack
 > tar -xvzf VisionSDK.tar.gz
 
2. build source, there is 2 options
 * using qt creator ide
  `Open Project` > `Choice` **visionSDK.pro** > `configure project` > `run (Ctrl+R)`
 * command line
  > $ qmake && make 
