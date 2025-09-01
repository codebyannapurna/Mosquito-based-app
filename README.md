# Mosquito-based-app

Step 1: Define a .proto Schema
Create a file, sparkplug_metric.proto
Step 2: Generate C++ Classes with protoc

protoc --cpp_out=. sparkplug_metric.proto
# This generates sparkplug_metric.pb.h and sparkplug_metric.pb.cc
Install protocol buffers and compiler: sudo apt-get install protobuf-compiler libprotobuf-dev

Step 3: Create C++ Publisher with Protobuf Serialization
  Compile sample
  g++ -o sparkplug_pub sparkplug_pub.cpp sparkplug_metric.pb.cc -lmosquittopp -lmosquitto -lprotobuf
Integrate with Cron
Deploy the compiled binary and schedule it using cron to run at regular intervals.

Notes
Mosquitto libraries are lightweight and ideal for embedded Linux systems

Setting Up Cron Job
Deploy the compiled program (e.g., as /usr/local/bin/sparkplug-pub).

Edit the crontab:

bash
  crontab -e
Add a cron entry to run the program every minute
  text
  * * * * * /usr/local/bin/sparkplug-pub
Adjust the timing as needed.
