

#ifndef TRLOG_HPP
#define TRLOG_HPP

#include <sys/types.h>
#include <iostream>
#include <ctime>
#include <cstdint>
#include <iomanip>
#include <pthread.h>


namespace Tr {
namespace Log {

static const char* TimeFormat = "%c %Z";

#ifdef LINUX
static thread_local pid_t TID = gettid();
#else
static uint64_t getTID()
{
    uint64_t tid;
    pthread_threadid_np(NULL, &tid);

    return tid;
}

static thread_local uint64_t TID = getTID();
#endif

}
}

#define TRLOGTIME(STREAM) \
    { \
        std::time_t result = std::time(nullptr); \
        STREAM << std::put_time(std::localtime(&result), Tr::Log::TimeFormat); \
    } \

#define TRERROR \
    TRLOGTIME(std::cerr) \
    std::cerr << " @ " << Tr::Log::TID << " (ERROR) "

#define TRINFO \
    TRLOGTIME(std::cout) \
    std::cout << " @ " << Tr::Log::TID << " (INFO) " \


#endif // TRLOG_HPP
