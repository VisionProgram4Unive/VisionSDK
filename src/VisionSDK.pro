#-------------------------------------------------
#
# Project created by QtCreator 2016-01-04T17:49:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisionSDK
TEMPLATE = app

CONFIG += c++11

#include opencv library
win32 {
    ## Windows common build here
    !contains(QMAKE_TARGET.arch, x86_64) {
        message("windows x86 build")

        ## Windows x86 (32bit) specific build here
        INCLUDEPATH += C:/Users/develop/OpenCV/release/3.1/include
        LIBS += -L"C:\Users\develop\OpenCV\release\3.1\MinGW\x86\mingw\bin"
        #CONFIG(debug, debug|release) {
        #        message("linking debug library")
        #        LIBS += -lopencv_bgsegm310d -lopencv_bioinspired310d \
        #                -lopencv_calib3d310d -lopencv_ccalib310d -lopencv_core310d \
        #                -lopencv_datasets310d -lopencv_dnn310d -lopencv_dpm310d \
        #                -lopencv_face310d -lopencv_features2d310d -lopencv_flann310d \
        #                -lopencv_fuzzy310d -lopencv_highgui310d -lopencv_imgcodecs310d \
        #                -lopencv_imgproc310d -lopencv_line_descriptor310d -lopencv_ml310d \
        #                -lopencv_objdetect310d -lopencv_optflow310d -lopencv_photo310d \
        #                -lopencv_plot310d -lopencv_reg310d -lopencv_rgbd310d \
        #                -lopencv_saliency310d -lopencv_shape310d -lopencv_stereo310d \
        #                -lopencv_stitching310d -lopencv_structured_light310d -lopencv_superres310d \
        #                -lopencv_surface_matching310d -lopencv_text310d -lopencv_tracking310d \
        #                -lopencv_video310d -lopencv_videoio310d \
        #                -lopencv_videostab310d -lopencv_xfeatures2d310d -lopencv_ximgproc310d \
        #                -lopencv_xobjdetect310d -lopencv_xphoto310d
        #} else {
                #message("linking release library")
                LIBS += -lopencv_bgsegm310 -lopencv_bioinspired310 \
                        -lopencv_calib3d310 -lopencv_ccalib310 -lopencv_core310 \
                        -lopencv_datasets310 -lopencv_dnn310 -lopencv_dpm310 \
                        -lopencv_face310 -lopencv_features2d310 -lopencv_flann310 \
                        -lopencv_fuzzy310 -lopencv_highgui310 -lopencv_imgcodecs310 \
                        -lopencv_imgproc310 -lopencv_line_descriptor310 -lopencv_ml310 \
                        -lopencv_objdetect310 -lopencv_optflow310 -lopencv_photo310 \
                        -lopencv_plot310 -lopencv_reg310 -lopencv_rgbd310 \
                        -lopencv_saliency310 -lopencv_shape310 -lopencv_stereo310 \
                        -lopencv_stitching310 -lopencv_structured_light310 -lopencv_superres310 \
                        -lopencv_surface_matching310 -lopencv_text310 -lopencv_tracking310 \
                        -lopencv_video310 -lopencv_videoio310 \
                        -lopencv_videostab310 -lopencv_xfeatures2d310 -lopencv_ximgproc310 \
                        -lopencv_xobjdetect310 -lopencv_xphoto310
        #}
    } else {
        message("windows x86_64 build")

        ## Windows x64 (64bit) specific build here

    }

} else:unix {
        message("linux x86_64 build")
        INCLUDEPATH += /usr/local/include/opencv
        LIBS        += -L/usr/local/lib \
#                   -lopencv_stitching -lopencv_superres -lopencv_videostab \
#                   -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired \
#                   -lopencv_ccalib -lopencv_dnn -lopencv_dpm \
#                   -lopencv_fuzzy -lopencv_line_descriptor -lopencv_optflow \
#                   -lopencv_plot -lopencv_reg -lopencv_saliency \
#                   -lopencv_stereo -lopencv_structured_light -lopencv_rgbd \
#                   -lopencv_surface_matching -lopencv_tracking -lopencv_datasets \
#                   -lopencv_text -lopencv_face -lopencv_xfeatures2d \
#                   -lopencv_shape -lopencv_video -lopencv_ximgproc \
#                   -lopencv_calib3d -lopencv_features2d -lopencv_flann \
#                   -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml \
#                   -lopencv_xphoto -lopencv_highgui -lopencv_videoio \
#                   -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc \
#                   -lopencv_core
                -lopencv_shape -lopencv_stitching -lopencv_objdetect \
                -lopencv_superres -lopencv_videostab -lopencv_calib3d \
                -lopencv_features2d -lopencv_highgui -lopencv_videoio \
                -lopencv_imgcodecs -lopencv_video -lopencv_photo \
                -lopencv_ml -lopencv_imgproc -lopencv_flann \
                -lopencv_core

}

SOURCES += main.cpp\
        mainwindow.cpp \
        util/imagedialog.cpp \
        util/imagelabel.cpp \
        algorithm/bilateralfilter.cpp \
        algorithm/cannyedge.cpp \
        algorithm/contrast.cpp \
        algorithm/gaussianblur.cpp \
        algorithm/histogramcalc.cpp \
        algorithm/histogrameq.cpp \
        algorithm/medianblur.cpp \
        algorithm/normalblur.cpp \
        algorithm/sharpen.cpp \
        algorithm/sobeledge.cpp \
        algorithm/threshold.cpp \
        algorithm/abstructalgorithm.cpp \
        queuethread.cpp \
        algorithm/houghcircle.cpp \
        algorithm/detectcircle.cpp \
        IO/inputthread.cpp \
        IO/resolutiondlg.cpp

HEADERS  += mainwindow.h \
        util/imagedialog.h \
        util/imagelabel.h \
        algorithm/bilateralfilter.h \
        algorithm/cannyedge.h \
        algorithm/contrast.h \
        algorithm/gaussianblur.h \
        algorithm/histogramcalc.h \
        algorithm/histogrameq.h \
        algorithm/medianblur.h \
        algorithm/normalblur.h \
        algorithm/sharpen.h \
        algorithm/sobeledge.h \
        algorithm/threshold.h \
        algorithm/abstructalgorithm.h \
        queuethread.h \
        algorithm/houghcircle.h \
        algorithm/detectcircle.h \
        IO/inputthread.h \
        IO/resolutiondlg.h

FORMS    += mainwindow.ui \
        util/imagedialog.ui \
        algorithm/bilateralfilter.ui \
        algorithm/cannyedge.ui \
        algorithm/contrast.ui \
        algorithm/gaussianblur.ui \
        algorithm/histogramcalc.ui \
        algorithm/histogrameq.ui \
        algorithm/medianblur.ui \
        algorithm/normalblur.ui \
        algorithm/sharpen.ui \
        algorithm/sobeledge.ui \
        algorithm/threshold.ui \
        algorithm/houghcircle.ui \
        algorithm/detectcircle.ui \
        IO/resolutiondlg.ui

win32 {
        SOURCES +=
        HEADERS +=

} else:unix {
        message("include v4l2 dependancy code sources")
        SOURCES += IO/v4l2capture.cpp
        HEADERS += IO/v4l2capture.h
}

debug:	DESTDIR = build-debug
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
