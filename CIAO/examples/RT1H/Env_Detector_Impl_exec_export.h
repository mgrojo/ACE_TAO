// -*- C++ -*-
// $Id$

// Definition for Win32 Export directives
// ---------------------------------------------

#ifndef _ENV_DETECTOR_IMPL_EXEC_EXPORT_H_
#define _ENV_DETECTOR_IMPL_EXEC_EXPORT_H_

#include "ace/config-all.h"

#if !defined (ENV_DETECTOR_IMPL_EXEC_HAS_DLL)
#  define ENV_DETECTOR_IMPL_EXEC_HAS_DLL 1
#endif /* !ENV_DETECTOR_IMPL_EXEC_HAS_DLL */

#if defined (ENV_DETECTOR_IMPL_EXEC_HAS_DLL) && (ENV_DETECTOR_IMPL_EXEC_HAS_DLL == 1)
#  if defined (ENV_DETECTOR_IMPL_EXEC_BUILD_DLL)
#    define ENV_DETECTOR_IMPL_EXEC_Export ACE_Proper_Export_Flag
#    define ENV_DETECTOR_IMPL_EXEC_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define ENV_DETECTOR_IMPL_EXEC_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else  /* ENV_DETECTOR_IMPL_EXEC_BUILD_DLL */
#    define ENV_DETECTOR_IMPL_EXEC_Export ACE_Proper_Import_Flag
#    define ENV_DETECTOR_IMPL_EXEC_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define ENV_DETECTOR_IMPL_EXEC_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* ENV_DETECTOR_IMPL_EXEC_BUILD_DLL */
#else  /* ENV_DETECTOR_IMPL_EXEC_HAS_DLL == 1 */
#  define ENV_DETECTOR_IMPL_EXEC_Export
#  define ENV_DETECTOR_IMPL_EXEC_SINGLETON_DECLARATION(T)
#  define ENV_DETECTOR_IMPL_EXEC_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* ENV_DETECTOR_IMPL_EXEC_HAS_DLL == 1 */

// Set ENV_DETECTOR_IMPL_EXEC_NTRACE = 0 to turn on library specific 
// tracing even if tracing is turned off for ACE.

#if !defined (ENV_DETECTOR_IMPL_EXEC_NTRACE)
#  if (ACE_NTRACE == 1)
#    define ENV_DETECTOR_IMPL_EXEC_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define ENV_DETECTOR_IMPL_EXEC_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !ENV_DETECTOR_IMPL_EXEC_NTRACE */

#if (ENV_DETECTOR_IMPL_EXEC_NTRACE == 1)
#  define ENV_DETECTOR_IMPL_EXEC_TRACE(X)
#else /* (ENV_DETECTOR_IMPL_EXEC_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define ENV_DETECTOR_IMPL_EXEC_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (ENV_DETECTOR_IMPL_EXEC_NTRACE == 1) */

#endif /* ENV_DETECTOR_IMPL_EXEC_EXPORT_H_ */
