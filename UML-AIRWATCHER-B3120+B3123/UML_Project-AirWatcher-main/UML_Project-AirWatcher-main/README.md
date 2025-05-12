# UML_Project - AirWatcher

Welcome to AirWatcher, a software application designed to empower government agencies in monitoring and analyzing air quality data. This user manual guides you through AirWatcher's functionalities, tailored to different user roles.

AirWatcher caters to different user roles with varying levels of access:

    Government Agent: Full access to monitor data, analyze sensor performance, and evaluate air quality across locations.

    Air Cleaner Provider: Access to observe the effectiveness of air cleaners in improving air quality.

    Private Individual: Monitor data from your personal sensors and track points earned for contributing data.

    Administrator

Getting Started

System Requirements: You likely meet them if you're running Linux already (most distributions come with a modern processor and enough RAM).
Installation: The GNU C++ compiler (g++) is often pre-installed. Verify with g++ --version in your terminal. If not installed, use your package manager (e.g., sudo apt install build-essential on Ubuntu/Debian).

To launch the application and sign in:

    1) To build the application, simply run: "make"
This will compile the source files and create the executable airwatcher in the root directory.

Execute the AirWatcher application from the designated directory on the server.
Enter your credentials provided by the system administrator.
Upon successful authentication, you will gain access to the AirWatcher console interface.

    2) Cleaning Up
To remove the object files (.o) and the executable, run: "make clean"
This will clean up the build artifacts and leave your directory tidy.

Main Features
    Government Agent : Sign in by writing "gouv" in the user login

Analyze Sensor Data: View real-time and historical data from all sensors, including sensor ID, location, timestamps, and measured attributes (e.g., O3 concentration).
Calculate Mean Air Quality: Assess average air quality for a specified geographical area and time period. Users can define the area by radius around a central point or specify a specific latitude and longitude. The application calculates the mean Air Quality Index (AQI) based on sensor data within the chosen area and timeframe.
Compare Sensor Similarity: Rank all sensors based on their similarity to a chosen sensor during a specified period. This helps identify sensors with similar air quality patterns, potentially indicating similar environmental conditions.

Utilizing the Console Interface :
The console interface presents a menu with options tailored to your user role. Use the corresponding numbers or keywords to select the desired functionality. Each option might prompt for additional information, such as sensor IDs, geographical coordinates, or timeframes. The application will display the results of your queries on the console screen.


