import serial
from flask import Flask, render_template, request
from time import sleep


ser = serial.Serial('COM5', 9600)
ser.setDTR(True)
sleep(1)
ser.flushInput()
ser.setDTR(False)


app = Flask(__name__)
@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        print(request.form['submit'])
        if request.form['submit'] == 'OPEN':
            print("Open")
            ser.write(str.encode('4'))
        elif request.form['submit'] == 'CLOSE':
            print("Close")
            ser.write(str.encode('5'))
        else:
            pass  # unknown
    return render_template('home.html')
if __name__ == "__main__":
    app.run(debug= True)