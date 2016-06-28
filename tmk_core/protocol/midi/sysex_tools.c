//midi for embedded chips,
//Copyright 2010 Alex Norman
//
//This file is part of avr-midi.
//
//avr-midi is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//avr-midi is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with avr-midi.  If not, see <http://www.gnu.org/licenses/>.

#include "sysex_tools.h"

uint16_t sysex_encoded_length(uint16_t decoded_length){
   uint8_t remainder = decoded_length % 7;
   if (remainder)
      return (decoded_length / 7) * 8 + remainder + 1;
   else
      return (decoded_length / 7) * 8;
}

uint16_t sysex_decoded_length(uint16_t encoded_length){
   uint8_t remainder = encoded_length % 8;
   if (remainder)
      return (encoded_length / 8) * 7 + remainder - 1;
   else
      return (encoded_length / 8) * 7;
}

uint16_t sysex_encode(uint8_t *encoded, const uint8_t *source, const uint16_t length){
   uint16_t encoded_full = length / 7; //number of full 8 byte sections from 7 bytes of input
   uint16_t i,j;

   //fill out the fully encoded sections
   for(i = 0; i < encoded_full; i++) {
      uint16_t encoded_msb_idx = i * 8;
      uint16_t input_start_idx = i * 7;
      encoded[encoded_msb_idx] = 0;
      for(j = 0; j < 7; j++){
         uint8_t current = source[input_start_idx + j];
         encoded[encoded_msb_idx] |= (0x80 & current) >> (1 + j);
         encoded[encoded_msb_idx + 1 + j] = 0x7F & current;
      }
   }

   //fill out the rest if there is any more
   uint8_t remainder = length % 7;
   if (remainder) {
      uint16_t encoded_msb_idx = encoded_full * 8;
      uint16_t input_start_idx = encoded_full * 7;
      encoded[encoded_msb_idx] = 0;
      for(j = 0; j < remainder; j++){
         uint8_t current = source[input_start_idx + j];
         encoded[encoded_msb_idx] |= (0x80 & current) >> (1 + j);
         encoded[encoded_msb_idx + 1 + j] = 0x7F & current;
      }
      return encoded_msb_idx + remainder + 1;
   } else {
      return encoded_full * 8;
   }
}

uint16_t sysex_decode(uint8_t *decoded, const uint8_t *source, const uint16_t length){
   uint16_t decoded_full = length / 8;
   uint16_t i,j;

   if (length < 2)
      return 0;

   //fill out the fully encoded sections
   for(i = 0; i < decoded_full; i++) {
      uint16_t encoded_msb_idx = i * 8;
      uint16_t output_start_index = i * 7;
      for(j = 0; j < 7; j++){
         decoded[output_start_index + j] = 0x7F & source[encoded_msb_idx + j + 1];
         decoded[output_start_index + j] |= (0x80 & (source[encoded_msb_idx] << (1 + j)));
      }
   }
   uint8_t remainder = length % 8;
   if (remainder) {
      uint16_t encoded_msb_idx = decoded_full * 8;
      uint16_t output_start_index = decoded_full * 7;
      for(j = 0; j < (remainder - 1); j++) {
         decoded[output_start_index + j] = 0x7F & source[encoded_msb_idx + j + 1];
         decoded[output_start_index + j] |= (0x80 & (source[encoded_msb_idx] << (1 + j)));
      }
      return decoded_full * 7 + remainder - 1;
   } else {
      return decoded_full * 7;
   }
}

