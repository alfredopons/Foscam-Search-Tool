/*
 * FoscamSearchTool
 *
 * Copyright (C) 2017 Alfredo Pons Menargues <alfredo.pons@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "FoscamSearch.hpp"
#include <iostream>

// Return num cameras to shell
int main (void)
{
  std::vector<Camera> cameras;
  FoscamSearch fs;

  if (fs.search_foscam (cameras))
    {
      for (auto &i : cameras)
        std::cout << "Received FOSCAM camera from IP: " <<  i.m_ip_camera << ", Name: " << i.m_name_camera << " Port: " <<  i.m_port_ip_camera << std::endl;

      return cameras.size();
    }

  return 0;
}
