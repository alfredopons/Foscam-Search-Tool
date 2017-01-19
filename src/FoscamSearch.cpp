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
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

FoscamSearch::FoscamSearch()
{
}

FoscamSearch::~FoscamSearch()
{
}


bool
FoscamSearch::search_foscam (std::vector<Camera> &foscam_cameras)
{
  // Messages sent to broadcast address
  uint8_t msg1[27] = { 0x4d, 0x4f, 0x5f, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
                     };
  uint8_t msg2[5] = { 0xb4, 0x9a, 0x70, 0x4d, 0x00 };
  int s = -1;
  char buf[512];
  struct sockaddr_in broadcastAddr;
  std::string broadcastIP = BROADCAST_IP;
  uint16_t broadcastPort = BROADCAST_PORT;

  if ( (s = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
      std::cerr << "Can't open UDP socket" << std::endl;
      return false;
    }

  int broadcastPermission = 1;

  if (setsockopt (s, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof (broadcastPermission)) < 0)
    {
      std::cerr << "setsockopt error" << std::endl;
      return false;
    }

  /* Construct local address structure */
  memset (&broadcastAddr, 0, sizeof (broadcastAddr));
  broadcastAddr.sin_family = AF_INET;
  broadcastAddr.sin_addr.s_addr = inet_addr (broadcastIP.c_str());
  broadcastAddr.sin_port = htons (broadcastPort);

  //send the message 1
  if (sendto (s, msg1, sizeof (msg1), 0, (struct sockaddr *) &broadcastAddr, sizeof (broadcastAddr)) == -1)
    {
      std::cerr << "Error sending msg 1" << std::endl;
      return false;
    }

  //send the message 2
  if (sendto (s, msg2, sizeof (msg2), 0, (struct sockaddr *) &broadcastAddr, sizeof (broadcastAddr)) == -1)
    {
      std::cerr << "Error sending msg 2" << std::endl;
      return false;
    }

  char name_camera[LENGTH_NAME_CAMERA + 1];
  int port_camera = 0;
  int offset_name = 36;
  int offset_port = 75;
  int len = sizeof (broadcastAddr);
  int ret = 0;
  int num_cameras_detected = 0;
  fd_set fdMaskRead;
  fd_set fdMaskError;
  struct timeval timeout;
  // If in 1 seconds nothing is received, no Foscam cameras in network.
  timeout.tv_sec = 1;
  timeout.tv_usec = 0;

  while (num_cameras_detected < MAX_NETWORK_NUM_CAMERAS)
    {
      /*********** Wait for reply ***********/
      memset (buf, 0x00, BUFFER_SIZE);
      FD_ZERO (&fdMaskRead);
      FD_ZERO (&fdMaskError);
      FD_SET (s, &fdMaskRead);
      FD_SET (s, &fdMaskError);
      ret = ::select (s + 1, &fdMaskRead, NULL, &fdMaskError, &timeout);

      if (ret < 0)
        {
          std::cerr << "Error to call method select: " <<  errno << " (" <<  strerror (errno) << ")" << std::endl;
          return false;
        }
      else if (ret == 0)
        {
          // Timeout done
          break;
        }
      else
        {
          if (FD_ISSET (s, &fdMaskRead))
            {
              // Change value
              ret = recvfrom (s, buf, BUFFER_SIZE, 0, (struct sockaddr *) &broadcastAddr, (socklen_t*) &len);

              if (ret == 0)
                {
                  // No data
                  continue;
                }

              if (ret == -1)
                {
                  std::cerr << "Error receiving data: " <<  errno << " (" <<  strerror (errno) << ")" << std::endl;
                  return false;
                }

              if (ret != 129)
                {
                  std::cerr << "Unknown response. Not Foscam response." << std::endl;
                  return false;
                }

              num_cameras_detected++;
              // Comprobar tamany buffer rebut
              memcpy (name_camera, buf + offset_name, LENGTH_NAME_CAMERA);
              name_camera[LENGTH_NAME_CAMERA] = '\0';
              port_camera = buf[offset_port];
              Camera fc;
              fc.m_ip_camera = inet_ntoa (broadcastAddr.sin_addr);
              fc.m_name_camera = name_camera;
              fc.m_port_ip_camera = port_camera;
              foscam_cameras.push_back (fc);
            }
        }
    }

  ::close (s);
  return true;
}
