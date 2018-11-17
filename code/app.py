import serial
from flask import request
from flask import Flask
app = Flask(__name__)

@app.route('/', methods = ['POST', 'GET'])
def hello():
    if request.method == 'POST':
        print(request.form['submit'])
        ser = serial.Serial('COM5', 9600, timeout=1)
        if request.form['submit'] == 'OPEN':
            print("Open")
            ser.write('4')
        elif request.form['submit'] == 'CLOSE':
            print("Close")
            ser.write('5')
        else:
            pass  # unknown
    return '<form action="/" method="POST"><input type="submit" name="submit" value="OPEN"><input type="submit" name="submit" value="CLOSE"></form>'

if __name__ == "__main__":
    app.run()