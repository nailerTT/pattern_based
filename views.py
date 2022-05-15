from pbd import app
from pbd.database import database
from flask import render_template, request, redirect, url_for


def format_data(data):
    fmt = "%.2f"
    result = []
    for item in data:
        if type(item) is list:
            result.append(", ".join([(fmt % i).rstrip('0').rstrip('.')
                                     for i in item]))
        else:
            result.append((fmt % item).rstrip('0').rstrip('.'))
    return result


@app.route("/")
def show_home_login():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    db.get_login_info()
    app.config['DATABASE']= db
    args = {"dataset": dataset,"data":db}
    return render_template('home_login.html', args=args)

@app.route("/show_staff_home")
def show_staff_home():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('staff_home.html', args=args)

@app.route("/staff_home")
def staff_home():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    if "staff_text" in request.args and "password" in request.args:
        a1 = request.args.get("staff_text")
        a2 = request.args.get("password")
    else:
        return render_template('home_login.html', args=args)
    if(db._staff_info.staff_log(a1,a2)):
        db._current="staff"
        db._current_id=a1
        app.config['DATABASE']= db
        return render_template('staff_home.html', args=args)
    else:
        return render_template('home_login.html', args=args)

@app.route("/show_student_home")
def show_student_home():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('student_home.html', args=args)

@app.route("/student_home")
def student_home():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    if "student_text" in request.args:
        a1 = request.args.get("student_text")
        print(a1)
    else:
        return render_template('home_login.html', args=args)
    if(db._student_list.student_log(a1)):
        db._current="student"
        db._current_id=a1
        app.config['DATABASE']= db
        return render_template('student_home.html', args=args)
    else:
        return render_template('not_registered.html', args=args)

@app.route("/stu_profile")
def stu_profile():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    print("***"+db._current_id)
    args = {"dataset": dataset,"data":db}
    return render_template('stu_profile.html', args=args)

@app.route("/stu_course_management")
def stu_course_management():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    stu_course=db.get_student_course(db._current_id)
    for item in stu_course:
        print(item._type)
    args = {"dataset": dataset,"data":db,"course_list":stu_course,"all_course":db._course_list.arr}
    return render_template('stu_course_management.html', args=args)

@app.route("/delete_course")
def delete_course(CID):
    print("delete!!")
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    stu_course=db.get_student_course(db._current_id)
    if "delete_cid" in request.args:
        a1 = request.args.get("delete_course")
        print(a1)
    else:
        args = {"dataset": dataset,"data":db}
        return render_template('home_login.html', args=args)
    db.delete_student_course(db._current_id,a1)
    stu_course=db.get_student_course(db._current_id)
    args = {"dataset": dataset,"data":db,"course_list":stu_course,"all_course":db._course_list.arr}
    return render_template('stu_course_management.html', args=args)

@app.route("/stu_mailbox")
def stu_mailbox():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('stu_mailbox.html', args=args)

@app.route("/stu_send_mail")
def stu_send_mail():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('stu_send_mail.html', args=args)

@app.route("/stu_timetable")
def stu_timetable():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('stu_timetable.html', args=args)

@app.route("/staff_mailbox")
def staff_mailbox():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('staff_mailbox.html', args=args)

@app.route("/staff_send_mail")
def staff_send_mail():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('/staff_send_mail.html', args=args)

@app.route("/staff_stu_course")
def staff_stu_course():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('staff_stu_course.html', args=args)

@app.route("/pending_student_list")
def pending_student_list():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('pending_student_list.html', args=args)

@app.route("/course_list")
def course_list():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('course_list.html', args=args)

@app.route("/register_student")
def register_student():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('register_student.html', args=args)

@app.route("/not_registered")
def not_registered():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('not_registered.html', args=args)

@app.route("/report_problem")
def report_problem():
    dataset = app.config['DATASET']
    db = app.config['DATABASE']
    args = {"dataset": dataset,"data":db}
    return render_template('report_problem.html', args=args)
