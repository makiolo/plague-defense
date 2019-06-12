LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/../../../Classes/entityx/Entity.cc  \
                   $(LOCAL_PATH)/../../../Classes/entityx/Event.cc  \
                   $(LOCAL_PATH)/../../../Classes/entityx/System.cc \
                   $(LOCAL_PATH)/../../../Classes/entityx/help/Pool.cc \
                   $(LOCAL_PATH)/../../../Classes/entityx/help/Timer.cc \
                   $(LOCAL_PATH)/../../../Classes/fast-event-system/clock.cpp \
                   $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
