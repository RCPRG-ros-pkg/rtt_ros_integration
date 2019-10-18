#ifndef OROCOS_RTT_TF_COMPONENT_HPP
#define OROCOS_RTT_TF_COMPONENT_HPP

#include <rtt/RTT.hpp>
#include <tf2_msgs/TFMessage.h>
#include <tf2/buffer_core.h>

namespace rtt_tf
{
  // Inherit from TaskContext and Transformer, the second is required in order to use tf_prefix
  class RTT_TF: public RTT::TaskContext, protected tf2::BufferCore
  {
    static const int DEFAULT_BUFFER_SIZE = 100;

    double prop_cache_time;
    double prop_buffer_size;
    std::string prop_tf_prefix;

    RTT::InputPort<tf2_msgs::TFMessage> port_tf_in;
    RTT::InputPort<tf2_msgs::TFMessage> port_tf_static_in;
    RTT::OutputPort<tf2_msgs::TFMessage> port_tf_out;
    RTT::OutputPort<tf2_msgs::TFMessage> port_tf_static_out;

    void internalUpdate(
        tf2_msgs::TFMessage& msg,
        RTT::InputPort<tf2_msgs::TFMessage>& port,
        bool is_static);

    ros::Time getLatestCommonTime(
        const std::string& target,
        const std::string& source) const;

    bool canTransform(
        const std::string& target,
        const std::string& source) const;

    bool canTransformAtTime(
        const std::string& target,
        const std::string& source,
        const ros::Time& common_time) const;

    geometry_msgs::TransformStamped lookupTransform(
        const std::string& target,
        const std::string& source) const;

    geometry_msgs::TransformStamped lookupTransformAtTime(
        const std::string& target,
        const std::string& source,
        const ros::Time& common_time) const;

    void broadcastTransform(
        const geometry_msgs::TransformStamped &tform);

    void broadcastTransforms(
        const std::vector<geometry_msgs::TransformStamped> &tforms);

    void broadcastStaticTransform(
        const geometry_msgs::TransformStamped &tform);

    void broadcastStaticTransforms(
        const std::vector<geometry_msgs::TransformStamped> &tforms);

    void addTFOperations(RTT::Service::shared_ptr service);

  public:
    RTT_TF(std::string const& name);

    bool configureHook();

    void updateHook();

    void cleanupHook();
  };
}//namespace rtt_tf
#endif
