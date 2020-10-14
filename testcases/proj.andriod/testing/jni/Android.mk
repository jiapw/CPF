LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := shared_testing
LOCAL_SRC_FILES :=	\
../../../../core/rt/xml_xhtml.cpp \
../../../../core/os/kernel.cpp \
../../../../core/os/file_zip.cpp \
../../../../core/os/file_dir.cpp \
../../../../core/os/multi_thread.cpp \
../../../../core/inet/inet.cpp \
../../../../core/inet/tinyhttpd.cpp \
../../../../core/inet/tinyhttpd_fileserv.cpp \
../../../../core/ext/botan/botan.cpp \
../../../../core/ext/lib_inc.c \
../../../../testcases/tests/entrypoint.cpp \
../../../../testcases/tests/test_api.cpp \
../../../../testcases/tests/test_http.cpp \
../../../../testcases/tests/test_botan.cpp \
test.c \

LOCAL_LDLIBS    := -lm -llog
LOCAL_CPP_FEATURES += exceptions 
LOCAL_CPP_FEATURES += rtti

LOCAL_CPPFLAGS += -std=gnu++14


APP_OPTIM := debug
LOCAL_CFLAGS := -D_DEBUG
LOCAL_CFLAGS += -D_GLIBCXX_PERMIT_BACKWARD_HASH
LOCAL_CFLAGS += -DPLATFORM_ANDROID



include $(BUILD_SHARED_LIBRARY)


