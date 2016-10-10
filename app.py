#########################
#Author: James Poole
#Date: 10 October 2016
#########################

from flask import Flask, render_template, request, redirect, request, url_for, make_response
import RPi.GPIO as GPIO

app = Flask(__name__)

GPIO.setmode(GPIO.BCM)

#dictionary to hold each pin's associated colour and state
pins = {
	18 : { 'colour' : 'blue', 'state' : GPIO.LOW},
	23 : { 'colour' : 'red', 'state' : GPIO.LOW},
	24 : { 'colour' : 'green', 'state' : GPIO.LOW}
}

for pin in pins:
	GPIO.setup(pin, GPIO.OUT)
	GPIO.output(pin, GPIO.LOW)

@app.route('/')
def index():
	for pin in pins:
		pins[pin]['state'] = GPIO.input(pin)

	templateData = {
		'pins' : pins
	}

	return render_template('indextrial.html', **templateData)

@app.route('/<changepin>/<action>', methods=['POST'])
def reroute(changepin, action):

	changePin = int(changepin)

	if action == "on":
		GPIO.output(changePin, GPIO.HIGH)
	elif action == "off":
		GPIO.output(changePin, GPIO.LOW)

	response = make_response(redirect(url_for('index')))
	return(response)

app.run(debug=True, host='0.0.0.0', port=8000)
