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
#include "WYPB_Player.hpp"
#include "WYPB_Event.hpp"
#include "WYPB_EventMgr.hpp"
#include "WYPB_Exception.hpp"
#include "WYPB_PlayerMgr.hpp"
#include "WYPB_Logger.hpp"

int main(int argc, char * argv[])
{
    char char_buf[128];
    static WYPB_Logger logger_obj;
    WYPB_IO io_obj;
    if(logger_obj.init(&io_obj) != 0) {
        std::cout << "Logger memory allocation error. Abort." << "\n";
        return 0;
    }
    

    logger_obj.concat("Starting");
    logger_obj.concat(" application");
    logger_obj.log();
    logger_obj.concat("Test log");
    logger_obj.log();


    try {
        WYPB_PlayerMgr player_mgr_obj;
        WYPB_EventMgr event_mgr_obj;
        WYPB_Player* player_obj1 = new WYPB_Player();
        WYPB_Player* player_obj2 = new WYPB_Player();
        WYPB_Player* player_obj3 = new WYPB_Player();


        player_mgr_obj.add_player(player_obj1);
        player_mgr_obj.add_player(player_obj2);
        player_mgr_obj.add_player(player_obj3);
        player_mgr_obj.remove_player(player_obj2);

        
        event_mgr_obj.add_event(new WYPB_Event());
        event_mgr_obj.add_event(new WYPB_Event());
        event_mgr_obj.add_event(new WYPB_Event());

        event_mgr_obj.process_all_events(&player_mgr_obj, &event_mgr_obj);

        event_mgr_obj.add_event(new WYPB_Event());
        event_mgr_obj.add_event(new WYPB_Event());
        event_mgr_obj.add_event(new WYPB_Event());
        event_mgr_obj.process_all_events(&player_mgr_obj, &event_mgr_obj);

    } catch (int e) {
        snprintf(char_buf, 128, "Exception: %d", e);
        logger_obj.log(char_buf);
    }

    return 0;
}