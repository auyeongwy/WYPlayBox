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



#include <cstddef>
#include <exception>
#include <cstring>
#include <iostream>
#include "WYPB_PlayerMgr.hpp"
#include "WYPB_Exception.hpp"


WYPB_PlayerMgr::WYPB_PlayerMgr(const unsigned long p_max_size)
{
    if(p_max_size < 1)
        throw INVALID_PARAMETER; /* Ensure we never deal with invalid entries that require special checks throughout. */
    m_max_size = p_max_size;
    m_current_size = 0;
    m_next = 0;

    try {
        m_player_list = new WYPB_Player* [m_max_size];
    } catch (std::exception &e) { /* Memory allocation error. */
        throw MEMORY_ALLOCATION_ERR;
    }
    memset(m_player_list, 0, sizeof(WYPB_Player*)*m_max_size);
}


WYPB_PlayerMgr::~WYPB_PlayerMgr(void)
{
    unsigned long i = 0;

    while((m_current_size > 0) && (i < m_max_size)) { /* Exit when all members freed or the whole list has been parsed. */ 
        if(m_player_list[i] != NULL) { /* Found a valid member. */
            delete(m_player_list[i]); /* Delete member. */
            --m_current_size; /* Update number of valid members. */
        }
        ++i; /* Move to next member. */
    }
    delete[] m_player_list;
}


int WYPB_PlayerMgr::add_player(WYPB_Player* const p_obj) noexcept
{
    if(m_current_size < m_max_size) {
        m_player_list[m_next] = p_obj;
        ++m_current_size;
        get_next_index();
    }
    else /* Exceed allocated size. */
        return MEMORY_ALLOCATION_ERR;

    return 0;
}


int WYPB_PlayerMgr::remove_player(WYPB_Player* const p_player) noexcept
{
    for(unsigned long i=0; i<m_max_size; i++) {
        if(m_player_list[i] == p_player) {
            delete(m_player_list[i]);
            m_player_list[i] = NULL;
            --m_current_size;
            get_next_index();
            return 0;
        }
    }
    return NOT_FOUND;
}


   
void WYPB_PlayerMgr::process_event(WYPB_Event * const p_event, WYPB_EventMgr * const p_event_mgr) noexcept
{
    unsigned long i = 0;
    unsigned long j = m_current_size;

    while((j > 0) && (i < m_max_size)) { /* Exit when all objects are processed or max objects exceeded. */
        if(m_player_list[i] != NULL) { /* Found a valid member. */
            m_player_list[i]->process_event(p_event, p_event_mgr); /* Object processes the event. */
            --j;
        }
        ++i; /* Move to next member. */
    }
}


void WYPB_PlayerMgr::get_next_index(void)
{
    if(m_current_size < m_max_size) {
        for(unsigned long i=0; i<m_max_size; ++i) {
            if(m_player_list[i] == NULL) {
                m_next = i;
                break;
            }
        }
    }   
}