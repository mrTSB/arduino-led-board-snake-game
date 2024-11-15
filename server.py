from flask import Flask, render_template, jsonify, request
from flask_cors import CORS
import serial
import time

app = Flask(__name__)
CORS(app)

grid = [[0 for _ in range(8)] for _ in range(8)]

try:
    arduino = serial.Serial(
        port='COM6',
        baudrate=115200,
        timeout=1
    )
    time.sleep(2)
    print("Connected to Arduino on port COM6")
except Exception as e:
    print(f"An unexpected error occurred: {e}")

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/update_grid', methods=['POST'])
def update_grid():
    print("API /update_grid called")
    global grid
    data = request.get_json()
    new_grid = data['grid']
    
    positions = ""
    for i in range(8):
        for j in range(8):
            if grid[i][j] != new_grid[i][j]:
                positions += f"{i} {j} "
                print(i)
                print(j)

    try:
        arduino.write(positions.encode())
    except:
        print("Failed to communicate with Arduino")
    
    grid = new_grid
    return jsonify({'status': 'success'})

@app.route('/get_grid', methods=['GET'])
def get_grid():
    return jsonify({'grid': grid})

if __name__ == '__main__':
    app.run(debug=True) 