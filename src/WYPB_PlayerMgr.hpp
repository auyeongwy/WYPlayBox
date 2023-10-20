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

#ifndef _WYPB_PLAYER_MGR_HPP_
#define _WYPB_PLAYER_MGR_HPP_

#include "WYPB_Player.hpp"
#include "WYPB_EventMgr.hpp"
#include "WYPB_Event.hpp"


class WYPB_Player;
class WYPB_Event;
class WYPB_EventMgr;


/** Implements a manager to organize the list of WYPB_Player objects created in the Playbox.
*/
class WYPB_PlayerMgr
{
public:
    /** Constructor.
    * 
    * \param p_max_size Max number of WYPB_Player objects managed by WYPB_PlayerMgr. Defaults to 1024 if not defined.
    * \throws Integer exception if memory allocation error. See "WYPB_Exception.h" for exception codes.
    */
    WYPB_PlayerMgr(const unsigned long p_max_size=1024);


    /** Destructor. When the destructor is called, all WYPB_Player objects assigned to it will be deallocated. Attempts to access those objects after this will obviously result in errors.
    */
    ~WYPB_PlayerMgr();


    /** Adds a WYPB_Player object to the WYPB_PlayerMgr. The WYPB_Player object MUST BE dynamically assigned as WYPB_PlayerMgr will manage the deallocation of the WYPB_Player object. DO NOT attempt to free the WYPB_Player object outside of WYPB_PlayerMgr.
     * 
     * \param p_player A dynamically assigned WYPB_Player object.
    */
    int add_player(WYPB_Player* const p_player) noexcept;


    /** Removes a WYPB_Player object from WYPB_PlayerMgr and deallocates it.
     * 
     * \param p_player A valid WYPB_Player object to be deallocated. This will become deallocated if the removal and deallocation is successful.
     * \return 0 if successful. Non-zero if the object is not found in this WYPB_PlayerMgr.
    */
    int remove_player(WYPB_Player* const p_player) noexcept;


    /** Sends a WYPB_Event to all the WYPB_Player objects managed by this WYPB_PlayerMgr.
     * \param p_event The WYPB_Event to send to all WYPB_Player objects.
     * \param p_event_mgr The WYPB_EventMgr that will receive and queue new events which may be generated when this event is processed.
    */
    void process_event(WYPB_Event * const p_event, WYPB_EventMgr * const p_event_mgr) noexcept;

private:
    /** Gets the next available index in m_player_list.
    */
    void get_next_index(void);

    /** Max number of WYPB_Player objects managed by this WYPB_PlayerMgr object.
    */
    unsigned long m_max_size;

    /** Current number of WYPB_Player objects managed by this WYPB_PlayerMgr object.
    */
    unsigned long m_current_size;

    /** Next available index in m_player_list. Will be invalid if m_current_size == m_max_size.
    */
    unsigned long m_next;
    
    /** List of WYPB_Player objects managed by this WYPB_PlayerMgr.
    */
    WYPB_Player **m_player_list; 

};


#endif