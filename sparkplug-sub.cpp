#include "sparkplug_metric.pb.h" // Generated from .proto

// buffer: pointer to received data
// size: size of received data (in bytes)
sparkplug::MetricsPayload payload;
bool success = payload.ParseFromArray(buffer, size);

if (success) {
    // Now you can access fields:
    for (const auto& metric : payload.metrics()) {
        std::cout << "Metric name: " << metric.name()
                  << ", value: " << metric.value()
                  << ", timestamp: " << metric.timestamp() << std::endl;
    }
} else {
    std::cerr << "Failed to parse protobuf message." << std::endl;
}
