/**
 * @file    Manager.h
 * @ingroup LoggerCpp
 * @brief   The static class that manage the registered Channel and Output objects
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include "Log.h"
#include "Channel.h"
#include "Output.h"
#include "Config.h"


namespace Log
{


/**
 * @brief   The static class that manage the registered channels and outputs
 * @ingroup LoggerCpp
 *
 *  The Manager keeps a map of all the named Channel objects
 * and share them on demand by new Logger objects created with the same name.
 *
 * Thus the Manager is able to change the Log::Level of selected Channel object.
 *
 * The Manager also keep a list of all configured Output object to output the Log objects.
 */
struct Manager
{
public:
    /**
     * @brief Create and configure the Output objects.
     *
     * @param[in] aConfigList   List of Config for Output objects
     */
    static void         configure(const Config::Vector& aConfigList);

    /**
     * @brief Destroy the Output objects.
     * 
     * Clear the Output list to release the ownership.
     */
    static void         terminate(void);

    /**
     * @brief Return the Channel corresponding to the provided name
     *
     * Create a new Channel or get the existing one. 
     *
     * @param[in] apChannelName String to identify the underlying Channel of a Logger
     *
     * @return Pointer to the corresponding Channel (never NULL)
     */
    static Channel::Ptr get(const char* apChannelName);

    /**
     * @brief Output the Log to all the active Output objects.
     *
     * Dispatch the Log to OutputConsole/OutputFile/OutputVS/OutputMemory...
     *
     * @param[in] aChannelPtr   The underlying Channel of the Log
     * @param[in] aLog          The Log to output
     */
    static void         output(const Channel::Ptr& aChannelPtr, const Log& aLog);

    /**
     * @brief Set the default output Log::Level of any new Channel
     */
    static inline void setDefaultLevel (Log::Level aLevel) {
        mDefaultLevel = aLevel;
    }

    /**
     * @brief Return the map of shared pointer of Channel objects
     */
    static inline Channel::Map  getChannelMap(void) {
        return mChannelMap;
    }

private:
    static Channel::Map     mChannelMap;    //!< Map of shared pointer of Channel objects
    static Output::Vector   mOutputList;    //!< List of Output objects
    static Log::Level       mDefaultLevel;  //!< Default Log::Level of any new Channel
};


} // namespace Log
