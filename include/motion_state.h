#ifndef MOTION_STATE_H
#define MOTION_STATE_H
#include "clientNet.h"
#include <unistd.h>
#include <vector>


class  MotionState
{
public:
    //send 1 to request move
    bool set_move_request(int, std::vector<float>&);

    //send 2 to get current pose
    bool get_current_state(int, std::vector<float>&);
	
	//set up connect to robot.
    bool setup_connect(const int,  const char *service_ip);

	//close connection
	void close_connect();
	
private:

    CClientNet cct;
};

#endif
