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


#include <limits.h>
#include "WYPB_Event.hpp"
#include "WYPB_Exception.hpp"


WYPB_Event::WYPB_Event(const std::time_t p_time, const unsigned long p_type, const unsigned long p_subtype, WYPB_Player* const p_parent) noexcept
{
    m_time = p_time;
    m_type = p_type;
    m_subtype = p_subtype;
    m_parent_player = p_parent;
}


void WYPB_Event::get_event_members(s_event_members* const p_event_members) noexcept
{
    p_event_members->time = m_time;
    p_event_members->type = m_type;
    p_event_members->subtype = m_subtype;
    p_event_members->parent = m_parent_player;
}

