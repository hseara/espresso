/*
  Copyright (C) 2016,2017 The ESPResSo project

  This file is part of ESPResSo.


  ESPResSo is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  ESPResSo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OBSERVABLES_OBSERVABLE_HPP
#define OBSERVABLES_OBSERVABLE_HPP

#include <fstream>
#include <vector>
#include <string>

#include "core/PartCfg.hpp"

namespace Observables {
class Observable {
public:
  friend class CylindricalFluxDensityProfile;
  Observable();
  virtual ~Observable() = default;
  int calculate();

  /* IO functions for observables */
  void set_filename(std::string const &filename, bool binary);
  bool writable() const;
  void write();

  virtual int n_values() const { return 0; }
  std::vector<double> last_value;

private:
  virtual int actual_calculate(PartCfg & partCfg) = 0;

  int n;
  double last_update;

  virtual void do_write();
  std::ofstream m_ofile;
  std::string m_filename;
  bool m_binary;
};

} // Namespace Observables
#endif
