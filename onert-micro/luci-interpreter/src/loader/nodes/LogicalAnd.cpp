/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Builders.h"

#include "kernels/LogicalAnd.h"

namespace luci_interpreter
{

std::unique_ptr<Kernel> build_kernel_CircleLogicalAnd(std::vector<const Tensor *> &&inputs,
                                                      std::vector<Tensor *> &&outputs,
                                                      const uint32_t op_index,
                                                      KernelBuilder &builder)
{
  assert(inputs.size() == 2);

  const Tensor *input1 = inputs.at(0);
  const Tensor *input2 = inputs.at(1);
  Tensor *output = outputs.at(0);

  return std::make_unique<kernels::LogicalAnd>(input1, input2, output);
}

} // namespace luci_interpreter