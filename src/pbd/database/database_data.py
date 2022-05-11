from __future__ import annotations
import ast
import itertools
import functools
import numpy as np
import xml.sax
import queue
from collections.abc import Iterable, Iterator
from abc import ABC, abstractmethod
import re,os
import socket
host = '192.168.31.79'
port = 6666
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.settimeout(3)
s.connect((host,port))

Staff_path="data/CS-staff.txt"
Student_path="data/student_list.txt"
Course_path="data/Course_list.txt"

class SingletonMeta(type):
    _instances = {}
    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            instance = super().__call__(*args, **kwargs)
            cls._instances[cls] = instance
        return cls._instances[cls]

class Visitor(ABC):
    def visit_message(self,element:message)-> None:
        pass

class message:
    def __init__(self,mail_id:int,subject:str,sender:str,receiver:str,content:str):
        self._id=mail_id
        self._subject=subject
        self._sender=sender
        self._receiver=receiver
        self._content=content
    def accept(self,visitor:Visitor):
        visitor.visit_message(self)

class newsletter:
    def __init__(self,subject:str,content:str):
        self._content=content
        self._subject=subject

#singleton
class staff_info(metaclass=SingletonMeta):
    def __init__(self):
        self._diction={}
    def staff_log(self,key,val):
        if(self._diction[key][0:6]==val):
            return 1
        else:
            return 0

class student(Visitor):
    def __init__(self,SID:str,S_NAME:str,state:str) -> None:
        self._SID=SID
        self._Name=S_NAME
        self._status=Status()
        self._mailbox=[]
        self._course_list=[]
        self.transition_to(state)

    def transition_to(self,state:str):
        print("Context: Transition to:"+state)
        if(state[0]=='F'):
            self._status=FullyStatus()
        if(state[0]=='P'):
            self._status=PendingStatus()
        # print(self._status.getstatus())
    def visit_message(self,element):
        self._mailbox.append(element)

#state pattern
class Status:
    def __init__(self):
        self.content=""
    def getstatus(self) -> str:
        return self.content

class FullyStatus(Status):
    def __init__(self):
        self.content="Fully Registered"
    def getstatus(self) -> str:
        return self.content

class PendingStatus(Status):
    def __init__(self):
        self.content="Pending Registered"
    def getstatus(self) -> str:
        return self.content

#singleton
class student_list(metaclass=SingletonMeta):
    def __init__(self):
        self.diction={}
        self.arr=[]
    def student_log(self,str:str):
        if(str in self.diction.keys()):
            return 1
        else:
            return 0

class course:
    def __init__(self,CID:str,Name:str,type:str,time:str,professor:str,description:str):
        self._CID=CID
        self._Name=Name
        self._type=type
        self._time=time
        self._professor=professor
        self._description=description
        self._is_composite=False
    def show_detail(self):
        return  self._CID,self._Name,self._type,self._time,self._professor,self._description,self._is_composite
    def is_composite(self):
        pass

class unit_course(course):
    def is_composite(self):
        return self._is_composite
    def show_detail(self):
        return  self._CID,self._Name,self._type,self._time,self._professor,self._description,self._is_composite
#composite
class composite_course(course):
    def __init__(self,CID:str,Name:str,type:str,time:str,professor:str,description:str,c1:course,c2:course) -> None:
        super().__init__(CID,Name,type,time,professor,description)
        self._is_composite=True
        self._children = [c1,c2]
    def is_composite(self):
        return self._is_composite
    def show_detail(self):
        return  self._CID,self._Name,self._type,self._time,self._professor,self._description,self._is_composite

#iterator
class AlphabeticalOrderIterator(Iterator):
    _position: int = None
    _flag: int = 0

    def __init__(self, collection,strategy: Strategy) -> None:
        self._collection = collection
        self._position = -1
        self._strategy = strategy

    def __next__(self):
        print(self._position)
        value,self._position=self._strategy.next(self._collection ,self._position)
        if(self._position>=len(self._collection)):
            raise StopIteration()
        return value

#Strategy
class Strategy(ABC):
    def next(self,data_list,pos):
        pass

