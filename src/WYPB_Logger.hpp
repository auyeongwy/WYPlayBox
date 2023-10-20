/*      
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.  The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.    
*/



#ifndef _WYPB_LOGGER_HPP_
#define _WYPB_LOGGER_HPP_

#include "WYPB_IO.hpp"

/** Implements a convenience logging class to log messages.  
 * This class provides an API to manage buffer sizes and write operations. But the actual IO is implemented by a WYPB_IO object with virtual functions to be overriden where necessary. This allows us to seperate the IO method from logging operations. For example we could be logging to a database, a socket, a file, etc. All to be implemented by the WYPB_IO virtual class depending on requirements instead of squeezing everything into a Logging class.  
 * 
 * E.g. \n
 * WYPB_Logger logger_obj; \n
 * WYPB_IO io_obj; \n
 * try { \n
 *  logger_obj.init(&io_obj); \n
 * } catch (int e) { \n
 *  std::cout << "Caught exception: " << e << "\n"; \n
 * }
 *   
*/
class WYPB_Logger 
{
public:
    /** Constructor. */
    WYPB_Logger(void) noexcept;

    /** Destructor. */
    ~WYPB_Logger(void);

    /** Initialises the object. This is mandatory to use the class.
     * \param p_io The IO object that implements IO. This function will call p_io->init() to perform any necessary initialisations.
     * \param p_max_size Max size of the logging buffer. Defaults to 1024.
     * \return 0. Or non-0 exception code from WYPB_Exception.hpp.
    */
    int init(WYPB_IO* const p_io, const unsigned long p_max_size=1024) noexcept;

    /** Appends additional log message to the existing log buffer. If the message is larger than the log buffer it will be truncated.
     * \param p_message The additional message to append.
     * \return 0. Or non-0 exception code from WYPB_Exception.hpp if the message is larger than the log buffer.
    */
    int concat(const char* p_message) noexcept;

    /** Logs a message directly. Message will be truncated if larger than the log buffer.
     * \param p_message Message to log.
     * \return 0. Or non-0 exception code from WYPB_Exception.hpp if the message is larger than the log buffer.
     * 
    */
    int log(const char* p_message) noexcept;
    
    /** Logs everything in the log buffer. Usually called after a series of concat().
    */
    void log() noexcept;

private:
    WYPB_IO* m_io; /**< Pointer to the IO object that writes the log. Allocation and deallocation must be managed outside this class. */
    unsigned long m_max_size; /**< Max buffer size. */
    unsigned long m_current_size; /**< Current size of the buffer. */
    char* __restrict__ m_message; /**< Message buffer itself. */
}; 


#endif