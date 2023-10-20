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

#include <fstream>
#include <exception>
#include "WYPB_Serialize.hpp"


int WYPB_Serialize::do_save(const unsigned long p_size, const char * const p_data) noexcept
{
    try {
        std::ofstream file("savefile");
        file.write(p_data, p_size);
        file.close();
    } catch (std::exception &e) {
        return IO_ERR;
    }
    return NO_ERR;
}


int WYPB_Serialize::do_load(const unsigned long p_size, char * p_data) noexcept
{
    try {
        std::ifstream file("savefile");
        file.read(p_data, p_size);
        file.close();
    } catch (std::exception &e) {
        return IO_ERR;
    }
    return NO_ERR;
}