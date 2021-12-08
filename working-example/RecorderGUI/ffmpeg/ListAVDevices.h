
#ifndef AUDIORECORDER_LISTAVDEVICES_H
#define AUDIORECORDER_LISTAVDEVICES_H

#ifdef _WINDOWS
//ref:  https://blog.csdn.net/jhqin/article/details/5929796
#include <windows.h>
#include <vector>
#include <dshow.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

#define MAX_FRIENDLY_NAME_LENGTH	128
#define MAX_MONIKER_NAME_LENGTH		256

HRESULT DS_GetAudioVideoInputDevices(std::vector<std::string> &vectorDevices,std::string deviceType);
std::string DS_GetDefaultAudioDevice();

#endif
#endif //AUDIORECORDER_LISTAVDEVICES_H