class Strategy_Optional(Strategy):
    def next(self,data_list,pos):
        pos=pos+1
        while(pos<len(data_list) and data_list[pos]._type[0:8]!="Optional"):
            pos=pos+1
        if(pos>=len(data_list)):
            return None,pos
        else:
            return data_list[pos],pos


class Strategy_Mandatory(Strategy):
    def next(self,data_list,pos):
        pos=pos+1
        while(pos<len(data_list) and data_list[pos]._type[0:9]!="Mandatory"):
            pos=pos+1
        if(pos>=len(data_list)):
            return None,pos
        else:
            return data_list[pos],pos

class Strategy_All(Strategy):
    def next(self,data_list,pos):
        pos=pos+1
        if(pos>=len(data_list)):
            return None,pos
        else:
            return data_list[pos],pos

class course_list(Iterable):
    def __init__(self):
        self.diction={}
        self.arr=[]
    def set_iter(type:strategy=Strategy_All()):
        self.iter=AlphabeticalOrderIterator(self.arr,type)
    def __iter__(self) -> AlphabeticalOrderIterator:
        return self.iter

#Template
class Activity:
    def __init__(self,Name:str,time:str,location:str,members_list,link):
        self.set_time(time)
        self._name=Name
        self.set_location(location)
        self.set_members_list(members_list)
        self.set_link(link)
    def set_time(self,time:str):
        self._time=time
    def set_location(self,location:str):
        self._location=location
    def set_members_list(self,members_list):
        self._members_list=members_list
    #hook
    def is_online(self):
        return False
    def set_link(self,link:str):
        if(self.is_online()):
            self._link=link
        else:
            self._link=None
    def show_details(self):
        print(self._name,self._time,self._location,self._members_list,self._link)

class online_Activity(Activity):
    def is_online(self):
        return True

#Adapter
class Adapter(message):
    _newsletter = None
    _messages = []
    def __init__(self,news:newsletter):
        self._newsletter=news
        stu_list=student_list()
        for stu in stu_list.arr:
            self._messages.append(message(self._newsletter._subject,"Student Union",stu._SID,self._newsletter._content))
    def get_content(self):
        return self._messages

class Staff(Visitor):
    def __init__(self,type:str):
        self._type=type
        self._right=[0,0,0]
    def visit_message(self,element):
        self._mailbox.append(element)

#Decorator
class Decorator(Staff):
    _staff = None
    def __init__(self, staff) -> None:
        self._staff = staff
        self._type=staff._type
        self._right=self._staff._right
        self._mailbox=[]
    def decorate(self):
        pass

class mail_Decorator(Decorator):
    def decorate(self):
        self._right[0]=1

class course_Decorator(Decorator):
    def decorate(self):
        self._right[1]=1

class student_Decorator(Decorator):
    def decorate(self):
        self._right[2]=1

class Builder(ABC):
    def product(self) -> None:
        pass
    def produce_part_student_union(self) -> None:
        pass
    def produce_part_support_office(self) -> None:
        pass
    def produce_part_admission_office(self) -> None:
        pass
    def produce_part_cs_department(self) -> None:
        pass

class staff_group():
    def __init__(self) -> None:
        self._support_office=None
        self._student_union=None
        self._admission_office=None
        self._cs_department=None

#Builder
class staff_Builder(Builder):
    def __init__(self) -> None:
        self.reset()
    def reset(self) -> None:
        self._product = staff_group()
    def product(self) -> staff_group:
        product = self._product
        self.reset()
        return product
    def produce_part_student_union(self) -> None:
        temp1=Staff("Student Union")
        self._product._student_union=mail_Decorator(temp1)
        self._product._student_union.decorate()

    def produce_part_support_office(self) -> None:
        temp2=Staff("Support Office")
        self._product._support_office=mail_Decorator(temp2)
        self._product._support_office.decorate()
        self._product._support_office=course_Decorator(self._product._support_office)
        self._product._support_office.decorate()

    def produce_part_admission_office(self) -> None:
        self._product._admission_office=Staff("Admission Office")
        self._product._admission_office=mail_Decorator(self._product._admission_office)
        self._product._admission_office.decorate()
        self._product._admission_office=student_Decorator(self._product._admission_office)
        self._product._admission_office.decorate()

    def produce_part_cs_department(self) -> None:
        self._product._cs_department=Staff("CS & Math Department")
        self._product._cs_department=mail_Decorator(self._product._cs_department)
        self._product._cs_department.decorate()
        self._product._cs_department=student_Decorator(self._product._cs_department)
        self._product._cs_department.decorate()

