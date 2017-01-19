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

#ifndef FOSCAMSEARCH_HPP_
#define FOSCAMSEARCH_HPP_


#include <string>
#include <vector>

#define BUFFER_SIZE  255
#define BROADCAST_IP  "255.255.255.255"
#define BROADCAST_PORT  10000
#define LENGTH_NAME_CAMERA  20
#define MAX_NETWORK_NUM_CAMERAS 20


class Camera
{
  public:
    /*! ip camera */
    std::string m_ip_camera;
    /*! name camera */
    std::string m_name_camera;
    /*! camera http port used for IP communication */
    int m_port_ip_camera = 0;
};

class FoscamSearch
{
  public:

    FoscamSearch();
    virtual ~FoscamSearch();

    /**
    Search Foscam cameras on then network.
    \param[out] foscam_cameras Cameras found.
    \return false If there is no camera on the network.
    */
    bool search_foscam (std::vector<Camera> &foscam_cameras);

};

#endif /* FOSCAMSEARCH_HPP_ */
