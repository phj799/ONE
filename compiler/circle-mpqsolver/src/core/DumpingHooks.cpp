/*
 * Copyright (c) 2023 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "DumpingHooks.h"

using namespace mpqsolver::core;

DumpingHooks::DumpingHooks(const std::string &save_path)
  : _save_path(save_path), _dumper(_save_path)
{
}

void DumpingHooks::on_begin_solver(const std::string &model_path, float q8error, float q16error)
{
  _model_path = model_path;
  _dumper.set_model_path(_model_path);
  _dumper.prepare_for_error_dumping();
  _dumper.dump_Q8_error(q8error);
  _dumper.dump_Q16_error(q16error);
}

void DumpingHooks::on_begin_iteration()
{
  _in_iterations = true;
  _num_of_iterations += 1;
}

void DumpingHooks::on_end_iteration(const LayerParams &layers, const std::string &def_type,
                                    float error) const
{
  _dumper.dump_MPQ_configuration(layers, def_type, _num_of_iterations);
  _dumper.dump_MPQ_error(error, _num_of_iterations);
}

void DumpingHooks::on_end_solver(const LayerParams &layers, const std::string &def_dtype,
                                 float qerror)
{
  _dumper.dump_final_MPQ(layers, def_dtype);
  _dumper.dump_MPQ_error(qerror);
  _in_iterations = false;
}

void DumpingHooks::on_quantized(luci::Module *module) const
{
  if (_in_iterations)
  {
    _dumper.dump_quantized(module, _num_of_iterations);
  }
}