class database(metaclass=SingletonMeta):
    def __init__(self):
        self._staff_info=staff_info()
        self._student_list=student_list()

    def str_num(str:str):
        return int(str)

    def get_login_info(self,student_id:str,staff_id:str,staff_password:str):
        key=""
        password=""
        #staff
        s.send(b"id=1,get,staff,name")
        data=s.recv(1024)
        key = data.decode('utf-8')
        s.send(b"id=1,get,staff,password")
        data=s.recv(1024)
        password = data.decode('utf-8')
        self._staff_info._diction[key]=password
        s.send(b"id=2,get,staff,name")
        data=s.recv(1024)
        key = data.decode('utf-8')
        s.send(b"id=2,get,staff,password")
        data=s.recv(1024)
        password = data.decode('utf-8')
        self._staff_info._diction[key]=password
        s.send(b"id=3,get,staff,name")
        data=s.recv(1024)
        key = data.decode('utf-8')
        s.send(b"id=3,get,staff,password")
        data=s.recv(1024)
        password = data.decode('utf-8')
        self._staff_info._diction[key]=password
        s.send(b"id=4,get,staff,name")
        data=s.recv(1024)
        key = data.decode('utf-8')
        s.send(b"id=4,get,staff,password")
        data=s.recv(1024)
        password = data.decode('utf-8')
        self._staff_info._diction[key]=password

        if(student_id==""):
            if(self._staff_info._diction[staff_id]==staff_password):
                return True
            else: return False
        else:
            temp_str="id="+student_id+",get,staff,name"
            s.send(b'temp_str)
            data=s.recv(1024)
            if(data==None):
                return False
            else:
                return True

    def get_student_course(self,SID):
        temp_str="id="+SID+",get,staff,enrolledcourseids"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_courses = data.decode('utf-8')
    def get_mail(self,SID):
        temp_str="id="+SID+",get,staff,receivedletterids"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_mails = data.decode('utf-8')
    def get_course_list(self):
        temp_str="get,course,all"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_courses = data.decode('utf-8')

    def send_message(self,subject,receiver,sender,content):
        temp_str="id="+SID+",get,staff,receivedletterids"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_mails = data.decode('utf-8')

    def add_course(self):
        temp_str="id="+SID+",get,staff,receivedletterids"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_mails = data.decode('utf-8')
    def get_message(self):
        temp_str="id="+SID+",get,staff,receivedletterids"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_mails = data.decode('utf-8')
    def add_student_course(self,SID,CID):
        temp_str="id="+SID+",get,staff,receivedletterids"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_mails = data.decode('utf-8')
    def add_activity_student(self):
        temp_str="id="+SID+",get,staff,receivedletterids"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_mails = data.decode('utf-8')
    def add_student(self,s_name,S_STATUS):
        temp_str="Add,staff,"+s_name+","+S_STATUS+",4,female,nopassword"
        s.send(b'temp_str)
    def delete_student(self,SID):
        temp_str="Del,staff,"+s_name+","+S_STATUS+",4,female,nopassword"
        s.send(b'temp_str)
    def delete_course(self):
        temp_str="id="+SID+",get,staff,receivedletterids"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_mails = data.decode('utf-8')
    def delete_student_course(self,SID,CID):
        temp_str="id="+SID+",get,staff,receivedletterids"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_mails = data.decode('utf-8')
    def change_student_status(self):
        temp_str="id="+SID+",get,staff,receivedletterids"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_mails = data.decode('utf-8')
    def change_student_mail_status(self):
        temp_str="id="+SID+",get,staff,receivedletterids"
        s.send(b'temp_str)
        data=s.recv(1024)
        temp_mails = data.decode('utf-8')

if __name__ == "__main__":
    #database Test
    print("database test-------------")
    dataset=database()
    dataset.get_login_info()
    print(dataset._student_list.diction["0002"]._status.getstatus())
    dataset.get_student_course("0001")
    print(dataset._mails[0]._id,dataset._mails[0]._sender)
