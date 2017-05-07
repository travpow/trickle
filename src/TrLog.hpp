

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

#define TRLOG(STREAM, LEVEL) \
    TRLOGTIME(STREAM) \
    STREAM << " @ " << Tr::Log::TID << " ("#LEVEL") " \

#define TRERROR  TRLOG(std::cerr,ERROR)
#define TRINFO   TRLOG(std::cout,INFO)
#define TRWARN   TRLOG(std::cerr,WARN)
#define TRDEBUG  TRLOG(std::cout,DEBUG)

#endif // TRLOG_HPP
