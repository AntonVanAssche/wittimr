#!/usr/bin/env python3

import threading

import serial
from flask import Flask, render_template_string
from flask_socketio import SocketIO

app = Flask(__name__)
app.wsgi_app = ProxyFix(app.wsgi_app)
socketio = SocketIO(app)

html = """
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8" />
        <meta http-equiv="X-UA-Compatible" content="IE=edge" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
        <title>What Is The Temperature In My Room</title>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/socket.io/3.1.3/socket.io.js"></script>
        <script type="text/javascript">
            let protocol = (window.location.protocol === 'https:') ? 'wss' : 'ws';
            let socket = io.connect(protocol + '://' + document.domain + ':' + location.port);

            function updateTemperature(data) {
                document.getElementById('temperature').innerText = data + ' °C';
            }
        </script>
        <style>
            * {
                margin: 0;
                padding: 0;
                box-sizing: border-box;
            }

            body {
                background-color: #141414;
                color: #ddd;
                font-family: sans-serif;
                display: flex;
                flex-direction: column;
                justify-content: center;
                align-items: center;
                height: 100vh;
            }

            h1 {
                font-size: 3rem;
                margin-bottom: 1rem;
            }

            p {
                font-size: 2rem;
            }
        </style>
    </head>
    <body>
        <h1>What Is The Temperature In My Room</h1>
        <p>Temperature: <span id="temperature">Loading...</span></p>
    </body>
</html>
"""


def get_temperature():
    ser = serial.Serial("/dev/ttyACM0", 9600)
    ser.flush()

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode("utf-8").rstrip()
            return line


@app.route("/")
def home():
    return render_template_string(html)


@socketio.on("connect")
def handle_connect():
    socketio.emit("temperature_update", get_temperature())


if __name__ == "__main__":
    thread = threading.Thread(target=read_temperature)
    thread.daemon = True  # Ensure it closes when the app stops
    thread.start()

    socketio.run(app, host="0.0.0.0", port=5000)
