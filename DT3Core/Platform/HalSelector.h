#pragma once
#include "DT3Core/Types/Base/BaseClass.hpp"

#if DT3_OS == DT3_IOS || DT3_OS == DT3_MACOSX
#include "DT3Apple/HAL.hpp"
#elif DT3_OS == DT3_ANDROID
#include "DT3Android/HAL.hpp"
#elif DT3_OS == DT3_WINDOWS
#include "DT3Windows8/HAL.hpp"
#elif DT3_OS == DT3_LINUX
#include "DT3Linux/HAL.hpp"
#endif
