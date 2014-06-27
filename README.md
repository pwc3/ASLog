# Overview

This file contains a convenience wrapper for logging to the Apple System Log
facility from Objective-C code.  It provides a series of macros for writing
to the log at various levels. It also provides a single function, `ASLog()`,
which takes a log level, an `NSString` format string, and a sequence of zero
or more arguments that are inserted into the format string if necessary.

Prior to importing this header file, it is possible to define `ASLOG_LEVEL` to
any of the `ASL_LEVEL` constants. This can be used to filter the log messages
to only those at an equal or higher level than `ASLOG_LEVEL`.

The log levels, from highest to lowest, are:

* `ASL_LEVEL_EMERG`
* `ASL_LEVEL_ALERT`
* `ASL_LEVEL_CRIT`
* `ASL_LEVEL_ERR`
* `ASL_LEVEL_WARNING`
* `ASL_LEVEL_NOTICE`
* `ASL_LEVEL_INFO`
* `ASL_LEVEL_DEBUG`

If this file is included in the PCH file, one log level shall be enabled for
the entire application. If this file is included by each file using logging,
it is possible to set the log level on a per-file basis.

To make log messages appear in Xcode's debug output area, the following must
be called (for example, in `main.m`):

    ASLogToStderr();

By default, log messages are prefixed with `__PRETTY_FUNCTION__` which expands
to the class name and method name at the location of the `ASLogXXX()` macro
call. If you define `ASLOG_EXCLUDE_PRETTY_FUNCTION` before importing this
file, log messages will not be prefixed with `__PRETTY_FUNCTION__`.

