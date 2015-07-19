/* 
 * Copyright (c) 2015, Daniel Swann <hs@dswann.co.uk>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the owner nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * For Tools access control (e.g. laser cutter) at Nottingham Hackspace
 */


#include "CNHmqtt_irc.h"
#include "CNHDBAccess.h"

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <curl/curl.h>
#include <libical/ical.h>
#include <libical/icalss.h>

using namespace std;

bool CNHmqtt::debug_mode = false;
bool CNHmqtt::daemonized = false; 



class nh_tools : public CNHmqtt_irc
{
  public:
    struct evtdata 
    {
      string full_name;
      int    duration_min;
      time_t start_time;
      time_t end_time;
    };    
    
    string _tool_topic;
    CNHDBAccess *_db;
    char _errorBuffer[CURL_ERROR_SIZE];
      
      
    nh_tools(int argc, char *argv[]);
    ~nh_tools();

    void process_message(string topic, string message);
    void process_irc_message(irc_msg msg);
    int db_connect();
    void setup();
    
    /* split - taken from Alec Thomas's answer to http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c */
    void split(vector<string> &tokens, const string &text, char sep);
    
    static void *s_cal_thread(void *arg);
    void cal_thread();
    
    static size_t s_curl_write(char *data, size_t size, size_t nmemb, void *p);
    int process_ical_data(string ical_data, evtdata &evt_now, evtdata &evt_nexy);
    

      
  
    
private:
      pthread_t calThread;

      bool init_curl(CURL *&conn, char *url);
      static bool event_by_start_time_sorter(evtdata const& i, evtdata const& j);
};


