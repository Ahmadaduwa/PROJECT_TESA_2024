# TESA - Real-time Audio Signal Processing and IoT System

## Overview

TESA (Thai Embedded Systems Academy) is a comprehensive embedded systems project that demonstrates real-time audio signal processing, machine learning classification, and IoT communication capabilities. The project consists of a series of workshop exercises and a final project that integrates audio capture, FFT analysis, KNN classification, and MQTT-based IoT communication.

## Project Structure

### Final Project (`finalProject10/`)
The main application that combines all learned concepts into a complete IoT audio processing system.

**Key Features:**
- **Real-time Audio Capture**: Uses ALSA to capture audio at 48kHz sampling rate
- **FFT Analysis**: Performs Fast Fourier Transform on audio data to extract frequency components
- **Machine Learning**: Implements K-Nearest Neighbors (KNN) classification for signal prediction
- **Database Storage**: SQLite databases for storing frequency data and classification outcomes
- **MQTT Communication**: Publishes processed data and receives control commands via MQTT
- **Multi-threading**: Concurrent processing using pthreads for audio capture, FFT processing, and IoT communication

**Main Components:**
- `sound_app.c` - Main application orchestrating all threads
- `alsa_thr.c` - Audio capture thread using ALSA library
- `fft_thr.c` - FFT processing and classification thread
- `iot_app.c` - MQTT communication thread
- `db_helper.c` - Database operations for data persistence
- `predictSignal.c` - MATLAB-generated KNN classification model
- `sound_freq.c` - MATLAB-generated FFT implementation

### Workshop Exercises (`workshop/`)

#### Exercise 2 (`ex_02/`) - Basic C Programming
- Simple "Hello World" program with user input
- Introduction to command-line arguments
- Basic file I/O operations

#### Exercise 3 (`ex_03/`) - Multi-threading Fundamentals
- Introduction to pthread programming
- Producer-consumer pattern implementation
- Thread synchronization using mutexes and condition variables
- Data pipeline: front → mid → end processing threads

#### Exercise 4 (`ex_04/`) - IoT Communication
- REST API client implementation
- MQTT publisher/subscriber functionality
- JSON data handling with cJSON library
- Concurrent REST and MQTT communication

#### Exercise 5 (`ex_05/`) - Database Operations
- SQLite database integration
- CRUD operations for data persistence
- Memory management and data structures

#### Exercise 11 (`ex_11/`) - MATLAB Code Generation
- MATLAB to C code generation workflow
- Integration of generated code with C applications
- Mathematical computation implementation

#### Exercise 12 (`ex_12/`) - Advanced Signal Processing
- Audio signal processing fundamentals
- Frequency domain analysis

#### Exercise 13 (`ex_13/`) - Audio Processing Application
- Complete audio processing application
- Integration of signal processing algorithms

#### Exercise 14 (`ex_14/`) - Machine Learning Integration
- KNN classification implementation
- Feature extraction from audio signals
- Model integration with real-time processing

## Technical Architecture

### System Flow
```
Audio Input (ALSA) → FFT Analysis → Feature Extraction → KNN Classification → Database Storage → MQTT Publishing
```

### Thread Architecture
1. **ALSA Thread**: Captures audio data continuously
2. **FFT Thread**: Processes audio data, performs FFT, extracts features, and runs classification
3. **MQTT Thread**: Handles IoT communication, publishes results, and receives control commands

### Data Flow
1. Audio data captured at 48kHz, 16-bit samples
2. 4096-sample buffers processed through FFT
3. Frequency components extracted (50Hz, 1kHz, 2kHz bins)
4. Features fed to KNN classifier for event detection
5. Results stored in SQLite database
6. Data published via MQTT with JSON format

## Dependencies

### System Libraries
- **ALSA** (`libasound2-dev`) - Audio capture
- **SQLite3** (`libsqlite3-dev`) - Database operations
- **Paho MQTT** (`libpaho-mqtt-dev`) - MQTT communication
- **cJSON** (`libcjson-dev`) - JSON handling
- **OpenMP** - Parallel processing support

