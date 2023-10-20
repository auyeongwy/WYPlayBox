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



#include <iostream>
#include <exception>
#include <cstring>
#include "WYPB_Logger.hpp"
#include "WYPB_Exception.hpp"


WYPB_Logger::WYPB_Logger(void) noexcept
{
    m_io = NULL;
    m_max_size = 0;
    m_current_size = 0;
    m_message = NULL;
}


WYPB_Logger::~WYPB_Logger(void)
{
    if(m_message!=NULL)
        delete[] m_message;    
}


int WYPB_Logger::init(WYPB_IO* const p_io, const unsigned long p_max_size) noexcept
{
    try {
        m_message = new char[p_max_size];
        m_message[0] = 0;
        m_io = p_io;
        m_io->init();
    } catch (std::exception &e) {
        return MEMORY_ALLOCATION_ERR;
    }
    m_max_size = p_max_size;
    return 0;
}


int WYPB_Logger::concat(const char* p_message) noexcept
{
    int return_val = NO_ERR;
    const unsigned long len = strlen(p_message);
    unsigned long len_to_write = m_max_size - m_current_size; /* How much space is available to write. m_current_size should always be 1 less than m_max_size to store the terminator. So len_to_write is always > 0. */
    
    if(len < len_to_write) /* Must have space for terminator. */
        len_to_write = len;
    else {
        len_to_write -= 1; /* Not enough space, message will be truncated. */
        return_val = MEMORY_OVERFLOW; 
    }

    strncpy(m_message + m_current_size, p_message, len_to_write);
    m_message[m_current_size += len_to_write] = 0; /* Increment current size and add the null. */

    return return_val;
}


int WYPB_Logger::log(const char* p_message) noexcept
{
    int return_val = NO_ERR;

    unsigned long len = strlen(p_message);
    if(len >= m_max_size) {
        len = m_max_size - 1;
        return_val = MEMORY_OVERFLOW;
    }
    strncpy(m_message, p_message, len);
    m_message[len + 1] = 0;
    log();

    return return_val;
}


void WYPB_Logger::log() noexcept
{
    m_io->write(m_message);
    m_current_size = 0;
    m_message[0] = 0;
}
