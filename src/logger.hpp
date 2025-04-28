#pragma once

// #define DISABLE_LOGGER

#include <iostream>
#include <sstream>

template<typename T>
inline void getLogLine(std::stringstream& stream, const T& a) {
    stream << a;
}

template<typename T, typename... Types>
inline void getLogLine(std::stringstream& stream, const T& a, Types... args) {
    stream << a;
    getLogLine(stream, args...);
}

// #define getLogString(...) outputVars(m__VA_ARGS__).c_str()
template<typename... Types>
inline std::string getLogString(Types... args) {
    std::stringstream s;
    getLogLine(s, args...);
    return s.str();
}

#define LOG_TAG "PUZZLE"

#ifdef DISABLE_LOGGER

#define LOGE(...)
#define LOGI(...)
#define LOGD(...)

#else

#ifdef __ANDROID_API__

#include <android/log.h>

#define LOGE(...)                                         \
    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s", \
                        getLogString(__VA_ARGS__).c_str());
#define LOGI(...)                                        \
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "%s", \
                        getLogString(__VA_ARGS__).c_str());
#define LOGD(...)                                         \
    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%s", \
                        getLogString(__VA_ARGS__).c_str());

#else

#ifdef QT_ENV

#include <QtGlobal>

#define LOGE(...) \
    qCritical() << LOG_TAG << "error:" << getLogString(__VA_ARGS__).c_str();
#define LOGI(...) \
    qWarning() << LOG_TAG << "info:" << getLogString(__VA_ARGS__).c_str();
#define LOGD(...) \
    qDebug() << LOG_TAG << "debug:" << getLogString(__VA_ARGS__).c_str();

#else

#define LOGE(...)                                                         \
    std::cout << LOG_TAG << "error:" << getLogString(__VA_ARGS__).c_str() \
              << std::endl;
#define LOGI(...)                                                        \
    std::cout << LOG_TAG << "info:" << getLogString(__VA_ARGS__).c_str() \
              << std::endl;
#define LOGD(...)                                                         \
    std::cout << LOG_TAG << "debug:" << getLogString(__VA_ARGS__).c_str() \
              << std::endl;

#endif
#endif
#endif
