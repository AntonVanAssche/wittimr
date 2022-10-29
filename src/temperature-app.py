#!/usr/bin/env python3

from flask import Flask
import serial
app = Flask(__name__)

html = '''
<!DOCTYPE html>
<html lang="en">
   <head>
      <meta charset="UTF-8" />
      <meta http-equiv="X-UA-Compatible" content="IE=edge" />
      <meta name="viewport" content="width=device-width, initial-scale=1.0" />
      <meta http-equiv="refresh" content="1" />
      <title>What Is The Temperature In My Room</title>
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
      <p>Temperature: {{ content|safe }}</p>
   </body>
</html>
'''

def get_temp():
    ser = serial.Serial('/dev/ttyACM0', 9600)
    ser.flush()

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            return line

@app.route('/')
def home():
    return html.replace('{{ content|safe }}', str(get_temp()))

if __name__ == '__main__':
    app.run()

