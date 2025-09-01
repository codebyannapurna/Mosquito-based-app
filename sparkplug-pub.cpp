
#include <mosquittopp.h>
#include <iostream>
#include <cstring>
#include "sparkplug_metric.pb.h" // Generated from .proto file

const char* HOST = "localhost";
const int PORT = 1883;
const int KEEP_ALIVE = 60;
const char* TOPIC = "spBv1.0/group_id/NBIRTH/edge_node/device";

class SparkplugPublisher : public mosqpp::mosquittopp {
public:
    SparkplugPublisher(const char *id): mosqpp::mosquittopp(id) {
        connect(HOST, PORT, KEEP_ALIVE);
    }

    void on_connect(int rc) override {
        if(rc == 0) {
            sparkplug::MetricsPayload payload;
            auto metric = payload.add_metrics();
            metric->set_name("Temperature");
            metric->set_value(23.5);
            metric->set_timestamp(time(nullptr));

            std::string binary_data;
            if(payload.SerializeToString(&binary_data)) {
                publish(nullptr, TOPIC, binary_data.size(), binary_data.data(), 1, false);
            } else {
                std::cerr << "Failed to serialize payload." << std::endl;
            }
        } else {
            std::cerr << "Connection failed: " << rc << std::endl;
        }
    }

    void on_publish(int mid) override {
        std::cout << "Sparkplug metric published. Message ID: " << mid << std::endl;
        disconnect();
    }
};

int main() {
    mosqpp::lib_init();
    SparkplugPublisher publisher("EmbeddedLinuxPublisher");
    while(!publisher.want_write()) {
        publisher.loop();
    }
    mosqpp::lib_cleanup();
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
