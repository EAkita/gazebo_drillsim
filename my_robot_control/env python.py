#!/usr/bin/env python
from __future__ import print_function   
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image, CompressedImage, Joy
from std_msgs.msg import String
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
from robotiq_2f_gripper_control.msg import Robotiq2FGripper_robot_output as outputMsg
from robotiq_2f_gripper_control.msg import Robotiq2FGripper_robot_input as inputMsg
from scipy.spatial.transform import Rotation as Rot
frameset=[]
depth_image=[]
Kodak_image=np.zeros((1440,1440,3), np.uint8)
Kodak_rear_image=np.zeros((1440,1440,3), np.uint8)
crop_img=np.zeros((587,871,3), np.uint8)
rear_crop_img=np.zeros((587,871,3), np.uint8)
s_img = cv2.imread("/home/nrgadmin/vaultbot-nrg/src/temoto_intuitive_teleoperator/graphical_ui/src/stop_sign.png")
