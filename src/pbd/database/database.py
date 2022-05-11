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

#Adapter
class Adapter(message):
    _newsletter = None
    _messages = []
    def __init__(self,mid,news:newsletter):
        self._newsletter=news
        self._messages=message(mid,news._subject,"Student Union","",news._content)
    def get_content(self):
        return self._messages


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
    def student_log(self,SID:str):
        if(SID in self.diction.keys()):
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
        #print(self._position)
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
        while(pos<len(data_list) and (data_list[pos]==None or data_list[pos]._type[0:8]!="Optional")):
            pos=pos+1
        if(pos>=len(data_list)):
            return None,pos
        else:
            return data_list[pos],pos


class Strategy_Mandatory(Strategy):
    def next(self,data_list,pos):
        pos=pos+1
        while(pos<len(data_list) and (data_list[pos]==None or data_list[pos]._type[0:9]!="Mandatory")):
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
    def set_iter(self,type:strategy=Strategy_All()):
        self.iter=AlphabeticalOrderIterator(self.arr,type)
    def __iter__(self) -> AlphabeticalOrderIterator:
        return self.iter

#Template
class Activity:
    def __init__(self,AID,Name:str,time:str,location:str,members_list,link):
        self.set_time(time)
        self._id=AID
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
        self._current=None
        self._current_id=None
        self._student_list=None
        self._course_list=None
        self._staff_info=staff_info()
        self._mails=[]
        self._activities=[]
        self._mail_num=0
        self._course_num=0
        self._activity_num=0
        self._student_num=0

        #3 2d-array
        self._student_course=[[0]*100 for i in range(100)]
        self._student_mail=[[0]*100 for i in range(100)]
        self._student_activity=[[0]*100 for i in range(100)]
        self._staff_mail=[[0]*100 for i in range(100)]

        builder=staff_Builder()
        builder.produce_part_cs_department()
        builder.produce_part_student_union()
        builder.produce_part_support_office()
        builder.produce_part_admission_office()
        self.staffs=builder.product()

        f1=open(Staff_path)
        lines = f1.readlines()
        for line in lines:
            key,val=line.split(',')
            print(key,val)
            self._staff_info._diction[key]=val
        f1.close()

        self._student_list=student_list()
        f2=open(Student_path)
        lines = f2.readlines()
        for line in lines:
            SID,S_NAME,S_STATUS=line.split(',')
            temp=student(SID,S_NAME,S_STATUS)
            self._student_num+=1
            self._student_list.diction[SID[0:4]]=temp
            self._student_list.arr.append(temp)
        f2.close()

        f3=open("data/mail_list.txt")
        lines = f3.readlines()
        flag=0
        for line in lines:
            if(flag%4==0):
                MID=line[4:-1]
            if(flag%4==1):
                subject=line[8:-1]
            if(flag%4==2):
                sender=line[7:-1]
            if(flag%4==3):
                content=line[8:-1]
                print(MID,subject,sender,"",content)
                temp=message(int(MID),subject,sender,"",content)
                self._mails.append(temp)
                self._mail_num+=1
            flag=flag+1
        f3.close()

        f4=open("data/activity_list.txt")
        lines = f4.readlines()
        for line in lines:
            AID,A_NAME,A_TIME,A_LOCATION,A_LINK,A_MEMBERS=line.split(',')
            if(A_LINK!=""):
                temp=online_Activity(AID,A_NAME,A_TIME,A_LOCATION,A_MEMBERS,A_LINK)
            else:
                temp=Activity(AID,A_NAME,A_TIME,A_LOCATION,A_MEMBERS,A_LINK)
            temp.show_details()
            self._activities.append(temp)
            self._activity_num+=1
        f4.close()

        self._course_list=course_list()
        f5=open(Course_path)
        lines = f5.readlines()
        for line in lines:
            CID,C_NAME,C_professor,C_type,C_time,C_description,C_com=line.split(',')
            print(CID,C_NAME,C_professor,C_type,C_time,C_description,C_com)
            if(C_com[0:1]=="1"):
                print(C_com[2:7],C_com[8:13])
                temp=composite_course(CID,C_NAME,C_type,C_time,C_professor,C_description,self._course_list.diction[C_com[2:7]],self._course_list.diction[C_com[8:13]])
            else:
                temp=unit_course(CID,C_NAME,C_type,C_time,C_professor,C_description)
            self._course_num+=1
            self._course_list.diction[CID]=temp
            self._course_list.arr.append(temp)
            print(temp.show_detail())

        print("student_mail")
        f6=open("data/student_mail.txt")
        lines = f6.readlines()
        for line in lines:
                student_id=line[0:4]
                mails=line[5:-1].split(',')
                for item in mails:
                    print(int(student_id),int(item))
                    self._student_mail[int(student_id)][int(item)]=1
        f6.close()

        print("student_course")
        f7=open("data/student_course.txt")
        lines = f7.readlines()
        for line in lines:
                student_id=line[0:4]
                courses=line[5:-1].split(',')
                for item in courses:
                    print(int(student_id),int(item))
                    self._student_course[int(student_id)][int(item)]=1
        f7.close()

        print("student_activity")
        f8=open("data/student_activity.txt")
        lines = f8.readlines()
        for line in lines:
                student_id=line[0:4]
                acivities=line[5:-1].split(',')
                for item in acivities:
                    print(int(student_id),int(item))
                    self._student_activity[int(student_id)][int(item)]=1
        f8.close()

        print("staff_mail")
        f9=open("data/staff_mail.txt")
        lines = f9.readlines()
        for line in lines:
            mails=[]
            print(line[0:2])
            if(line[0:2]=="St"):
                key=1
                mails=line[14:-1].split(',')
            if(line[0:2]=="Su"):
                key=2
                mails=line[15:-1].split(',')
            if(line[0:2]=="Ad"):
                key=3
                mails=line[17:-1].split(',')
            if(line[0:2]=="CS"):
                key=4
                mails=line[21:-1].split(',')
            for item in mails:
                if(item==''): break
                print(key,int(item))
                self._staff_mail[key][int(item)]=1
        f9.close()

    def get_login_info(self):
        self._current=None
        self._current_id=None

    def get_student_course(self,SID):
        stu_course=[]
        for i in range(0,self._course_num+1):
            print(i)
            if(self._student_course[int(SID)][i]==1):
                print("*****",i)
                stu_course.append(self._course_list.arr[i-1])
        return stu_course

    def get_stu_mail(self,SID):
        stu=self._student_list.diction[SID]
        stu._mailbox=[]
        for i in range(0,self._mail_num+1):
            if(self._student_mail[int(SID)][i]==1):
                self._mails[i-1].accept(stu)
        return  stu._mailbox

    def get_staff_mail(self,s_type:str):
        staff_mails=[]
        if(s_type[0:2]=="St" and self.staffs._student_union._right[0]==1):
            key=1
        if(s_type[0:2]=="Su" and self.staffs._support_office._right[0]==1):
            key=2
        if(s_type[0:2]=="Ad" and self.staffs._admission_office._right[0]==1):
            key=3
        if(s_type[0:2]=="CS" and self.staffs._cs_department._right[0]==1):
            key=4
        for i in range(0,self._mail_num+1):
            if(self._staff_mail[key][i]==1):
                print(key,i)
                staff_mails.append(self._mails[i-1])
        return  staff_mails

    def send_message(self,subject,receiver,sender,content):
        self._mail_num+=1
        temp=message(self.get_id(self._mail_num),subject,sender,receiver,content)
        self._mails.append(temp)

        print(receiver,sender)
        if(receiver[0]<='9' and receiver[0]>='0'):
            self._student_mail[int(receiver)][self._mail_num]=1
        else:
            if(receiver[0:2]=="St"):
                key=1
            if(receiver[0:2]=="Su"):
                key=2
            if(receiver[0:2]=="Ad"):
                key=3
            if(receiver[0:2]=="CS"):
                key=4
            print(key)
            self._staff_mail[key][self._mail_num]=1

    def send_newsletter(self,subject,content):
        adaptee=newsletter(subject,content)
        self._mail_num+=1
        mail2=Adapter(self.get_id(self._mail_num),adaptee).get_content()
        self._mails.append(mail2)
        for item in self._student_list.arr:
            if(item._status.getstatus()[0]=='F'):
                self._student_mail[int(item._SID)][self._mail_num]=1

    def add_unit_course(self,C_NAME,C_type,C_time,C_professor,C_description):
        print("unit",C_NAME,C_type,C_time,C_professor,C_description)
        self._course_num+=1
        CID=self.get_course_id(self._course_num)
        temp=unit_course(CID,C_NAME,C_type,C_time,C_professor,C_description)
        self._course_list.arr.append(temp)
        self._course_list.diction[CID]=temp

    def add_composite_course(self,C_NAME,C_type,sub1,sub2):
        print("composite",C_NAME,C_type,sub1,sub2)
        self._course_num+=1
        CID=self.get_course_id(self._course_num)
        C_time=self._course_list.diction[sub1]._time+"+"+self._course_list.diction[sub2]._time
        C_professor=self._course_list.diction[sub1]._professor+"&"+self._course_list.diction[sub2]._professor
        C_description="composite:"+sub1+","+sub2
        temp=composite_course(CID,C_NAME,C_type,C_time,C_professor,C_description,self._course_list.diction[sub1],self._course_list.diction[sub2])
        self._course_list.arr.append(temp)
        self._course_list.diction[CID]=temp

    def add_student_course(self,SID,CID):
        self._student_course[int(SID)][int(CID)]=1

    def get_id(self,num:int):
        ans=""
        print(num)
        while num>0:
            temp=num%10
            ans=str(temp)+ans
            num=(num-temp)/10
        print(ans)
        for i in range(0,4-len(ans)):
            ans="0"+ans
        print(ans)
        return ans

    def get_course_id(self,num:int):
        ans=""
        print(num)
        while num>0:
            temp=num%10
            ans=str(temp)+ans
            num=(num-temp)/10
        print(ans)
        for i in range(0,5-len(ans)):
            ans="0"+ans
        print(ans)
        return ans

    def get_student_activity(self,SID):
        activities=[]
        for i in range(1,self._activity_num+1):
            if(self._student_activity[int(SID)][i]==1):
                activities.append(self._activities[i-1])
        return activities

    def delete_activity(self,SID,AID):
        self._activities[int(AID)-1]=None
        self._student_activity[int(SID)][int(AID)]=1

    def add_activity(self,SID,A_NAME,A_TIME,A_LOCATION,A_MEMBERS,A_LINK):
        self._activity_num+=1
        if(A_LINK!=""):
            temp=online_Activity(self.get_id(self._activity_num),A_NAME,A_TIME,A_LOCATION,A_MEMBERS,A_LINK)
        else:
            temp=Activity(self.get_id(self._activity_num),A_NAME,A_TIME,A_LOCATION,A_MEMBERS,A_LINK)
        self._activities.append(temp)
        self._student_activity[int(SID)][self._activity_num]=1

    def get_student_course_set(self,SID):
        course_set=set()
        for i in range(1,self._course_num+1):
            if(self._student_course[int(SID)][i]==1):
                if(self._course_list.arr[i-1].is_composite()):
                    for item in self._course_list.arr[i-1]._children:
                        course_set.add(item)
                else:
                    course_set.add(self._course_list.arr[i-1])
        return course_set

    def add_student(self,S_NAME,S_STATUS):
       self._student_num+=1
       temp=student(self.get_id(self._student_num),S_NAME,S_STATUS)
       self._student_list.arr.append(temp)
       self._student_list.diction[self.get_id(self._student_num)]=temp

    def delete_course(self,CID):
        del self._course_list.diction[CID]
        self._course_list.arr[int(CID)-1]=None
        for i in range(1,self._student_num+1):
            self._student_course[i][int(CID)]=0

    def delete_student_course(self,SID,CID):
        self._student_course[int(SID)][int(CID)]=0

    def get_Optional_course(self):
        o_course=[]
        courses=course_list()
        courses.arr=self._course_list.arr
        courses.diction=self._course_list.diction
        courses.set_iter(Strategy_Optional())
        while True:
            try:
                temp=next(courses.__iter__())
                o_course.append(temp)
                print(temp._CID)
            except StopIteration:
                break
        return o_course

    def get_Mandatory_course(self):
        o_course=[]
        courses=course_list()
        courses.arr=self._course_list.arr
        courses.diction=self._course_list.diction
        courses.set_iter(Strategy_Mandatory())
        while True:
            try:
                temp=next(courses.__iter__())
                o_course.append(temp)
                print(temp._CID)
            except StopIteration:
                break
        return o_course

    def get_All_course(self):
        o_course=[]
        courses=course_list()
        courses.arr=self._course_list.arr
        courses.diction=self._course_list.diction
        courses.set_iter()
        while True:
            try:
                temp=next(courses.__iter__())
                o_course.append(temp)
                print(temp._CID)
            except StopIteration:
                break
        return o_course
