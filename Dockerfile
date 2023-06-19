FROM docker.io/library/python:latest

WORKDIR /app

COPY requirements.txt requirements.txt
RUN pip install -r requirements.txt

# Access /dev/ttyACM0
RUN usermod -a -G dialout root

COPY src/ .

EXPOSE 5000

CMD [ "python3", "-m" , "flask", "run", "--host=0.0.0.0"]
