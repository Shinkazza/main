#include "pubsub/pubsub.h"
#include <ros/ros.h>
#include <std_msgs/Int32.h>

int filter(int lift_des_msg, int lift_msg, int state_1_2, int state_3_4)
{
   lift_des_msg = lift_msg;
   if(lift_msg==-1){      	
       if( ((state_1_2==0)||(state_1_2==2)) && ((state_3_4==0)||(state_3_4==2)) ){	
           lift_des_msg = lift_msg;
       }   	
   }else if(lift_msg==0){
       lift_des_msg = lift_msg;
   }else if(lift_msg==1){
       if( ((state_1_2==0)||(state_1_2==-2)) && ((state_3_4==0)||(state_3_4==-2)) ){
           lift_des_msg = lift_msg;
       }
   }
   return lift_des_msg;
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "pub_sub_node");  
    pub_sub<std_msgs::Int32> lift_des_obj("lift_des","pub",1000);
    pub_sub<std_msgs::Int32> lift_obj("lift","sub",1000);
    pub_sub<std_msgs::Int32> motor_1_2_state_obj("motor_1_2_state","sub",1000);
    pub_sub<std_msgs::Int32> motor_3_4_state_obj("motor_3_4_state","sub",1000);
    ros::Rate loop_rate(100);
    std_msgs::Int32 lift_des_msg;

   while (ros::ok())
   {

        ros::spinOnce();
        lift_des_msg.data = filter(lift_des_msg.data,lift_obj.buffer_.data, 
            motor_1_2_state_obj.buffer_.data, motor_3_4_state_obj.buffer_.data);
        lift_des_obj.publish(lift_des_msg);

        loop_rate.sleep();
        //ROS_INFO("state_1_2 : %d", motor_1_2_state_obj.buffer_.data);
        //ROS_INFO("state_3_4 : %d", motor_3_4_state_obj.buffer_.data);
   }
   return 0;
}

