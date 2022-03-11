#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Float64
import math

def talker():
    pub = rospy.Publisher('/my_robot/joint1_position_controller/command', Float64, queue_size=10)
    pub_bit = rospy.Publisher('/my_robot/joint4_position_controller/command', Float64, queue_size=10)
    pub_st80 = rospy.Publisher('/my_robot/joint15_position_controller/command', Float64, queue_size=10)
#50 rpm is about 5.23 rad/sec
    rospy.init_node('rig_talker', anonymous=True) #can give any name; was talker
    rate = rospy.Rate(10) # 10hz
    i = 0
    j=0
    while not rospy.is_shutdown():
        #hello_str = "hello world %s" % rospy.get_time()
        #position = math.pi/2  #in radians 
        #position = 10*abs(math.sin(i)) #this is for bitbouncing
        position = 20*(math.sin(i)) #this is for bitbouncing
        
        if position <-3.5: #
            position_1 = 100*abs(math.sin(i))
            position_2 = -2
        else:
            #position > 0
            position_1 = 0
            position_2 = 0
        rospy.loginfo(position)
        pub.publish(position)
        pub_bit.publish(position_1)
        pub_st80.publish(position_2)
        rate.sleep()
        i +=0.01
        j+=1



if __name__ == '__main__':
    try:
        talker()
        #talker_2()
    except rospy.ROSInterruptException:
        pass

#check upper and lower bounds for joint limits from 
#urdf file
#for RPM, I think you can either change to velocity commands and give constant 
#value, or you can use position control for the revolute joint dont use position contro - 
#it switches the direction 
