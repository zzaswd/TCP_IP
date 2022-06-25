#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

void *send_msg(void * arg);
void *recv_msg(void *arg);
void error_handling(char *msg);

char name[NAME_SIZE]= "[DEFAULT]";
char msg[BUF_SIZE];

class ROS {
public:
	int sock;
	int argc;
	char** argv;
};



int main(int argc, char *argv[]){
	ROS turtle;
	turtle.argc = argc;
	turtle.argv = argv;

	int sock;
	struct sockaddr_in serv_addr;
	pthread_t snd_thread, rcv_thread;
	void * thread_return;
	if(argc!=4){
		printf("Usage : %s <IP> <port> <name> \n",argv[0]);
		exit(1);
	}
	

	sprintf(name, "[%s]",argv[3]);
	turtle.sock = socket(PF_INET, SOCK_STREAM, 0);
	//sock= socket(PF_INET,SOCK_STREAM,0);

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	
	if(connect(turtle.sock,(struct sockaddr *) &serv_addr, sizeof(serv_addr))== -1)
		error_handling("connect() error");
	//if(connect(sock,(struct sockaddr *) &serv_addr, sizeof(serv_addr))== -1)
	//	error_handling("connect() error");


	pthread_create(&rcv_thread, NULL, recv_msg, (void*)&turtle);
	//pthread_create(&snd_thread,NULL,send_msg,(void *)&sock);
	//pthread_create(&rcv_thread,NULL,recv_msg,(void *)&sock);
	pthread_join(snd_thread,&thread_return);
	pthread_join(rcv_thread,&thread_return);
	close(turtle.sock);
	return 0;
}

void * recv_msg(void *arg){
	ROS* recv = (ROS*)arg;
	int sock = recv->sock;
	//int sock = *((int*)arg);

	ros::init(recv->argc, recv->argv, "joystick");
	ros::NodeHandle n;
	ros::Publisher sensor_pub = n.advertise<std_msgs::String>("Joystick", 1000);
	ros::Rate loop_rate(1);

	char name_msg[NAME_SIZE + BUF_SIZE];
	int str_len;
	while(1){
		memset(name_msg, 0x0, sizeof(name_msg));
		str_len = read(sock,name_msg, NAME_SIZE + BUF_SIZE -1);
		if(str_len == -1)
			return (void*)-1;
		name_msg[str_len] = 0;
		fputs(name_msg, stdout);

		if (ros::ok()) {
			std_msgs::String msg;
			std::stringstream ss1;
			ss1 << name_msg;
			msg.data = ss1.str();
			ROS_INFO("%s", msg.data.c_str());

			sensor_pub.publish(msg);
			ros::spinOnce();
			loop_rate.sleep();
		}

	}
		return NULL;
}


void error_handling(char * msg){
	fputs(msg,stderr);
	fputc('\n',stderr);
	exit(1);
}

	


