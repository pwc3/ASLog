/*
 * Copyright (c) 2014, Anodized Software, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This file contains a convenience wrapper for logging to the Apple System Log
 * facility from Objective-C code.  It provides a series of macros for writing
 * to the log at various levels. It also provides a single function, ASLog(),
 * which takes a log level, an NSString format string, and a sequence of zero
 * or more arguments that are inserted into the format string if necessary.
 *
 * Prior to importing this header file, it is possible to define ASLOG_LEVEL to
 * any of the ASL_LEVEL constants. This can be used to filter the log messages
 * to only those at an equal or higher level than ASLOG_LEVEL.
 *
 * The log levels, from highest to lowest, are:
 *
 *    ASL_LEVEL_EMERG
 *    ASL_LEVEL_ALERT
 *    ASL_LEVEL_CRIT
 *    ASL_LEVEL_ERR
 *    ASL_LEVEL_WARNING
 *    ASL_LEVEL_NOTICE
 *    ASL_LEVEL_INFO
 *    ASL_LEVEL_DEBUG
 *
 * If this file is included in the PCH file, one log level shall be enabled for
 * the entire application. If this file is included by each file using logging,
 * it is possible to set the log level on a per-file basis.
 *
 * To make log messages appear in Xcode's debug output area, the following must
 * be called (for example, in main.m):
 *
 *    ASLogToStderr();
 *
 * By default, log messages are prefixed with __PRETTY_FUNCTION__ which expands
 * to the class name and method name at the location of the ASLogXXX() macro
 * call. If you define ASLOG_EXCLUDE_PRETTY_FUNCTION before importing this
 * file, log messages will not be prefixed with __PRETTY_FUNCTION__.
 */

#ifndef __AS_LOG_H__
#define __AS_LOG_H__

#include <asl.h>

/**
 * Prints a log message at the specified level. Note, calling this function
 * directly will always result in a log message being printed. To allow for
 * filtering, call one of the ASLogXXX() macros instead.
 */
void ASLog(int level, NSString *format, ...);

/**
 * Call this function to make log messages appear in Xcode's debug output area.
 */
void ASLogToStderr(void);

/**
 * If ASLOG_ALL defined, show all log messages.
 */
#ifdef ASLOG_ALL
#define ASLOG_LEVEL ASL_LEVEL_DEBUG
#endif

/**
 * The default log level is ASL_LEVEL_WARNING unless otherwise set before
 * including/importing this file.
 */
#ifndef ASLOG_LEVEL
#define ASLOG_LEVEL ASL_LEVEL_WARNING
#endif

#ifdef ASLOG_EXCLUDE_PRETTY_FUNCTION
  #define ASLogEmergency(...)      if (ASLOG_LEVEL >= ASL_LEVEL_EMERG)   { ASLog(ASL_LEVEL_EMERG,   ##__VA_ARGS__); }
  #define ASLogAlert(...)          if (ASLOG_LEVEL >= ASL_LEVEL_ALERT)   { ASLog(ASL_LEVEL_ALERT,   ##__VA_ARGS__); }
  #define ASLogCritical(...)       if (ASLOG_LEVEL >= ASL_LEVEL_CRIT)    { ASLog(ASL_LEVEL_CRIT,    ##__VA_ARGS__); }
  #define ASLogError(...)          if (ASLOG_LEVEL >= ASL_LEVEL_ERR)     { ASLog(ASL_LEVEL_ERR,     ##__VA_ARGS__); }
  #define ASLogWarning(...)        if (ASLOG_LEVEL >= ASL_LEVEL_WARNING) { ASLog(ASL_LEVEL_WARNING, ##__VA_ARGS__); }
  #define ASLogNotice(...)         if (ASLOG_LEVEL >= ASL_LEVEL_NOTICE)  { ASLog(ASL_LEVEL_NOTICE,  ##__VA_ARGS__); }
  #define ASLogInfo(...)           if (ASLOG_LEVEL >= ASL_LEVEL_INFO)    { ASLog(ASL_LEVEL_INFO,    ##__VA_ARGS__); }
  #define ASLogDebug(...)          if (ASLOG_LEVEL >= ASL_LEVEL_DEBUG)   { ASLog(ASL_LEVEL_DEBUG,   ##__VA_ARGS__); }
#else
  #define ASLogEmergency(fmt, ...) if (ASLOG_LEVEL >= ASL_LEVEL_EMERG)   { ASLog(ASL_LEVEL_EMERG,   @"%s " fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__); }
  #define ASLogAlert(fmt, ...)     if (ASLOG_LEVEL >= ASL_LEVEL_ALERT)   { ASLog(ASL_LEVEL_ALERT,   @"%s " fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__); }
  #define ASLogCritical(fmt, ...)  if (ASLOG_LEVEL >= ASL_LEVEL_CRIT)    { ASLog(ASL_LEVEL_CRIT,    @"%s " fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__); }
  #define ASLogError(fmt, ...)     if (ASLOG_LEVEL >= ASL_LEVEL_ERR)     { ASLog(ASL_LEVEL_ERR,     @"%s " fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__); }
  #define ASLogWarning(fmt, ...)   if (ASLOG_LEVEL >= ASL_LEVEL_WARNING) { ASLog(ASL_LEVEL_WARNING, @"%s " fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__); }
  #define ASLogNotice(fmt, ...)    if (ASLOG_LEVEL >= ASL_LEVEL_NOTICE)  { ASLog(ASL_LEVEL_NOTICE,  @"%s " fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__); }
  #define ASLogInfo(fmt, ...)      if (ASLOG_LEVEL >= ASL_LEVEL_INFO)    { ASLog(ASL_LEVEL_INFO,    @"%s " fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__); }
  #define ASLogDebug(fmt, ...)     if (ASLOG_LEVEL >= ASL_LEVEL_DEBUG)   { ASLog(ASL_LEVEL_DEBUG,   @"%s " fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__); }
#endif

#endif

