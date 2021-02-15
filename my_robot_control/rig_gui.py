#!/usr/bin/env python
from __future__ import print_function   
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image, CompressedImage #Joy 
from std_msgs.msg import String, Float64 #added float64

import cv2
import numpy as np  
import rospy
import sys
import roslib
import tf
import math
import rospy
from geometry_msgs.msg import TwistStamped, WrenchStamped,Twist
from industrial_msgs.msg import RobotStatus
import sys,time
import tf2_ros
from tf import TransformListener
import imutils
#from robotiq_2f_gripper_control.msg import Robotiq2FGripper_robot_output as outputMsg
#from robotiq_2f_gripper_control.msg import Robotiq2FGripper_robot_input as inputMsg
from scipy.spatial.transform import Rotation as Rot
frameset=[]
depth_image=[]

x_color=0
y_color=0
rec_border_topleft = (x_color-20,y_color-20)
rec_border_btmright = (x_color+20,y_color+20)
red = (0,0,255)
green = (0,255,0)
yellow= (0,255,255)
white=(255,255,255)

position = 0  #initialize as global to access in all functions

#class here is a group of functions, can calll it several times in the code 
rospy.Subscriber("/my_robot/joint1_position_controller/command", Float64, dp_line) #calling the subscriber(msg structure)
rospy.Subscriber("/my_robot/camera1/image_raw",Image, cam_1) #function


def dp_line(data):
    #this is where you define what the  data is doing, 
    position = data #position data from the joint1 command

def cam_1(data):
    #I wanna share the info from dp_line to the camera so I can do the overlay
    try:
        #CV converter; don't need this without ros, eg. webcam
        cv_image =CvBridge().imgmsg_to_cv2(data, desired_encoding="passthrough") #this transfers 
        #the img from data that ros packs inisde some msg into a format that CV can use
    except CvBridgeError as e:
            print(e)
    if '/my_robot/joint1_position_controller/command' in dict(rospy.get_published_topics()):
        print("No position command")

     #convert from CV bridge format to numpy can use; this allows us to work with multi dimensional arrays  access 
    np_image = np.array(cv_image, dtype=np.uint8)

#convert from float to string, so you can overlay dynamic data value

    cv2.putText(np_image, str(position), (4,10),cv2.FONT_HERSHEY_SIMPLEX,1,red,2)
    #can adjust the np_image dimension to get the center to switch with (480, 1084)