from code import arduinoSerial
import time
import atexit
from flask import Flask, request, render_template, redirect, url_for, send_from_directory

app = Flask(__name__)


def setupSerial():
	global arduino
	arduino=arduinoSerial.Arduino(9600,'*',0)
setupSerial()
app = Flask(__name__)
@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        print(request.form['submit'])
        if request.form['submit'] == 'OPEN':
            print("Open")
            arduino.serWrite('4')
        elif request.form['submit'] == 'CLOSE':
            print("Close")
            arduino.serWrite('5')
        elif request.form['submit'] == 'RECO':
            print("Reconnecting")
            setupSerial()
        elif request.form['submit'] == 'DISCO':
            print("Terminating Program")
            exit()

        else:
            pass  # unknown
    return render_template('home.html')


@app.route('/state')
def getState():
    arduino.serWrite('6')
    a = arduino.serRead()
    print(a)
    return a

if __name__ == "__main__":
	app.run(debug=True)
