from __future__ import annotations
import ast
import itertools
import functools
import numpy as np
import xml.sax
import queue
from collections.abc import Iterable, Iterator
from abc import ABC, abstractmethod
import socket

#host = '172.31.236.191'
#port = 6666
#s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
#s.connect((host,port))
#s.send(b'{yuchen}')
#print(s.recv(1024))

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
    def __init__(self,subject:str,sender:str,receiver:str,content:str):
        self._subject=subject
        self._sender=sender
        self._receiver=receiver
        self._content=content
        lines = f.readlines()
        for line in lines:
            key,val=line.split(':')
            print(key,val)
            if(key=="subject"):
                self._subject=val
            if(key=="sender"):
                self._sender=val
            if(key=="receiver"):
                self._receiver=val
            if(key=="content"):
                self._content=val
    def accept(self,visitor:Visitor):
        visitor.visit_message(self)

class newsletter:
    def __init__(self,subject:str,content:str):
        self._content=content
        self._subject=subject

#singleton
class staff_info(metaclass=SingletonMeta):
    def __init__(self):
        self.diction={}
        f=open(Staff_path)
        lines = f.readlines()
        for line in lines:
            key,val=line.split(',')
            print(key,val)
            self.diction[key]=val
    def staff_log(self,key,val):
        if(self.diction[key][0:6]==val):
            return 1
        else:
            return 0

class student(Visitor):
    def __init__(self,SID:str,S_NAME:str,state:str) -> None:
        self._SID=SID
        self._Name=S_NAME
        self._status=Status()
        self._mailbox=[]
        self.transition_to(state)

    def transition_to(self,state:str):
        print("Context: Transition to:"+state)
        if(state=="fully"):
            self._status=FullyStatus()
        if(state=="pending"):
            self._status=PendingStatus()
        # print(self._status.getstatus())
    def visit_message(self,element):
        self._mailbox.append(element)

#state pattern
class Status:
    content=""
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
        f=open(Student_path)
        lines = f.readlines()
        for line in lines:
            SID,S_NAME,S_STATUS=line.split(',')
            temp=student(SID,S_NAME,S_STATUS)
            self.diction[SID]=temp
            self.arr.append(temp)
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
    def __init__(self,type:strategy=Strategy_All()):
        self.diction={}
        self.arr=[]
        f=open(Course_path)
        lines = f.readlines()
        for line in lines:
            CID,C_NAME,C_professor,C_type,C_time,C_description,C_com=line.split(',')
            if(C_com[0:1]=="1"):
                temp=composite_course(CID,C_NAME,C_type,C_time,C_professor,C_description,self.diction["00001"],self.diction["00002"])
            else:
                temp=unit_course(CID,C_NAME,C_type,C_time,C_professor,C_description)
            self.diction[CID]=temp
            self.arr.append(temp)
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
    def __init__(self,str:str):
        if(str=="default"):
            self._staff_info=staff_info()
            self._student_list=student_list()
        else:
            self._staff_info=None
            self._student_list=None
    def get_login_info(self):
        m_str="{ask,login_information}"
        s.send(m_str)
        temp_data=s.recv(2048)
        data = temp_data.decode('utf-8')
    def get_staff_mail(self,type:str):
        m_str="{ask,staff_mail"+type+"}"
        s.send(m_str)
        temp_data=s.recv(2048)
        data = temp_data.decode('utf-8')
    def get_student_detail(self,SID):
        m_str="{ask,staff_mail"+type+"}"
        s.send(m_str)
        temp_data=s.recv(2048)
        data = temp_data.decode('utf-8')

    def close_socket(self):
        s.close()


if __name__ == "__main__":
    # The client code.
    # state test
    print("state test-------------")
    context = student("test","test","pending")
    print(context._status.getstatus())
    context.transition_to("fully")
    print(context._status.getstatus())
    context.transition_to("pending")
    print(context._status.getstatus())

    #student_log
    print("student_log test-------------")
    students=student_list()
    print(students.student_log("0001"))
    print(students.student_log("0004"))

    #staff_log
    print("staff_log test-------------")
    staff1=staff_info()
    staff2=staff_info()
    print(staff1.staff_log("Student Union","123456"))

    #singleton test
    print("singleton test-------------")
    print(staff1==staff2)

    #iterator test
    print("iterator test-------------")
    courses=course_list()
    while True:
        try:
            print(next(courses.__iter__())._CID)
        except:
            break

    #strategy test
    print("strategy test-------------")
    courses1=course_list(Strategy_Mandatory())
    while True:
        try:
            print(next(courses1.__iter__())._CID)
        except:
            break
    courses=course_list(Strategy_Optional())
    while True:
        try:
            print(next(courses.__iter__())._CID)
        except:
            break

    #composite test
    print("composite test-------------")
    for item in courses.arr:
        print(item.show_detail())
        if(item.is_composite()):
            print("children")
            for kid in item._children:
                print(kid._CID)

    #decorator&builder test
    print("decorator&builder test-------------")
    builder=staff_Builder()
    builder.produce_part_cs_department()
    builder.produce_part_student_union()
    builder.produce_part_support_office()
    builder.produce_part_admission_office()
    staffs=builder.product()
    print(staffs._student_union._staff._type,staffs._student_union._right)
    print(staffs._admission_office._staff._type,staffs._admission_office._right)
    print(staffs._support_office._staff._type,staffs._support_office._right)
    print(staffs._cs_department._staff._type,staffs._cs_department._right)

    #visitor test
    print("visitor test-------------")
    f=open("data/mail_list.txt")
    lines = f.readlines()
    for line in lines:
        key,val=line.split(':')
        print(key,val)
        if(key[0:7]=="subject"):
            subject=val
        if(key[0:6]=="sender"):
            sender=val
        if(key[0:8]=="receiver"):
            receiver=""
        if(key[0:7]=="content"):
            content=val
    receiver=""
    mail=message(subject,sender,receiver,content)
    mail.accept(context)
    mail.accept(staffs._student_union)
    for item in context._mailbox:
        print(item._subject,item._sender)

    #adapter test
    print("adapter test-------------")
    adaptee=newsletter("adapter test","just a test!")
    mail2=Adapter(adaptee)
    for item in mail2.get_content():
        print(item._subject,item._receiver,item._sender,item._content)

    #template test
    print("template test-------------")
    #Name:str,time:str,location:str,members_list,link
    activ1=Activity("Test1","03.10.02","Kilburn2.25","perofessor Carroll and Yuchen Tang","")
    activ1.show_details()
    activ2=online_Activity("Test2","05.10.02","Kilburn2.81","perofessor Carroll and Yuchen Tang","http://zoom.com")
    activ2.show_details()
