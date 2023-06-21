#pragma once

#include <vulkan/vulkan.hpp>

#include "Device.h"
#include "ShaderData.h"

namespace VPP {

namespace impl {

class VertexArray;

class Pipeline : public DeviceResource {
  friend class DrawCmd;

public:
  Pipeline();
  ~Pipeline();

  bool SetShader(const Shader::MetaData& data);
  void SetVertexAttrib(uint32_t location, uint32_t binding, vk::Format format,
                       uint32_t offset);
  bool Enable(const VertexArray& array);

  void BindCmd(const vk::CommandBuffer& buf) const;

private:
  struct Module {
    vk::ShaderModule shader{};
    vk::ShaderStageFlagBits stage{};
  };
  vk::Pipeline pipeline_{};
  vk::PipelineLayout pipe_layout_{};
  std::vector<vk::DescriptorSetLayout> desc_layout_{};
  vk::DescriptorPool desc_pool_{};
  std::vector<vk::DescriptorSet> desc_set_{};
  std::vector<Module> shaders_{};
  std::vector<vk::VertexInputBindingDescription> vertex_bindings_{};
  std::vector<vk::VertexInputAttributeDescription> vertex_attribs_{};
};

} // namespace impl

} // namespace VPP
