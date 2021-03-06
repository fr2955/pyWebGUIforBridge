from flask import Flask, request, render_template

from code import arduinoSerial

app = Flask(__name__)


def setupSerial():
    global arduino
    arduino = arduinoSerial.Arduino(9600, '*', 0)


setupSerial()
app = Flask(__name__)


@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        print(request.form['submit'])
        if request.form['submit'] == 'OPEN':
            print("Open")
            arduino.serWrite('o')
        elif request.form['submit'] == 'CLOSE':
            print("Close")
            arduino.serWrite('c')
        elif request.form['submit'] == 'RECO':
            print("Reconnecting")
            setupSerial()
        elif request.form['submit'] == 'DISCO':
            print("Terminating Program")
            exit()
        elif request.form['submit'] == 'SWAP':
            print("Swapping Bridge State")
            arduino.serWrite('e')
        else:
            pass  # unknown
    return render_template('home.html')


@app.route('/state')
def getState():
    arduino.serWrite('s')
    a = arduino.serRead()
    print("test")
    return "test"


if __name__ == "__main__":
    app.run(debug=False)
