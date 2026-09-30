#include <ament_index_cpp/get_package_share_directory.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include "manager/node_manager.hpp"

namespace robosense { namespace lidar {

class RslidarComponent : public rclcpp::Node
{
public:
  explicit RslidarComponent(const rclcpp::NodeOptions & options)
    : Node("rslidar_sdk_node", options), manager_(*this)
  {
    auto path = declare_parameter<std::string>("config_path", "");
    if (path.empty()) {
      path = ament_index_cpp::get_package_share_directory("rslidar_sdk") +
        "/config/rslidar.param.yaml";
    }
    manager_.init(YAML::LoadFile(path));
    manager_.start();
    RCLCPP_INFO(get_logger(), "LiDAR configuration: %s", path.c_str());
  }

  ~RslidarComponent() override = default;

private:
  NodeManager manager_;
};

}}  // namespace robosense::lidar

RCLCPP_COMPONENTS_REGISTER_NODE(robosense::lidar::RslidarComponent)
