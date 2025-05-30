# AirWatcher App - UML project

**AirWatcher** is a C++ application designed to monitor and analyze air quality data from multiple sensors. It provides a role-based interface for different users (private individuals, air cleaner providers, and government agencies), to explore air quality statistics, visualize data, and test system performance, depending on their access level.

## Authors
Authors: Asmae TOUITI, Ines CHEBBI, Tom SANCHEZ, Yassine TAHARSTE, Omar TKITO 


**Project Structure**

This application follows an MVC architecture.

	Model: Manages data (users, sensors, measurements).

	View: Handles input/output interactions.

	Controller: Manages the application flow and user interaction logic.


**Getting Started**

System Requirements: You likely meet them if you're running Linux already (most distributions come with a modern processor and enough RAM).
Installation: The GNU C++ compiler (g++) is often pre-installed. Verify with g++ --version in your terminal. If not installed, use your package manager (e.g., sudo apt install build-essential on Ubuntu/Debian).

To launch the application and sign in:

    1. To build the application, simply run: "make"

This will compile the source files and create the executable "Airwatcher" in the root directory.

Execute the AirWatcher application from the designated directory on the server.
After launching the app, the user is prompted to log in with a username (e.g., government, or another registered key in the CSV files).
Once logged in, a menu corresponding to the user type is displayed. The user can then select a functionality by typing its number.
Upon successful authentication, you will gain access to the AirWatcher console interface, and be able to run functionalities.

    2. Cleaning Up
To remove the object files (.o) and the executable, run: "make clean"
This will clean up the build artifacts and leave your directory tidy.


**Main Features**

The application supports three types of users, each with distinct privileges:


### 1. Government Agent : Sign in by writing "government" in the user login

	- Air Quality Over Area: Calculate average air quality in a geographical area within a date range. Users can define the area by radius around a central point, by specifying a latitude and a longitude.

	Visualize measurements for a specific sensor and attribute (NO2, PM10, SO2, O3): View statistics for a selected sensor and attribute over a date range.

	Sensor Similarity Ranking: Rank all sensors based on their similarity to a chosen sensor during a specified period. This helps identify sensors with similar air quality patterns, 	potentially indicating similar environmental conditions.

	Performance Tests: Run internal performance tests of the main algorithms used.

	Logout.

# Interacting using the Console Interface :
The console interface presents a menu with options tailored to your user role. Use the corresponding numbers or keywords to select the desired functionality. Each option might prompt for additional information, such as sensor IDs, geographical coordinates, or timeframes. The application will display the results of your queries on the console screen.



### 2. Private Individual

- View all readings for a specific sensor and attribute over a date range.
- Logout.

### 3. AirCleaner Provider
The providers have access to the same functionalities as a private individual.

- View all readings for a specific sensor and attribute over a date range.
- Logout.


## Application handling : 

The controller manages:
-User sign-in and privilege assignment.
-Input validation for:
	-Sensor ID
	-Attributes (NO2, PM10, SO2, O3)
	-Dates (in YYYY-MM-DD format)
	-Geographic coordinates (latitude, longitude, radius)
	-Delegation to the model for data retrieval and processing.
	-Interaction with the view for displaying results and error messages.

## Performance Testing
Only available to Government Agency users, this feature allows:
	-Average air quality computation benchmarking.
	-Sensor similarity ranking performance test.
	-Full-scale sensor reading extraction test.
	

## Sample Menu (Government)

AirWatcher App - Government Agency Menu

1. Calculate mean air quality over an area
2. Show all the statistics of a Sensor
3. Rank and score sensors by similarity
4. Run performance tests
5. Sign out

Select a functionality by choosing the corresponding number:


## Technologies Used
C++11




