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


#include <exception>
#include <cstring>
#include "WYPB_EventMgr.hpp"
#include "WYPB_Exception.hpp"


WYPB_EventMgr::WYPB_EventMgr(const unsigned long p_max_events)
{
    m_max_events = p_max_events; /* Max events. */
    m_num_events[0] = 0; /* Initialise num event in each queue. */
    m_num_events[1] = 0;

    try { /* Allocate each event queue. */
        m_event_queue[0] = new WYPB_Event* [p_max_events];
        m_event_queue[1] = new WYPB_Event* [p_max_events]; 
    } catch (std::exception &e) { /* Memory allocation error. */
        throw MEMORY_ALLOCATION_ERR;
    }

    memset(m_event_queue[0], 0, sizeof(WYPB_Event*)*m_max_events); /* Initialise values in each queue to NULL. */
    memset(m_event_queue[1], 0, sizeof(WYPB_Event*)*m_max_events);

    m_backup_queue = 0; /* Set the backup and current queues. */
    m_current_queue = 1;
}


WYPB_EventMgr::~WYPB_EventMgr(void)
{
    while(m_num_events[0] > 0) { /* Exit when all members freed. */
        delete(m_event_queue[0][--m_num_events[0]]); 
    }
    while(m_num_events[1] > 0) { /* Exit when all members freed. */
        delete(m_event_queue[1][--m_num_events[1]]); 
    }
    delete[] m_event_queue[0];
    delete[] m_event_queue[1];    
}


int WYPB_EventMgr::add_event(WYPB_Event* const p_event) noexcept
{
    const unsigned long i = m_backup_queue; /* The queue to queue events. */
    if(m_num_events[i] < m_max_events) {
        m_event_queue[i][m_num_events[i]++] = p_event;
        return 0;
    } else /* Return error if number of events exceed max allowed. */
        return MEMORY_ALLOCATION_ERR;
}


void WYPB_EventMgr::process_all_events(WYPB_PlayerMgr * const p_player_mgr, WYPB_EventMgr * const p_event_mgr) noexcept
{
    const unsigned long i = m_current_queue; /* The queue to process events. */
    const unsigned long k = m_num_events[i];
    for(unsigned long j=0; j<k; j++) { /* We do FIFO for events. */
        p_player_mgr->process_event(m_event_queue[i][j], p_event_mgr);
        delete(m_event_queue[i][j]); /* The event is freed after it is sent to all relevant players. */
    }
    m_num_events[i] = 0;

    if(++m_current_queue > 1) { /* Current queue processed. It now becomes the backup while the other queue is made current. */
        m_current_queue = 0;
        m_backup_queue = 1;
    } else
        m_backup_queue = 0;
}