### Development Tools
- **GCC** - C compiler
- **Make** - Build system
- **MATLAB** - Code generation (for signal processing algorithms)

## Building and Running

### Prerequisites
```bash
# Install required libraries (Ubuntu/Debian)
sudo apt-get update
sudo apt-get install libasound2-dev libsqlite3-dev libpaho-mqtt-dev libcjson-dev build-essential

# Install MATLAB (for code generation)
# Follow MATLAB installation instructions
```

### Build Instructions
```bash
# Navigate to final project directory
cd finalProject10/

# Build the application
make clean
make

# Run the application
./sound_app hw:0  # hw:0 is the ALSA device name
```

### Workshop Exercises
```bash
# Build and run individual exercises
cd workshop/ex_02/
make
./hello YourName

cd workshop/ex_03/
make
./thr_app

cd workshop/ex_04/
make
./iot_app http://api.example.com/data sensor/topic
```

## Configuration

### MQTT Settings
- **Broker**: `tcp://broker.emqx.io:1883`
- **Client ID**: `TGR2024_MQTT_CLIENT`
- **Publish Topic**: `data/raspberry/prediction`
- **Control Topics**: 
  - `data/raspberry/open` - Start processing
  - `data/raspberry/close` - Stop processing

### Audio Settings
- **Sample Rate**: 48kHz
- **Channels**: Mono (1 channel)
- **Format**: 16-bit signed little-endian
- **Buffer Size**: 4096 samples

### Database Schema
```sql
-- Size tracking table
CREATE TABLE size_table (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    size INTEGER,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- Outcome data table
CREATE TABLE outcome_table (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    timestamp VARCHAR(20),
    frequency1 REAL,
    frequency2 REAL,
    frequency3 REAL,
    event INTEGER
);
```

## Usage Examples

### Basic Operation
1. Start the application: `./sound_app hw:0`
2. Send MQTT command to `data/raspberry/open` to begin processing
3. Audio data is captured, processed, and results published
4. Send MQTT command to `data/raspberry/close` to stop processing

### MQTT Commands
```bash
# Start processing
mosquitto_pub -h broker.emqx.io -t "data/raspberry/open" -m "start"

# Stop processing
mosquitto_pub -h broker.emqx.io -t "data/raspberry/close" -m "stop"

# Subscribe to results
mosquitto_sub -h broker.emqx.io -t "data/raspberry/prediction"
```

### Sample Output
```json
{
    "timestamp": "2024-01-15 10:30:45",
    "frequency1": 0.1234,
    "frequency2": 0.5678,
    "frequency3": 0.9012,
    "outcome": "1"
}
```

## Learning Objectives

This project demonstrates:

1. **Embedded Systems Programming**: Real-time audio processing on Linux
2. **Multi-threading**: Concurrent programming with pthreads
3. **Signal Processing**: FFT analysis and frequency domain operations
4. **Machine Learning**: KNN classification for pattern recognition
5. **IoT Communication**: MQTT protocol for device communication
6. **Database Integration**: SQLite for data persistence
7. **Code Generation**: MATLAB to C workflow for algorithm implementation
8. **System Integration**: Combining multiple technologies into a cohesive system

## Troubleshooting

### Common Issues

1. **Audio Device Not Found**
   ```bash
   # List available audio devices
   arecord -l
   # Use appropriate device name (e.g., hw:1,0)
   ```

2. **MQTT Connection Failed**
   - Check internet connectivity
   - Verify broker address and port
   - Ensure firewall allows MQTT traffic

3. **Database Permission Errors**
   - Check file permissions for database files
   - Ensure write access to project directory

4. **Compilation Errors**
   - Verify all dependencies are installed
   - Check library paths and include directories

## Contributing

This project serves as a learning resource for embedded systems development. Contributions should focus on:
- Code improvements and optimizations
- Additional signal processing algorithms
- Enhanced IoT communication features
- Documentation improvements

## License

This project is part of the TESA (Thai Embedded Systems Academy) curriculum and is intended for educational purposes.

## Contact

For questions or support regarding this project, please refer to the TESA course materials or contact the course instructors.
