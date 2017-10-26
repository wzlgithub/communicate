#include "clientNet.h"
#include "motion_state.h"
#include <vector>
#include <iostream>
#include <unistd.h>


//when request move action_type==1
bool MotionState::set_move_request(int action_type, std::vector<float>& target_pose)
{
	char send_move_req[512];
	memset(send_move_req, 0, sizeof(send_move_req));

	void *pf;
	pf = &action_type;
	for (int i = 0; i < 4; i++)
	{
		*(send_move_req + i) = *((char*)pf + i);
	}
    pf = &target_pose[0];
	for (int i = 4; i < 8; i++)
	{
		*(send_move_req + i) = *((char*)pf + i - 4);
	}
    pf = &target_pose[1];
	for (int i = 8; i < 12; i++)
	{
		*(send_move_req + i) = *((char*)pf + i - 8);
	}
    pf = &target_pose[2];
	for (int i = 12; i < 16; i++)
	{
		*(send_move_req + i) = *((char*)pf + i - 12);
	}
    pf = &target_pose[3];
	for (int i = 16; i < 20; i++)
	{
		*(send_move_req + i) = *((char*)pf + i - 16);
	}
    pf = &target_pose[4];
	for (int i = 20; i < 24; i++)
	{
		*(send_move_req + i) = *((char*)pf + i - 20);
	}
    pf = &target_pose[5];
	for (int i = 24; i < 28; i++)
	{
		*(send_move_req + i) = *((char*)pf + i - 24);
	}
    pf = &target_pose[6];
	for (int i = 28; i < 32; i++)
	{
		*(send_move_req + i) = *((char*)pf + i - 28);
	}
    int send_res=cct.SendMsg(send_move_req, sizeof(send_move_req));

    if(send_res==0)
    {
        char receive_msg[512];
        int move_result;
        int recv_res=cct.ReceiveMsg(receive_msg,sizeof(receive_msg));
        switch (recv_res) {
        case -1:
            std::cout<<"not received feedback signal from robot"<<std::endl;
            return false;
        case 0:
            memcpy(&move_result,receive_msg,4);
            if(move_result==1)
            {
                return true;
            }else{
                std::cout<<"robot can't reach sent pose!"<<std::endl;
                return false;
            }
        case 1:
            std::cout<<"received data is overflow!"<<std::endl;
            return false;
        default:
            break;
        }


    }else{
        std::cout<<"send move request failed!"<<std::endl;
        return false;
    }

    return false;

}


bool MotionState::get_current_state(int action_type, std::vector<float>& current_state)
{
    char send_state_req[4];
    memset(send_state_req, 0, sizeof(send_state_req));

    void *pf;
    pf = &action_type;
    for (int i = 0; i < 4; i++)
    {
        *(send_state_req + i) = *((char*)pf + i);
    }

    int send_result=cct.SendMsg(send_state_req, sizeof(send_state_req));
    if(send_result==0)
    {
        char receive_msg[512];
        int recv_result=cct.ReceiveMsg(receive_msg,sizeof(receive_msg));

        switch (recv_result) {
        case -1:
            std::cout<<"not received feedback signal from robot"<<std::endl;
            return false;
        case 0:
            memcpy(&current_state[0], receive_msg, 4);
            memcpy(&current_state[1], receive_msg + 4, 4);
            memcpy(&current_state[2], receive_msg + 8, 4);
            memcpy(&current_state[3], receive_msg + 12, 4);
            memcpy(&current_state[4], receive_msg + 16, 4);
            memcpy(&current_state[5], receive_msg + 20, 4);
            memcpy(&current_state[6], receive_msg + 24, 4);
            return true;
        case 1:
            std::cout<<"received data is overflow!"<<std::endl;
            return false;
        default:
            break;
        }

    }else{
        std::cout<<"send get current state command failed!"<<std::endl;
        return false;
    }

    return false;
}

bool MotionState::setup_connect(const int receive_port, const char *service_ip)
{

	int connect_num = 0;

	for (connect_num = 1; connect_num <= 10; connect_num++)
	{
        std::cout << "Try " << connect_num << " time to connect server..." << std::endl;
		int connect_result = cct.Connect(receive_port, service_ip);
		//int connect_recult=client.Connect(2700, "127.0.0.1");
		if (connect_result == 0)
		{
            std::cout << "Connected to the: " << service_ip << std::endl;
			break;
        }
		else if (connect_result != 0){
			if (connect_num < 5)
			{
                std::cout << "The " << connect_num << " connection failed!  Wait 0.5 seconds to reconnect..." << std::endl;
                sleep(500);
			}
			else if (connect_num == 5)
			{
                std::cout << "Connection failed!" << std::endl;
				//getchar();
				return false;
			}
		}

	}

	return true;
}

void MotionState::close_connect()
{
	cct.Close();
}
