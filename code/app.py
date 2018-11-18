import serial
from flask import request
from flask import Flask
from time import sleep


ser = serial.Serial('COM5', 9600)
ser.setDTR(True)
sleep(1)
ser.flushInput()
ser.setDTR(False)

app = Flask(__name__)

@app.route('/', methods = ['POST', 'GET'])
def webApp():
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
    return '<form action="/" method="POST"><input type="submit" name="submit" value="OPEN"><input type="submit" name="submit" value="CLOSE"></form>'

if __name__ == "__main__":
    webApp.run(app)