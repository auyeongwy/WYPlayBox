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
#include <limits.h>
#include <exception>
#include "WYPB_Player.hpp"
#include "WYPB_Exception.hpp"


unsigned long WYPB_Player::m_generate_id=0; /* Initialise the static ID. */


WYPB_Player::WYPB_Player()
{
    if(WYPB_Player::m_generate_id < ULONG_MAX) /* Check ID does not overflow. */
        m_id = ++WYPB_Player::m_generate_id;
    else 
        throw EXCEPTION_ID_OVERFLOW;
}


WYPB_Player::~WYPB_Player()
{

}


unsigned long WYPB_Player::get_id(void) noexcept
{
    return m_id;
}


void WYPB_Player::process_event(const WYPB_Event* const p_event, WYPB_EventMgr * const p_event_mgr) noexcept
{

}


/*WYPB_Event* WYPB_Player::generate_event(void) noexcept
{
    try {
        return new WYPB_Event();
    } catch (std::exception &e) {
        return NULL;
    }
}*/
