# NOPDevicePushNotificationLib
PushNotification send push with event key, uid, event time, channel number, device type, and device name.
PushNotification is created with sender. The senders needs support https protocol.

## Http Sender
The project provides curl sender to test. You also can use customized sender for PushNotification.

## Event Key
| Event |
| ----- |
| kStandaloneMotion|
| kStandaloneHuman |
| kDVRMotion |
| kDVRHuman |

## Usage
```c++
_sender = std::make_shared<nightowl::NOP::CurlSender>();
_pusher = std::make_unique<nightowl::NOP_Push_Notification::PushNotification>(_sender);
auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMotion, kUid, eventTime, kStandaloneDeviceType, kStandaloneName);
```

## Requirements

This library is written in c++ and compiled in c++ 11 or later.

## Build Requirements
* CMake
* C++11-standard-compliant compiler


