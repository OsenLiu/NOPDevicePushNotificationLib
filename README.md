# NOPDevicePushNotificationLib
PushNotification send push with event key, uid, event time, channel number, device type, and device name.
PushNotification is created with sender. The senders needs support https protocol.

## Http Sender
The project provides curl sender to test. You also can use customized sender for PushNotification.

## Event Key
| Standalone | DVR |
| --- | --- |
| kStandaloneMotion| kDVRMotion |
| kStandaloneHuman | kDVRHuman |
| kStandaloneMoved | kDVRMoved |
| kStandaloneFaceDetect | kDVRFaceDetect |

## Usage
```c++
_sender = std::make_shared<nightowl::NOP::CurlSender>();
_pusher = std::make_unique<nightowl::NOP_Push_Notification::PushNotification>(_sender);
// The device send push notification message without channel. The message without channel name should call this function. 
auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMotion, kUid, eventTime, kStandaloneDeviceType, kStandaloneName);

// The device send push notification message with channel. The message with channel name should call this function.
auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRFaceDetect, kUid, eventTime, kDVRType, kChannelID, kChannelName);
```

Push notification with image URL
```
_pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman, kUid, eventTime, kDVRType, kChannelID, kChannelName, kImageURL);
```

## Compiler
You can set your own compile with following arguments:
```
cmake -DCMAKE_C_COMPILER=/path/to/gcc/bin/gcc -DCMAKE_CXX_COMPILER=/path/to/gcc/bin/g++ .
```
Hisiv SDK
```
export CROSS=arm-hisiv510-linux
export TARGETMACH=arm-hisiv510-linux
export CROSS_COMPILE="arm-hisiv510-linux"

export AR=${CROSS_COMPILE}-ar
export AS=${CROSS_COMPILE}-as
export LD=${CROSS_COMPILE}-ld
export RANLIB=${CROSS_COMPILE}-ranlib
export CC=${CROSS_COMPILE}-gcc
export CXX=${CROSS_COMPILE}-gcc
export NM=${CROSS_COMPILE}-nm
```


## CURL Library
CURL_LIBRARY_DIR is the curl static library path and CURL_INCLUDE_DIRS is curl header path.

OPENSSL_LIBRARY_DIR is the OpenSSL static library path and OPENSSL_INCLUDE_DIRS is OpenSSL header path.

```
cmake . -Bout -DCURL_LIBRARY_DIR=/root/project/externalLibs -DOPENSSL_LIBRARY_DIR=/root/project/externalLibs -DCURL_INCLUDE_DIRS=/root/project/curl/include -DOPENSSL_INCLUDE_DIRS=/root/project/openssl/include
```
Add CFLAGS CXXFLAGS in the head of command when you failed compiling with m32 or m64
```
CFLAGS= CXXFLAGS= cmake . -Bout -DCURL_LIBRARY_DIR=/root/project/externalLibs -DOPENSSL_LIBRARY_DIR=/root/project/externalLibs -DCURL_INCLUDE_DIRS=/root/project/curl/include -DOPENSSL_INCLUDE_DIRS=/root/project/openssl/include
```  

## Build Requirements
* CMake
* C++11-standard-compliant compiler


