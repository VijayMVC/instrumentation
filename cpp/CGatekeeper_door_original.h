#include <string>
#include <time.h>
#include <string.h>
#include <list>

#include "CLogging.h"
#include "CNHDBAccess.h"
#include "nh-cbi.h"
#include "CGatekeeper_door.h"

class CGatekeeper_door_original : public CGatekeeper_door
{
  public:
    CGatekeeper_door_original();
    ~CGatekeeper_door_original();
  //  std::string door_short_name;
    void set_opts(int id, std::string base_topic, CLogging *log, CNHDBAccess *db, InstCBI *cb, std::string entry_announce, int read_timeout, std::string door_state, std::string exit_message);
    void process_door_event(std::string type, std::string payload);

  private:
    struct door_bell
    {
      std::string mqtt_topic;
      std::string mqtt_message;
    };

    void dbg(std::string msg);

    std::list<door_bell> _door_bells;
    int _id;
    std::string _base_topic;
    std::string _handle;
    std::string _last_seen;
    std::string _entry_announce;
    time_t _last_valid_read;
    int _read_timeout;

    CLogging *_log;
    CNHDBAccess *_db;
    InstCBI *_cb;
};

