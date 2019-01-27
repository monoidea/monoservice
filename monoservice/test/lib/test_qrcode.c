/* Monoservice - monoidea's monoservice
 * Copyright (C) 2019 Joël Krähemann
 *
 * This file is part of Monoservice.
 *
 * Monoservice is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Monoservice is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Monoservice.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <glib-object.h>

#include <monoservice/lib/monoservice_qrcode.h>

#define TEST_QRCODE_FILENAME "test.svg"

int
main(int argc, char **argv)
{
  MonoserviceQrcode *qrcode;
  
  qrcode = monoservice_qrcode_new();
  monoservice_qrcode_encode(qrcode);

  monoservice_qrcode_export_svg(qrcode,
				TEST_QRCODE_FILENAME);
  
  return(0);
}
