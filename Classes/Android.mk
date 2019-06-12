LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := plague

LOCAL_MODULE_FILENAME := libplague

LOCAL_SRC_FILES := \
AppDelegate.cpp \
HelloWorldScene.cpp
entityx/Entity.cc  \
entityx/Event.cc  \
entityx/System.cc \
entityx/help/Pool.cc \
entityx/help/Timer.cc \
fast-event-system/clock.cpp \


LOCAL_C_INCLUDES := $(LOCAL_PATH)

include $(BUILD_STATIC_LIBRARY)
