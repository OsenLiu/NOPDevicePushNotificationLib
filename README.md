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

## Compiler
You can set your own compile with following arguments:
```
cmake -D CMAKE_C_COMPILER=/path/to/gcc/bin/gcc -D CMAKE_CXX_COMPILER=/path/to/gcc/bin/g++ .
```
Or you can set TOOLCHAIN_LIB_PATH and CROSS_COMPILE environment variable. CMake will find compile in following path:
```
$ENV{TOOLCHAIN_LIB_PATH}/../bin/$ENV{CROSS_COMPILE}gcc
$ENV{TOOLCHAIN_LIB_PATH}/../bin/$ENV{CROSS_COMPILE}g++
```

## CURL Library
add INSTALL_LIB_PATH environement variable so that it can link the libraries.

add INCLUDE_PATH environement variable to include the headers of libraries.

## Build Requirements
* CMake
* C++11-standard-compliant compiler


